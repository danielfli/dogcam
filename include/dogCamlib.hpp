#pragma once 
#include "../src/Vision.hpp"
// #include "../src/camera/Camera.hpp"

#include <iostream>

class dogCamApp
{
public:
    dogCamApp();
    ~dogCamApp();

    // true -> Error
    bool TakePicture(std::string name);

    /* fehlende Funktionen
        - Video()
        - Webcame()
        - Sound()
        - dogCamEnv() //environment

        environment:
        - video Bilder hochladen 
        - 
    */
    

private:
     Vision vision;
    // Camera myCamera{};
};
