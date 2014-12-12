#include "modules/debug.h"

Debug::Debug() {
    show = true;
}

Debug::~Debug() {

}

bool Debug::isShowing() {
    return this->show;
}

void Debug::setShow(bool show) {
    this->show = show;
}

void Debug::printMessage(string message, string tag) {
    if (show) {
        cout << tag << " | " << message << endl;
    }
}

void Debug::selectMode(int mode) {
    this->mode = mode;
}

void Debug::saveInFile(string message, string tag) {
    // TODO
}