#pragma once

#include <sys/mman.h>

#include <condition_variable>
#include <iostream>
#include <memory>
#include <mutex>
#include <queue>
#include <set>
#include <string>
#include <thread>
#include <variant>

#include <libcamera/base/span.h>
#include <libcamera/camera.h>
#include <libcamera/camera_manager.h>
#include <libcamera/control_ids.h>
#include <libcamera/controls.h>
#include <libcamera/formats.h>
#include <libcamera/framebuffer_allocator.h>
#include <libcamera/property_ids.h>
#include <libcamera/color_space.h>
#include <libcamera/pixel_format.h>

#include "completed_request.hpp"
#include "post_processor.hpp"
#include "stream_info.hpp"

// Minmal copy of libcamera-app 
// Init camera + take picture + take video 
class Camera
{
public:
    enum class MsgType
    {
        RequestComplete,
        Quit
    }; 
    typedef std::variant<CompletedRequestPtr> MsgPayload;
    struct Msg
    {
        Msg(MsgType const &t) : type(t) {}

        template <typename T>
        Msg(MsgType const &t, T p) : type(t), payload(std::forward<T>(p))
        {
        }
        
        MsgType type;
        MsgPayload payload;
    };
    
    Camera();
    ~Camera();

    bool CameraOpen();
    void CameraClose();

    //Config für Standbild aufnahme
    bool CameraOpenConfigureStill();

    bool CameraStarten();

    bool CameraStoppen();

    //Bild aufnahme für ein Standbild 
    bool TakePicture(std::string namejpg);

    void Teardown();

    libcamera::Stream *StillStream(StreamInfo *info = nullptr) const;
    StreamInfo GetStreamInfo(libcamera::Stream const *stream) const;
    libcamera::Stream *GetStream(std::string const &name, StreamInfo *info = nullptr) const;
    Msg Wait();

    private:
        template <typename T>
        class MessageQueue
        {
        public:
            template <typename U>
            void Post(U &&msg)
            {
                std::unique_lock<std::mutex> lock(mutex_);
                queue_.push(std::forward<U>(msg));
                cond_.notify_one();
            }

            T Wait()
            {
                std::unique_lock<std::mutex> lock(mutex_);
                cond_.wait(lock, [this] { return !queue_.empty(); });
                T msg = std::move(queue_.front());
                queue_.pop();
                return msg;
            }
            
            void Clear()
            {
                std::unique_lock<std::mutex> lock(mutex_);
                queue_ = {};
            }

        private:
            std::queue<T> queue_;
            std::mutex mutex_;
            std::condition_variable cond_;
        };

        MessageQueue<Msg> msg_queue_;
        std::unique_ptr<libcamera::CameraManager> m_CameraManager;
        std::shared_ptr<libcamera::Camera> m_Camera;
        std::unique_ptr<libcamera::CameraConfiguration> m_Configuration;
        std::map<libcamera::Stream *, std::queue<libcamera::FrameBuffer *>> frame_buffers_;
        std::vector<std::unique_ptr<libcamera::Request>> requests_;
        libcamera::FrameBufferAllocator *allocator_ = nullptr;
        std::map<libcamera::FrameBuffer *, std::vector<libcamera::Span<uint8_t>>> mapped_buffers_;
        std::map<std::string, libcamera::Stream *> streams_;

        std::set<CompletedRequest *> completed_requests_;

        std::mutex camera_stop_mutex_;
        std::mutex completed_requests_mutex_;

        // For setting camera controls.
        std::mutex control_mutex_;
        libcamera::ControlList controls_;

        
        int errorCodeCamera;
        std::string cam_id;
        bool camera_acquired_ = false;
        float roi_x, roi_y, roi_width, roi_height;
        bool camera_started_ = false;
        uint64_t last_timestamp_;
        uint64_t sequence_ = 0;
        void makeRequests();
        bool setupCapture();
        void requestComplete(libcamera::Request * request);
	    void queueRequest(CompletedRequest *completed_request);
        std::vector<libcamera::Span<uint8_t>> Mmap(libcamera::FrameBuffer *buffer) const;

        void ConfigureViewfinder(); 
        PostProcessor post_processor_;
};
