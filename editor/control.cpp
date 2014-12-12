#include "modules/control.h"
#include "modules/image.h"

#define MAX_ROLL 3

Control::Control() {
    map = new Map();
    img = new Image();
    roll = 0;
    Control::loop();
}

Control::~Control() {
    delete map;
    map = NULL;
    delete img;
    img = NULL;
}

void Control::loop() {
    mPos.x = 0;
    mPos.y = 0;
    map->saveMemoryValue(mPos);
    Control::update(mPos.x, mPos.y, SELECT);

    while (map->isRunning()) {
        //Handle events on queue
        while (SDL_PollEvent(&event) != 0) {
            switch (event.type) {
                case SDL_QUIT:
                    map->quit();
                    break;

                case SDL_KEYDOWN:
                    Control::keyDown();
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    Control::mouseButtonDown();
                    break;

            }
        }
    }
}

void Control::keyDown() {
    switch (event.key.keysym.sym) {
        case SDLK_ESCAPE:
            map->quit();
            break;

        case SDLK_RIGHT:
            map->saveMemoryValue(mPos);
            if (map->getMemoryValue() == SELECT) {
                map->loadMemoryValue(mPos);
            }
            Control::moveRight();
            map->saveMemoryValue(mPos);
            break;

        case SDLK_LEFT:
            map->saveMemoryValue(mPos);
            if (map->getMemoryValue() == SELECT) {
                map->loadMemoryValue(mPos);
            }
            Control::moveLeft();
            map->saveMemoryValue(mPos);
            break;

        case SDLK_UP:
            map->saveMemoryValue(mPos);
            if (map->getMemoryValue() == SELECT) {
                map->loadMemoryValue(mPos);
            }
            Control::moveUp();
            map->saveMemoryValue(mPos);
            break;

        case SDLK_DOWN:
            map->saveMemoryValue(mPos);
            if (map->getMemoryValue() == SELECT) {
                map->loadMemoryValue(mPos);
            }
            Control::moveDown();
            map->saveMemoryValue(mPos);
            break;

        case SDLK_INSERT: // Reset mapa
            Control::save(MODE_UNDO);
            map->emptyMap();
            Control::update(mPos.x, mPos.y, SELECT);
            Control::save(MODE_REDO);
            break;
        case SDLK_DELETE:
            Control::save(MODE_UNDO);
            Control::update(mPos.x, mPos.y, EMPTY);
            Control::save(MODE_REDO);
            break;
        case SDLK_s:
            Control::save(MODE_MAP);
            cout << "Save Image" << endl;
            break;
        case SDLK_l:
            Control::save(MODE_UNDO);
            map->loadMap();
            Control::update(mPos.x, mPos.y, SELECT);
            cout << "Load Image" << endl;
            Control::save(MODE_REDO);
            break;
        case SDLK_0:
            Control::save(MODE_UNDO);
            Control::update(mPos.x, mPos.y, 0 + (10 * roll));
            map->saveMemoryValue(mPos);
            Control::save(MODE_REDO);
            break;
        case SDLK_1:
            Control::save(MODE_UNDO);
            Control::update(mPos.x, mPos.y, 1 + (10 * roll));
            map->saveMemoryValue(mPos);
            Control::save(MODE_REDO);
            break;
        case SDLK_2:
            Control::save(MODE_UNDO);
            Control::update(mPos.x, mPos.y, 2 + (10 * roll));
            map->saveMemoryValue(mPos);
            Control::save(MODE_REDO);
            break;

        case SDLK_3:
            Control::save(MODE_UNDO);
            Control::update(mPos.x, mPos.y, 3 + (10 * roll));
            map->saveMemoryValue(mPos);
            Control::save(MODE_REDO);
            break;

        case SDLK_4:
            Control::save(MODE_UNDO);
            Control::update(mPos.x, mPos.y, 4 + (10 * roll));
            map->saveMemoryValue(mPos);
            Control::save(MODE_REDO);
            break;

        case SDLK_5:
            Control::save(MODE_UNDO);
            Control::update(mPos.x, mPos.y, 5 + (10 * roll));
            map->saveMemoryValue(mPos);
            Control::save(MODE_REDO);
            break;
        case SDLK_6:
            Control::save(MODE_UNDO);
            Control::update(mPos.x, mPos.y, 6 + (10 * roll));
            map->saveMemoryValue(mPos);
            Control::save(MODE_REDO);
            break;
        case SDLK_7:
            Control::save(MODE_UNDO);
            Control::update(mPos.x, mPos.y, 7 + (10 * roll));
            map->saveMemoryValue(mPos);
            Control::save(MODE_REDO);
            break;
        case SDLK_8:
            Control::save(MODE_UNDO);
            Control::update(mPos.x, mPos.y, 8 + (10 * roll));
            map->saveMemoryValue(mPos);
            Control::save(MODE_REDO);
            break;
        case SDLK_9:
            Control::save(MODE_UNDO);
            Control::update(mPos.x, mPos.y, 9 + (10 * roll));
            map->saveMemoryValue(mPos);
            Control::save(MODE_REDO);
            break;

        case SDLK_RCTRL:
            roll = img->nextRoll(roll);

            std::cout << roll << std::endl;
            break;
        case SDLK_LCTRL:
            roll = img->lastRoll(roll);
            std::cout << roll << std::endl;

        case SDLK_RALT:
            roll++;
            roll %= MAX_ROLL;
            break;
        case SDLK_LALT:
            roll++;
            roll %= MAX_ROLL;
            roll = MAX_ROLL - roll;
            break;
            // special fill line with select img
        case SDLK_d:
            Control::save(MODE_UNDO);
            map->setBelow(mPos, map->getMemoryValue());
            Control::update(mPos.x, mPos.y, map->getMemoryValue());
            Control::save(MODE_REDO);
            break;
        case SDLK_u:
            Control::save(MODE_UNDO);
            map->setAbove(mPos, map->getMemoryValue());
            Control::update(mPos.x, mPos.y, map->getMemoryValue());

            Control::save(MODE_REDO);
            break;

            // special fill line with select img
        case SDLK_f:
            Control::save(MODE_UNDO);
            map->setRight(mPos, map->getMemoryValue());
            Control::update(mPos.x, mPos.y, map->getMemoryValue());

            Control::save(MODE_REDO);
            break;

        case SDLK_b:
            Control::save(MODE_UNDO);
            map->setLeft(mPos, map->getMemoryValue());
            Control::update(mPos.x, mPos.y, map->getMemoryValue());
            Control::save(MODE_REDO);
            break;

        case SDLK_a:
            Control::save(MODE_UNDO);
            map->setAll(map->getMemoryValue());
            Control::update(mPos.x, mPos.y, map->getMemoryValue());
            Control::save(MODE_REDO);
            break;
            // Load file

            // if (load_mapa(FILE_SOURCE)) {
            //     cout << "Load Image" << endl;
            //     save_undo();
            // }
            break;

            // Save file
            // limpa_selecao();
            //          if (save_mapa()) {
            //             	cout << "Save Image" << endl;
            //          }
            // Undo
            // limpa_selecao();
            //          if (save_mapa()) {
            //             	cout << "Save Image" << endl;
            //          }
            // Undo

        case SDLK_z:
            // if (load_undo()) {
            //     cout << "Undo" << endl;
            // }
            break;


            // Redo

            // Redo

        case SDLK_y:
            // if (load_redo()) {
            //     cout << "Redo" << endl;
            // }
            break;


    }
}

