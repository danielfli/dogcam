#include "Camera.hpp"

Camera::Camera(/* args */) 
    : m_CameraManager(std::make_unique<libcamera::CameraManager>()), errorCodeCamera(0) 
{
}

Camera::~Camera()
{
    m_Camera.reset();
    m_CameraManager.reset();
}

bool Camera::CameraOpen()
{
    errorCodeCamera = m_CameraManager->start();
    if(errorCodeCamera)
    {
        std::cout << "camera manager failed to start, code " << std::to_string(-errorCodeCamera) << std::endl;
        return false;
    }

    if (m_CameraManager->cameras().size() == 0)
    {
        std::cout << "no cameras available" << std::endl;
        return false;
    }
    cam_id = m_CameraManager->cameras()[0]->id();
    m_Camera = m_CameraManager->get(cam_id);
    if (!m_Camera)
    {
        std::cout << "failed to find camera" << cam_id << std::endl;
        return false;
    }
    std::cout << "Get camera: " << cam_id << std::endl;

    if (m_Camera->acquire())
    {
        std::cout << "failed to acquire camera" << cam_id << std::endl;
        return false;
    }

    return errorCodeCamera == 0 ? true : false;
}

// bool Camera::CameraStarten();
// bool Camera::CameraStoppen();