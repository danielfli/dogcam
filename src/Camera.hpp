#pragma once

#include <iostream>
#include <memory>

#include <libcamera/base/span.h>
#include <libcamera/camera.h>
#include <libcamera/camera_manager.h>
#include <libcamera/control_ids.h>
#include <libcamera/controls.h>
#include <libcamera/formats.h>
#include <libcamera/framebuffer_allocator.h>
#include <libcamera/property_ids.h>

// Minmal copy of libcamera-app camera_manager verwenden 
// Init camera + take picture + take video 
class Camera
{
private:
    std::unique_ptr< libcamera::CameraManager> m_CameraManager;
    std::shared_ptr<libcamera::Camera> m_Camera;
    int errorCodeCamera;
    std::string cam_id;

public:
    Camera(/* args */);
    ~Camera();

    bool CameraOpen();

    // bool CameraStarten();
    // bool CameraStoppen();


};


