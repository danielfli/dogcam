#pragma once 
// #include "../src/Vision.hpp"
#include "../src/Camera.hpp"

#include <iostream>


class dogCamApp
{
public:
    dogCamApp();
    ~dogCamApp();

    bool StartVision();
    

private:
    //  Vision vision;
    Camera myCamera{};
};