// Save without select image

void Control::save(int mode) {
    SDL_Point point;
    point.x = 0;
    point.y = 0;

    point = map->getSelection();
    map->cleanSelection(); // Clean selected tile
    switch (mode) {
        case MODE_UNDO:
            map->saveUndo();
            break;
        case MODE_REDO:
            map->saveRedo();
            break;
        case MODE_MAP:
            map->saveMap();
            break;
        default:
            return;

    }
    if (point.x > 0 && point.y > 0) { //Reset selection
        map->setMatrix(point.x, point.y, SELECT);
    }
}

void Control::mouseButtonDown() {
    map->loadMemoryValue(mPos);
    map->update();
    // map->setMatrix(mPos.x, mPos.y, EMPTY);
    //       map->update();

    mPos.x = event.motion.x;
    mPos.y = event.motion.y;

    map->saveMemoryValue(mPos);

    mPos = map->toMatrixPosition(mPos);
    Control::update(mPos.x, mPos.y, SELECT);

    map->cleanSelection(); // Clean selected tile
    Control::update(mPos.x, mPos.y, SELECT);
    map->loadMemoryValue(mPos);
    map->update();
    // cout << "x: " << mPos.x << " y: " << mPos.y << endl;
}

void Control::update(int x, int y, int value) {
    map->cleanSelection(); // Clean selected tile
    map->setMatrix(x, y, value);
    map->matrixToImage();
    map->update();
}

void Control::moveUp() {
    if (mPos.y != 0) {
        mPos.y--;
    } else {
        mPos.y = LIN - 1;
        if (mPos.x != 0) {
            mPos.x--;
        } else {
            mPos.x = COL - 1;
        }
    }

    map->saveMemoryValue(mPos);
    map->cleanSelection(); // Clean selected tile
    Control::update(mPos.x, mPos.y, SELECT);
    map->loadMemoryValue(mPos);
    map->update();
    // cout << "x: " << mPos.x << " y: " << mPos.y << endl;
}

void Control::moveDown() {
    if (mPos.y != LIN - 1) {
        mPos.y++;
    } else {
        mPos.y = 0;
        if (mPos.x != COL - 1) {
            mPos.x++;
        } else {
            mPos.x = 0;
        }
    }
    map->saveMemoryValue(mPos);
    map->cleanSelection(); // Clean selected tile
    Control::update(mPos.x, mPos.y, SELECT);
    map->loadMemoryValue(mPos);
    map->update();
    // cout << "x: " << mPos.x << " y: " << mPos.y << endl;
}

void Control::moveLeft() {
    if (mPos.x != 0) {
        mPos.x--;
    } else {
        mPos.x = COL - 1;
        if (mPos.y != 0) {
            mPos.y--;
        } else {
            mPos.y = LIN - 1;
        }
    }
    map->saveMemoryValue(mPos);
    map->cleanSelection(); // Clean selected tile
    Control::update(mPos.x, mPos.y, SELECT);
    map->loadMemoryValue(mPos);
    map->update();
    // cout << "x: " << mPos.x << " y: " << mPos.y << endl;
}

void Control::moveRight() {
    if (mPos.x != COL - 1) {
        mPos.x++;
    } else {
        mPos.x = 0;
        if (mPos.y != LIN - 1) {
            mPos.y++;
        } else {
            mPos.y = 0;
        }
    }
    map->saveMemoryValue(mPos);
    map->cleanSelection(); // Clean selected tile
    Control::update(mPos.x, mPos.y, SELECT);
    map->loadMemoryValue(mPos);
    map->update();
    // cout << "x: " << mPos.x << " y: " << mPos.y << endl;
}