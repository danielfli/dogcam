#include "Vision.hpp"

Vision::Vision() 
{
    if (CameraOpen())
    {
        Error = "Init Camera has Errors!";
    }
    else
    {
        camera_acquired_ = true;
    }
}

Vision::~Vision()
{
    if (!Error.empty())
    {
        std::cout << "Class Vison has Error: " << Error << std::endl; 
    }
}

bool Vision::CameraOpen()
{
    return camera.CameraOpen();
}

bool Vision::CameraOpenforStillmode()
{
    return camera.CameraOpenConfigureStill();
}

bool Vision::ConfigStillMode()
{
    return camera.CameraConfigureStill();
}

bool Vision::TakePicture(std::string name)
{
    std::cout << "DogCam Vision starting..." << std::endl;

    if(camera_acquired_)
    {
        if (ConfigStillMode())
            return true; //fehler
    }
    else
    {
        std::cout << "Error! Taken Piture." << std::endl;
    }

     if (CameraStart())
        return true; // fehler

     name += ".";
     name += GetTimestamp();
     name += std::to_string(countPicture++);
     name += ".jpeg";

     std::cout << "Name der JPEG: " << name << std::endl;
     if (camera.TakePicture(name))
       return true; // fehler

    if(CameraCleanUp())
        return true;

     return false; 
}

bool Vision::CameraCleanUp()
{
     if (camera.CameraStoppen())
        return true;
    camera.Teardown();

    return false;
}

bool Vision::CameraStart()
{
    return camera.CameraStarten();
}



std::string Vision::GetTimestamp()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);
    std::string timestamp = "";
    timestamp  = std::to_string(ltm->tm_mday);
    timestamp += std::to_string(1 + ltm->tm_mon);
    timestamp += std::to_string(1900 + ltm->tm_year);
    timestamp += "_";
    return timestamp;
}