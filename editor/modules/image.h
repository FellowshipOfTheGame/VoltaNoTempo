#ifndef _IMAGE_H_
#define _IMAGE_H_

#define MAX_IMG 30

using namespace std;

#include <iostream>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Image {
private:
    string img_path;
    string tile_base_filename;
    string default_base_filename;
    string format;
    int roll;
    std::vector<SDL_Surface*> img_surface;
    bool bmp;

    bool isBMP(string str);
    string getImageSource(string base, int roll, int number);

    // parameters : 
    // >> base --> base file name
    // >> roll --> roll of the image [0,2]
    // >> number --> number [0,9]
    SDL_Surface *loadImage(string base, int roll, int number);

    SDL_Surface** getTileImage(int number);
    SDL_Surface** getTileImage(int number, int roll);
    SDL_Surface** getDefaultImage(int number);


public:
    Image();
    ~Image();

    SDL_Surface** getImage(int number, int roll);
    int nextRoll(int roll);
    int lastRoll(int roll);

};

#endif
