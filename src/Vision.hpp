#pragma once 
#include "Camera.hpp"


class Vision 
{
public:
    Vision();
    ~Vision();

    bool StartUpCamera();

    bool TakePicture();

private:
    Camera camera{};
};
