#ifndef _MAP_H_
#define _MAP_H_

#include "view.h"
#include "image.h"
#include "debug.h"
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>




using namespace std;

class Map {
private:
    bool run;
    int map[COL][LIN]; // Draw map
    SDL_Point mem; // Save mouse point
    int mem_value; // Save value to restore
    View *view;
    Image *image;

    void startMatrix();

public:
    Map(); // Constructor
    ~Map(); // Destructor

    void update(); // Update view
    void clear();
    bool isRunning();
    void setRunning(bool state);

    // Save
    bool saveUndo();
    bool saveRedo();
    bool saveMap();

    SDL_Point getMemoryPoint();

    // Load
    bool loadUndo();
    bool loadRedo();
    bool loadMap();

    void quit();

    // Set mouse on click point
    SDL_Point toMatrixPosition(SDL_Point mPosition);

    // Clean selection point
    void cleanSelection();

    SDL_Point getSelection();

    // Change image
    bool tradeImage(SDL_Surface **surface, string str);

    // Set image for every value of mapa[COL][LIN]
    void matrixToImage();
    // -- SPECIAL FEATURES --

    // Repeat selected image to every point right the selection
    void setRight(SDL_Point point, int value);

    // Repeat selected image to every point down the selection
    // Apply to all tiles on the below
    void setBelow(SDL_Point point, int value);

    // Apply to all tiles on the left
    void setLeft(SDL_Point point, int value);


    // Apply to all tiles on the above
    void setAbove(SDL_Point point, int value);

    // Apply to all tiles
    void setAll(int value);

    // Reset mapa[COL][LIN] with EMPTY
    void emptyMap();

    // Fill mapa[COL][[LIN] with select image
    void fillMap();

    void saveMemoryValue(SDL_Point point);

    void loadMemoryValue(SDL_Point point);

    void setMatrix(int x, int y, int value);

    int getMemoryValue();
};

#endif