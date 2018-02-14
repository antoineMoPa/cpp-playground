#include <iostream>
#include "CImg.h"
#include <experimental/filesystem>
#include <string>

namespace fs = std::experimental::filesystem;
using namespace cimg_library;

int main(int argc, char ** argv){
    CImg<unsigned char> ones(15,15,1,3,255);
    
    for(char letter = 'a'; letter <= 'z'; letter++){
        CImg<int> letter_tot(15,15,1,3,0);
        CImg<unsigned char> letter_avg(15,15,1,3,0);
        int image_count = 0;
        
        for(auto& p: fs::directory_iterator("set/fonts")){
            std::string path = p.path().string() + "/"+letter+".png";
            
            if(fs::exists(path)){
                std::cout << "Opening: " << path << std::endl;
                CImg<unsigned char> current_image(path.c_str());
                
                current_image.resize(15,15,1,3,0, 1, 0.5, 0.5);
                current_image = ones - current_image;
                
                letter_tot += current_image;
                image_count++;
                
                //CImgDisplay display(letter_tot.resize(15, 15));
                //pause();
                //break;
            }
        }
        
        letter_avg = letter_tot / image_count;
        letter_avg.save_png((std::string("results/") + letter + "_avg.png").c_str());
        
    }
    
    return 0;
}





