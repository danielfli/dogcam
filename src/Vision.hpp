#pragma once 

#include <string>

#include "camera/Camera.hpp"

class Vision 
{
public:
    Vision();
    ~Vision();

    bool CameraOpen();
    bool CameraOpenforStillmode();

    bool CameraStart();

    bool ConfigStillMode();

    bool TakePicture(std::string name); 

private:
    Camera camera{};
    bool camera_acquired_;
};
