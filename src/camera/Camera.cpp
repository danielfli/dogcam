#include "Camera.hpp"
#include "image.hpp"

#include <tuple>

Camera::Camera() : post_processor_(this)
{
}

Camera::~Camera()
{
	std::cout << "Closing Libcamera application..."  << std::endl;
	CameraStoppen();
	Teardown();
	CameraClose();
}

void Camera::CameraClose()
{
	if (camera_acquired_)
		m_Camera->release();
	camera_acquired_ = false;

	m_Camera.reset();
	m_CameraManager.reset();
	std::cerr << "Camera closed" << std::endl;
}

bool Camera::CameraOpen()
{
	m_CameraManager = std::make_unique<libcamera::CameraManager>();
    errorCodeCamera = m_CameraManager->start();
    if(errorCodeCamera)
    {
        std::cout << "camera manager failed to start, code " << std::to_string(-errorCodeCamera) << std::endl;
        return true;
    }

    if (m_CameraManager->cameras().size() == 0)
    {
        std::cout << "no cameras available" << std::endl;
        return true;
    }

    cam_id = m_CameraManager->cameras()[0]->id();
    m_Camera = m_CameraManager->get(cam_id);
    if (!m_Camera)
    {
        std::cout << "failed to find camera" << cam_id << std::endl;
        return true;
    }
    
    std::cout << "Acquired camera: " << cam_id << std::endl;

    if (m_Camera->acquire())
    {
        std::cout << "failed to acquire camera" << cam_id << std::endl;
        return true;
    }
    camera_acquired_ = true;

	//File ist emty
	// if (!options_->post_process_file.empty())
	// 	post_processor_.Read(options_->post_process_file);
	// The queue takes over ownership from the post-processor.
	post_processor_.SetCallback(
		[this](CompletedRequestPtr &r) { this->msg_queue_.Post(Msg(MsgType::RequestComplete, std::move(r))); });

	return false; 
}

bool Camera::CameraOpenConfigureStill()
{
    using namespace libcamera;

	// 1. Open Camera 
    if (CameraOpen())
        return true; 

	//2. Config Stillmode
    std::cout << "camera configuration for Still capture..." << std::endl;

	StreamRoles stream_roles;
	stream_roles = { StreamRole::StillCapture, StreamRole::Raw };
	m_Configuration = m_Camera->generateConfiguration(stream_roles);
	if (!m_Configuration)
    {
        std::cout << "failed to generate still capture configuration" << std::endl;
        return true;
    }
        
	//default settings for still capture 
	m_Configuration->at(0).pixelFormat = libcamera::formats::YUV420;
    m_Configuration->at(0).colorSpace = libcamera::ColorSpace::Jpeg;

    //ToDo: Hardcoded width hidth. 
    m_Configuration->at(0).size.width = 2592;
    m_Configuration->at(0).size.height = 1944;

	post_processor_.AdjustConfig("still", &m_Configuration->at(0));

    //ToDo: Add deNoise and Transform Option
    // m_Configuration->transform = options_->transform;
	// configureDenoise(options_->denoise == "auto" ? "cdn_hq" : options_->denoise);

	if(setupCapture())
    {
        std::cout << "Error setupCature faild!" << std::endl;
        return true; 
    }

    streams_["still"] = m_Configuration->at(0).stream();

	post_processor_.Configure();

    //ToDo: Ausgabe 
	std::cout << "Still capture setup complete" << std::endl;
    
    return false; 
}

 bool Camera::setupCapture()
 {
     using namespace libcamera;
     // First finish setting up the configuration.
     CameraConfiguration::Status validation = m_Configuration->validate();
     if (validation == CameraConfiguration::Invalid)
     {
        std::cout << "failed to valid stream configurations" << std::endl;
        return true;
     }
     else if (validation == CameraConfiguration::Adjusted)
        std::cout << "Stream configuration adjusted" << std::endl;
     
     if (m_Camera->configure(m_Configuration.get()) < 0)
     {
        std::cout << "failed to configure streams" << std::endl;
        return true; 
     }

    //ToDO: Ausgabe 
    std::cout << "Camera streams configured" << std::endl;

     // Next allocate all the buffers we need, mmap them and store them on a free list.

     allocator_ = new FrameBufferAllocator(m_Camera);
     for (StreamConfiguration &config : *m_Configuration)
     {
         Stream *stream = config.stream();

         if (allocator_->allocate(stream) < 0)
         {
              std::cout << "failed to allocate capture buffers" << std::endl;
              return true; 
         }

         for (const std::unique_ptr<FrameBuffer> &buffer : allocator_->buffers(stream))
         {
	        // "Single plane" buffers appear as multi-plane here, but we can spot them because then
			// planes all share the same fd. We accumulate them so as to mmap the buffer only once.
			size_t buffer_size = 0;
			for (unsigned i = 0; i < buffer->planes().size(); i++)
			{
				const FrameBuffer::Plane &plane = buffer->planes()[i];
				buffer_size += plane.length;
				if (i == buffer->planes().size() - 1 || plane.fd.get() != buffer->planes()[i + 1].fd.get())
				{
					void *memory = mmap(NULL, buffer_size, PROT_READ | PROT_WRITE, MAP_SHARED, plane.fd.get(), 0);
					mapped_buffers_[buffer.get()].push_back(
						libcamera::Span<uint8_t>(static_cast<uint8_t *>(memory), buffer_size));
					buffer_size = 0;
				}
			}
			frame_buffers_[stream].push(buffer.get());
         }
	}
        //ToDo: Ausgabe.
		std::cout << "Buffers allocated and mapped" << std::endl;

	// The requests will be made when StartCamera() is called.
     return false;
 }

