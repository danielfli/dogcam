#include "../include/dogCamlib.hpp"
#include "Vision.hpp"

dogCamApp::dogCamApp()
{
}

dogCamApp::~dogCamApp()
{
}

bool dogCamApp::TakePicture(std::string name)
{
     if (vision.TakePicture(name))
       return true; // fehler

   return false;
}
