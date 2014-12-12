#include "modules/map.h"

/* --------      IMPORTANT     -----------        *
 * - IMAGE DIMENSION (SQUARE_SIZE X SQUARE_SIZE)  *
 * - DO NOT REMOVE ANY DEFINE -- JUST EDIT VALUES */

// DIMENSION OF IMG (ONE SIDE -- NOTE: IMAGE MUST HAVE A SQUARE DIMENSION)
#define FILE_SOURCE "file/map.bin"
#define UNDO_SOURCE "file/undo.bin"
#define REDO_SOURCE "file/redo.bin"

#define MAX_ROLL 3

// Constructor

Map::Map() {
    Map::startMatrix();
    mem.x = 0;
    mem.y = 0;

    view = new View();
    image = new Image();

    this->run = true;
}

// Destructor

Map::~Map() {
    delete view;
    view = NULL;
    delete image;
    image = NULL;
    this->run = false;
}

void Map::clear() {

    // map->cleanSelection();  // Clean selected tile
    view->clear();
}

void Map::startMatrix() {
    for (int i = 0; i < COL; i++) {
        for (int j = 0; j < LIN; j++) {
            map[i][j] = EMPTY;
        }
    }
}

void Map::quit() {
    this->run = false;
}

// Get if it is running

bool Map::isRunning() {
    return this->run;
}

// Set if it is running

void Map::setRunning(bool state) {
    this->run = state;
}

// Update view

void Map::update() {
    view->update();
}

// ### Save Methods ###

// save undo file

bool Map::saveUndo() {
    FILE *file = fopen(UNDO_SOURCE, "wb+");
    if (file == NULL) {
        cout << "Erro ao carregar arquivo -- save" << endl;
        return false;
    }

    //limpa_selecao();

    fwrite(map, COL * LIN * sizeof (int), 1, file);

    fclose(file);

    return true;
}

// save redo file

bool Map::saveRedo() {
    FILE *file = fopen(REDO_SOURCE, "wb+");
    if (file == NULL) {
        cout << "Erro ao carregar arquivo -- save" << endl;
        return false;
    }

    //limpa_selecao();

    fwrite(map, COL * LIN * sizeof (int), 1, file);

    fclose(file);
    return true;
}

bool Map::saveMap() {
    FILE *file = fopen(FILE_SOURCE, "wb+");
    if (file == NULL) {
        cout << "Erro ao carregar arquivo -- save" << endl;
        return false;
    }

    //limpa_selecao();

    map[mem.x][mem.y] = mem_value;

    fwrite(map, COL * LIN * sizeof (int), 1, file);

    fclose(file);
    return true;
}

// ### Load methods ###
// load redo file

bool Map::loadRedo() {
    FILE *file = fopen(REDO_SOURCE, "rb+");
    if (file == NULL) {
        cout << "Erro ao carregar arquivo -- load" << endl;
        return false;
    }
    fseek(file, 0, SEEK_END);
    if (ftell(file) < COL * LIN) {
        cout << "Erro - arquivo corrompido!" << endl;
        return false;
    }
    fseek(file, 0, SEEK_SET);

    fread(map, COL * LIN * sizeof (int), 1, file);

    fclose(file);
    return true;
}

// laod undo file

bool Map::loadUndo() {
    FILE *file = fopen(UNDO_SOURCE, "rb+");
    if (file == NULL) {
        cout << "Erro ao carregar arquivo -- load" << endl;
        return false;
    }
    fseek(file, 0, SEEK_END);
    if (ftell(file) < COL * LIN) {
        cout << "Erro - arquivo corrompido!" << endl;
        return false;
    }
    fseek(file, 0, SEEK_SET);

    fread(map, COL * LIN * sizeof (int), 1, file);

    fclose(file);

    return true;
}

//h = y = LIN

// w = x = COL

// Clean selection point

void Map::cleanSelection() {
    for (int i = 0; i < COL; i++) {
        for (int j = 0; j < LIN; j++) {
            if (map[i][j] == SELECT) {
                map[i][j] = EMPTY;
            }
        }
    }
}

SDL_Point Map::getSelection() {
    SDL_Point point;
    point.x = -1;
    point.y = -1;

    for (int i = 0; i < COL; i++) {
        for (int j = 0; j < LIN; j++) {
            if (map[i][j] == SELECT) {
                point.x = i;
                point.y = j;
                break;
            }
        }
    }
    return point;
}


// Set mouse on click point

SDL_Point Map::toMatrixPosition(SDL_Point mPosition) {


    mPosition.y -= view->getMenuSpace();
    mPosition.x /= SQUARE_SIZE;
    mPosition.y /= SQUARE_SIZE;

    map[mem.x][mem.y] = mem_value;
    mem_value = map[mPosition.x][mPosition.y];
    mem = mPosition;
    map[mPosition.x][mPosition.y] = SELECT;
    return mPosition;
}

void Map::matrixToImage() {
    SDL_Surface **ptr;

    mem.x = 0;
    mem.y = 0;

    view->clear();

    for (int i = 0; i < COL; i++) {
        for (int j = 0; j < LIN; j++) {
            ptr = image->getImage(map[i][j] % 10, map[i][j] / 10);
            if (ptr != NULL) {
                view->setImage(ptr, i*SQUARE_SIZE, j * SQUARE_SIZE);
            }
        }
    }
    view->update();
}

// -- SPECIAL FEATURES --

// Repeat selected image to every point right the selection

void Map::setRight(SDL_Point point, int value) {
    for (int i = point.x; i < COL; i++) {
        map[i][point.y] = value;
    }
}

// Repeat selected image to every point down the selection


// Apply to all tiles on the below

void Map::setBelow(SDL_Point point, int value) {
    for (int i = point.y; i < LIN; i++) {
        map[point.x][i] = value;
    }
}

// Apply to all tiles on the left

void Map::setLeft(SDL_Point point, int value) {
    for (int i = point.x; i >= 0; i--) {
        map[i][point.y] = value;
    }
}


// Apply to all tiles on the above

void Map::setAbove(SDL_Point point, int value) {
    for (int i = point.y; i >= 0; i--) {
        map[point.x][i] = value;
    }
}

// Apply to all tiles

void Map::setAll(int value) {
    for (int i = 0; i < COL; i++) {
        for (int j = 0; j < LIN; j++) {
            map[i][j] = value;
        }
    }
}
// Reset map[COL][LIN] with EMPTY

void Map::emptyMap() {
    Map::setAll(EMPTY);
}

// Fill map[COL][[LIN] with select image

void Map::fillMap() {
    setAll(mem_value);
}

void Map::saveMemoryValue(SDL_Point point) {
    mem_value = map[point.x][point.y]; // Save the value in the position map[x][y]
    mem = point;
}

SDL_Point Map::getMemoryPoint() {
    return mem;
}

int Map::getMemoryValue() {
    return mem_value;
}

void Map::loadMemoryValue(SDL_Point point) {
    map[point.x][point.y] = mem_value;
}

void Map::setMatrix(int x, int y, int value) {
    map[x][y] = value;
}

bool Map::loadMap() {
    FILE *file = fopen(FILE_SOURCE, "rb+");
    if (file == NULL) {
        printf("Erro ao carregar arquivo -- load\n");
        return false;
    }
    fseek(file, 0, SEEK_END);
    if (ftell(file) < COL * LIN) {
        printf("Erro - arquivo corrompido!\n");
        return false;
    }
    fseek(file, 0, SEEK_SET);

    fread(map, COL * LIN * sizeof (int), 1, file);

    fclose(file);

    return true;
}
