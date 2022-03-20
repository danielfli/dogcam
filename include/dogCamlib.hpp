#pragma once 
#include "../src/Vision.hpp"
#include <iostream>

class dogCamApp
{
public:
    dogCamApp();
    ~dogCamApp();

    // true -> Error
    bool TakePicture(std::string name);

    bool TakeVideo(std::string name); 

    // ToDo: add features
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
};
