#pragma once 

#include <string>

#include "camera/Camera.hpp"
#include <ctime>

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

    std::string GetTimestamp();

private:
    Camera camera{};
    bool camera_acquired_;
    bool CameraCleanUp();
    int countPicture{};
};
