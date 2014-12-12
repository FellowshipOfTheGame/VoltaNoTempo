#include "modules/image.h"
#include <stdio.h>

#define EXTRA_IMAGE 2
#define ROLL_SIZE 3


#define EXTRA_IMAGE 2

// Constructor

Image::Image() {
    img_path = "img/";
    tile_base_filename = "img_";
    default_base_filename = "extra_";
    format = "png";
    bmp = Image::isBMP(format);
    roll = 0;

    img_surface.reserve(MAX_IMG + EXTRA_IMAGE); // 32

    for (int i = 0; i < img_surface.size(); i++) {
        img_surface[i] = NULL;
        cout << "img_surface[" << i << "] = " << img_surface.at(i) << endl;
    }

    for (int i = 0; i < MAX_IMG; i++) {
        // cout << "i: " << i << endl;
        img_surface.push_back(loadImage(this->tile_base_filename, i / 10, i % 10));
    }

    for (int i = 0; i < EXTRA_IMAGE; i++) {
        // cout << "i: " << MAX_IMG+i << endl;
        img_surface.push_back(loadImage(this->default_base_filename, i / 10, i % 10));
    }

    if (img_surface.empty()) {
        cout << "size: " << img_surface.size() << endl;
    }

}

// Destructor

Image::~Image() {
    //bmp = return(this->format != "bmp")  -- string compare
    for (int i = 0; i < img_surface.size(); i++) {
        if (img_surface.at(i) != NULL) {
            SDL_FreeSurface(img_surface.at(i));
            img_surface[i] = NULL;
            // cout << "img_surface["<<i<< "] = " << img_surface.at(i) <<endl;
        }
    }
    img_surface.clear();
}

bool Image::isBMP(string str) {
    return (str.compare("bmp") == 0);
}

SDL_Surface* Image::loadImage(string base, int roll, int number) {
    string str = getImageSource(base, roll, number);
    if (!bmp) {
        return IMG_Load(str.c_str());
    }
    return SDL_LoadBMP(str.c_str());

}

int Image::nextRoll(int roll) {
    return (roll + 1) % ROLL_SIZE;
}

int Image::lastRoll(int roll) {
    if (roll == 0) {
        roll = ROLL_SIZE;
    }
    return (roll - 1);
}

// Parameters number [0,9]
// Return NULL if fail

SDL_Surface** Image::getTileImage(int number) {
    if (img_surface.size() < number) {
        cout << "Error getTileImg()1" << endl;
        return NULL;
    }

    return &img_surface.at(number + (roll * 10));
}

SDL_Surface** Image::getImage(int number, int roll) {
    return (number >= 0) ? Image::getTileImage(number, roll) : Image::getDefaultImage(number);
}

SDL_Surface** Image::getTileImage(int number, int roll) {
    if (img_surface.size() < number + (roll * 10)) {
        cout << "Error getTileImg()2" << endl;
        return NULL;
    }

    return &img_surface.at(number + (roll * 10));
}

// Parameters number [0,9]
// Return NULL if fail

SDL_Surface** Image::getDefaultImage(int number) {
    int aux = number;
    aux *= -1;
    aux += (MAX_IMG - 1);
    if (img_surface.size() < aux) {
        cout << "Error getDefaultImg()" << endl;
        return NULL;
    }
    // cout << "number : " << number << " aux: " << aux << endl;
    return &img_surface.at(aux);
}


// Roll - rolo de imagens de 0-9
// Number - número de 0-9 q foi escolhido
// return String with the correct path to find the img

std::string Image::getImageSource(string base, int roll, int number) {
    char c1 = (char) (((int) '0') + roll);
    char c2 = (char) (((int) '0') + number);

    // return img_path + base_filename + to_string(roll) + to_string(number) + '.' + format;	// Need c++11 (future use)

    // cout << "filename: " << (img_path + base + c1 + c2 + '.' + format) << endl;
    return img_path + base + c1 + c2 + '.' + format; // Path ready to load the image
}
