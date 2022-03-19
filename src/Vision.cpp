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

     countPicture++; 

     name += ".";
     name += GetTimestamp();
     name += std::to_string(countPicture);
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

bool Vision::ConfigStillMode()
{
    //ToDo: camera kann bisher nur eine Standbild aufnahme  
    return true;
}

std::string Vision::GetTimestamp()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);
    // // print various components of tm structure.
    // cout << "Year:" << 1900 + ltm->tm_year << endl;
    // cout << "Month: " << 1 + ltm->tm_mon << endl;
    // cout << "Day: " << ltm->tm_mday << endl;
    // cout << "Time: " << 5 + ltm->tm_hour << ":";
    // cout << 30 + ltm->tm_min << ":";
    // cout << ltm->tm_sec << endl;

    std::string timestamp = "";
    timestamp  = std::to_string(ltm->tm_mday);
    timestamp += std::to_string(1 + ltm->tm_mon);
    timestamp += std::to_string(1900 + ltm->tm_year);
    timestamp += "_";
    // timestamp += to_string(5 + ltm->tm_hour);
    // timestamp += to_string(30 + ltm->tm_min);
    // timestamp += to_string(ltm->tm_sec);

    return timestamp;
}