std::vector<libcamera::Span<uint8_t>> Camera::Mmap(libcamera::FrameBuffer *buffer) const
{
	auto item = mapped_buffers_.find(buffer);
	if (item == mapped_buffers_.end())
		return {};
	return item->second;
}

void Camera::makeRequests()
{
    using namespace libcamera;
    std::cout << "Eintritt ins Request" << std::endl;
    std::map<Stream *, std::queue<FrameBuffer *>> free_buffers(frame_buffers_);
	// auto free_buffers(frame_buffers_);
    while (true)
	{
		for (StreamConfiguration &config : *m_Configuration)
		{
			Stream *stream = config.stream();
			if (stream == m_Configuration->at(0).stream())
			{
				if (free_buffers[stream].empty())
				{
                    // ToDo: Debug Option anpassen false?
					std::cout << "Requests created" << std::endl;
					return;
				}
				std::unique_ptr<Request> request = m_Camera->createRequest();
				if (!request)
                    std::cout << "failed to make request" << std::endl;
                requests_.push_back(std::move(request));
			}
			else if (free_buffers[stream].empty())
                std::cout << "concurrent streams need matching numbers of buffers" << std::endl; 

            FrameBuffer *buffer = free_buffers[stream].front();
			free_buffers[stream].pop();
			if (requests_.back()->addBuffer(stream, buffer) < 0)
                std::cout << "failed to add buffer to request" << std::endl; 
		}
	}
}

