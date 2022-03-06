#include "Vision.hpp"

Vision::Vision() 
    : camera_acquired_(false)
{
}

Vision::~Vision()
{
}

bool Vision::CameraOpen()
{
    return camera.CameraOpen();
}

bool Vision::CameraOpenforStillmode()
{
    return camera.CameraOpenConfigureStill();
}

bool Vision::TakePicture(std::string name)
{
    std::cout << "DogCam Vision starting..." << std::endl;
    if(!camera_acquired_)
    {
        if (CameraOpenforStillmode())
            return true; //fehler
        camera_acquired_ = true; 
    }
     if (CameraStart())
        return true; // fehler

     name += ".jpeg";
     std::cout << "Name der JPEG: " << name << std::endl;
     if (camera.TakePicture(name))
       return true; // fehler

    return false; 
}

bool Vision::CameraStart()
{
    return camera.CameraStarten();
}

bool Vision::ConfigStillMode()
{
    //ToDo: camera kann bisher nur eine Standbild aufnahme  
    return true;
}