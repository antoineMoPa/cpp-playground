#include <iostream>
#include "CImg.h"
#include <experimental/filesystem>
#include <string>

namespace fs = std::experimental::filesystem;
using namespace cimg_library;

int main(int argc, char ** argv){

    for(auto& p: fs::directory_iterator("set/fonts")){
        std::string path = p.path().string() + "/a.png";
        
        if(fs::exists(path)){
            std::cout << "Opening: " << path << std::endl;
            CImg<float> image(path.c_str());
            CImgDisplay main_disp(image);
        }
    }
    
    return 0;
}