bool Camera::CameraStarten()
{
    using namespace libcamera;
    makeRequests();

	// Siehe verbose outpute es gibbt keine Output: Using crop
    // // Build a list of initial controls that we must set in the camera before starting it.
    // // We don't overwrite anything the application may have set before calling us.
	// if (!controls_.contains(controls::ScalerCrop) && roi_width != 0 && roi_height != 0)
	// {
	// 	Rectangle sensor_area = m_Camera->properties().get(properties::ScalerCropMaximum);
	// 	int x = roi_x * sensor_area.width;
	// 	int y = roi_y * sensor_area.height;
	// 	int w = roi_width * sensor_area.width;
	// 	int h = roi_height * sensor_area.height;
	// 	Rectangle crop(x, y, w, h);
	// 	crop.translateBy(sensor_area.topLeft());
	// 	if (true)
	// 		std::cout << "Using crop " << crop.toString() << std::endl;
	// 	controls_.set(controls::ScalerCrop, crop);
	// }

	// Framerate is a bit weird. If it was set programmatically, we go with that, but
	// otherwise it applies only to preview/video modes. For stills capture we set it
	// as long as possible so that we get whatever the exposure profile wants.
	if (!controls_.contains(controls::FrameDurationLimits))
	{
		if (StillStream())
		   controls_.set(controls::FrameDurationLimits, { INT64_C(100), INT64_C(1000000000) });
			//controls_.set(controls::FrameDurationLimits, { INT64_C(33333), INT64_C(33333) });
		// ToDo: Hardcoded default framerate : 30
		else if (30 > 0)
		{
			int64_t frame_time = 1000000 / 30; // in us
			controls_.set(controls::FrameDurationLimits, { frame_time, frame_time });
		}
	}
	// ToDo: Hardcoded default Options!
	if (!controls_.contains(controls::Saturation))
		controls_.set(controls::Saturation, 1);
	if (!controls_.contains(controls::Contrast))
		controls_.set(controls::Contrast, 1);
	if (!controls_.contains(controls::Sharpness))
		controls_.set(controls::Sharpness, 1);
	if (!controls_.contains(controls::ExposureTime) && 0)
		controls_.set(controls::ExposureTime, 0);
	if (!controls_.contains(controls::AeExposureMode))
		controls_.set(controls::AeExposureMode, 0);
	if (!controls_.contains(controls::AeMeteringMode))
		controls_.set(controls::AeMeteringMode, 0);
	if (!controls_.contains(controls::AnalogueGain) && 0)
		controls_.set(controls::AnalogueGain, 0);
	if (!controls_.contains(controls::ExposureValue))
		controls_.set(controls::ExposureValue, 0);
	if (!controls_.contains(controls::AwbMode))
		controls_.set(controls::AwbMode, 0);
	// if (!controls_.contains(controls::ColourGains) && 0)
	// 	controls_.set(controls::ColourGains, { 0, 0 });
	if (!controls_.contains(controls::Brightness))
		controls_.set(controls::Brightness, 0);

	 post_processor_.Start();

	if (m_Camera->start(&controls_))
	{
		std::cout << "failed to start camera" << std::endl;
		return true; 
	}

	controls_.clear();
	camera_started_ = true;
	last_timestamp_ = 0;

	// Request to libcamera 
	 m_Camera->requestCompleted.connect(this, &Camera::requestComplete);

	for (std::unique_ptr<Request> &request : requests_)
	{
		if (m_Camera->queueRequest(request.get()) < 0)
		{
			std::cout << "Failed to queue request" << std::endl;
			return true; 
		}
	}

	std::cout << "Camera started!" << std::endl;
    return false; 
}

void Camera::requestComplete(libcamera::Request *request)
{
	using namespace libcamera; 
	if (request->status() == Request::RequestCancelled)
		return;

	CompletedRequest *r = new CompletedRequest(sequence_++, request);
	CompletedRequestPtr payload(r, [this](CompletedRequest *cr) { this->queueRequest(cr); });
	{
		std::lock_guard<std::mutex> lock(completed_requests_mutex_);
		completed_requests_.insert(r);
	}

	//We calculate the instantaneous framerate in case anyone wants it.
	uint64_t timestamp = payload->buffers.begin()->second->metadata().timestamp;
	if (last_timestamp_ == 0 || last_timestamp_ == timestamp)
		payload->framerate = 0;
	else
		payload->framerate = 1e9 / (timestamp - last_timestamp_);
	last_timestamp_ = timestamp;

	std::cout << "requestComplete durchgeführt" << std::endl; 
	post_processor_.Process(payload); // post-processor can re-use our shared_ptr
}

