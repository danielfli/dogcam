#pragma once 

#include <string>

#include "camera/Camera.hpp"
#include <ctime>

class Vision 
{
public:
    Vision();
    ~Vision();

    bool TakePicture(std::string name);
    bool TakeVideo(std::string name, int duration);

    
    
protected:

    bool CameraOpen();
    bool CameraOpenforStillmode();
    bool CameraStart();
    bool ConfigStillMode();


private:
    Camera camera{};
    bool camera_acquired_;
    std::string Error;
    int countPicture{};

    bool CameraCleanUp();
    std::string GetTimestamp();

};
