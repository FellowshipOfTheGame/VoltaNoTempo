
#include "Controller/Game.h"

Game *controller = new Game();

int main(int argc, char *argv[])
{
    bool initSuccess = true;
    
    initSuccess = controller->init();
    
    if(initSuccess)
        controller->mainLoop();
    
    return 0;
}