void Camera::queueRequest(CompletedRequest *completed_request)
{
	using namespace libcamera; 
	libcamera::Request::BufferMap buffers(std::move(completed_request->buffers));

	Request *request = completed_request->request;
	delete completed_request;
	assert(request);

	// This function may run asynchronously so needs protection from the
	// camera stopping at the same time.
	std::lock_guard<std::mutex> stop_lock(camera_stop_mutex_);
	if (!camera_started_)
		return;

	// An application could be holding a CompletedRequest while it stops and re-starts
	// the camera, after which we don't want to queue another request now.
	{
		std::lock_guard<std::mutex> lock(completed_requests_mutex_);
		auto it = completed_requests_.find(completed_request);
		if (it == completed_requests_.end())
			return;
		completed_requests_.erase(it);
	}

	for (auto const &p : buffers)
	{
		if (request->addBuffer(p.first, p.second) < 0)
			std::cout << "failed to add buffer to request in QueueRequest" << std::endl;
	}

	{
		std::lock_guard<std::mutex> lock(control_mutex_);
		request->controls() = std::move(controls_);
	}

	if (m_Camera->queueRequest(request) < 0)
		std::cout << "failed to queue request" << std::endl;

	// std::cout << "queueRequest durchgeführt" << std::endl; 
}

libcamera::Stream *Camera::StillStream(StreamInfo *info) const
{
	return GetStream("still", info);
}

StreamInfo Camera::GetStreamInfo(libcamera::Stream const *stream) const
{
	libcamera::StreamConfiguration const &cfg = stream->configuration();
	StreamInfo info;
	info.width = cfg.size.width;
	info.height = cfg.size.height;
	info.stride = cfg.stride;
	info.pixel_format = stream->configuration().pixelFormat;
	info.colour_space = stream->configuration().colorSpace;
	return info;
}

libcamera::Stream *Camera::GetStream(std::string const &name, StreamInfo *info) const
{
	auto it = streams_.find(name);
	if (it == streams_.end())
		return nullptr;
	if (info)
		*info = GetStreamInfo(it->second);
	return it->second;
}

//Still capture mode save a jpeg and quit 
bool Camera::TakePicture(std::string namejpg)
{
	Msg msg = msg_queue_.Wait();
	if (msg.type == MsgType::Quit)
	{
		return false; //Fehler 
	}	
	else if (msg.type != MsgType::RequestComplete)
	{
		std::cout << " error: unrecognised message!" << std::endl;
		return true; 
	}

	CameraStoppen();
	std::cout << "Still capture image received" << std::endl;
	libcamera::Stream *stream = StillStream();
	StreamInfo info = GetStreamInfo(stream);
	CompletedRequestPtr &payload = std::get<CompletedRequestPtr>(msg.payload);
	const std::vector<libcamera::Span<uint8_t>> mem = Mmap(payload->buffers[stream]);
	jpeg_save(mem, info, payload->metadata, namejpg, m_Camera->id());
	return false; 
}

bool Camera::CameraStoppen()
{
	{
		// We don't want QueueRequest to run asynchronously while we stop the camera.
		std::lock_guard<std::mutex> lock(camera_stop_mutex_);
		if (camera_started_)
		{
			if (m_Camera->stop())
			{
				std::cout << "error: failed to stop camera" << std::endl;
				return true; 
			}
			post_processor_.Stop();
			camera_started_ = false;
		}
	}

	if (m_Camera)
		m_Camera->requestCompleted.disconnect(this, &Camera::requestComplete);

	// An application might be holding a CompletedRequest, so queueRequest will get
	// called to delete it later, but we need to know not to try and re-queue it.
	completed_requests_.clear();
	msg_queue_.Clear();
	requests_.clear();
	controls_.clear(); // no need for mutex here
	std::cerr << "Camera stopped!" << std::endl;
    return false; 
}

void Camera::Teardown()
{
	post_processor_.Teardown();

	std::cerr << "Tearing down requests, buffers and configuration" << std::endl;

	for (auto &iter : mapped_buffers_)
	{
		// assert(iter.first->planes().size() == iter.second.size());
		// for (unsigned i = 0; i < iter.first->planes().size(); i++)
		for (auto &span : iter.second)
			munmap(span.data(), span.size());
	}
	mapped_buffers_.clear();

	delete allocator_;
	allocator_ = nullptr;

	m_Configuration.reset();

	frame_buffers_.clear();

	streams_.clear();
}