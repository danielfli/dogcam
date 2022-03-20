#include <iostream>
#include "dogCamlib.hpp"

using namespace std;

int main()
{
    dogCamApp app;

    int loop = 1; 
    while (loop)
    {
        std::cout << "Foto? press 1, break? press 0: "; 
        std::cin >> loop;
        if (loop == 1)        
            app.TakePicture("image");
    }

    return 0;
}
