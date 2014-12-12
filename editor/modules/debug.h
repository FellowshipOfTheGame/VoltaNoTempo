#ifndef _DEBUG_H_
#define _DEBUG_H_

using namespace std;

#include <iostream>
#include <string>

class Debug {
private:
    bool show;
    int mode;

public:
    Debug();
    ~Debug();
    void selectMode(int mode);
    void printMessage(string message, string tag);
    void saveInFile(string message, string tag);
    void setShow(bool show);
    bool isShowing();
};


#endif
