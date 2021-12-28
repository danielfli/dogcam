#include "Vision.hpp"
#include "iostream"

Vision::Vision()
{
}

Vision::~Vision()
{
}

bool Vision::StartUpCamera()
{
    return camera.CameraOpen();
}