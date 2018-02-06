#include <iostream>
#include "CImg.h"

using namespace cimg_library;

int main(int argc, char ** argv){
    CImg<float> image("set/a.png");
    CImgDisplay main_disp(image);
    
    pause();
    
    return 0;
}





