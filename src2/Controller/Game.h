#ifndef __GAME_H__
#define __GAME_H__

#include "../syslibs.h"
#include "../View/Engine.h"
#include "../Utility/ResourceManager.h"
#include "../Utility/Tools.h"
#include "../Model/Player.h"
#include "../Model/Level.h"

#define PROJECT_PATH	"/home/guicc/Documents/FoG/VoltaNoTempo/"            //TODO: Ler de um arquivo de configuracao
#define makePath(p)		s.assign(PROJECT_PATH).append(p)

class Game
{
private:
	Engine *engine;
	ResourceManager *resources;
    std::queue<Renderable*> renderQ;
	bool running;
    
    Level *levelZero;

	FILE *ferr;
	FILE *fout;

public:
    Game();
	~Game();


	void mainLoop();
	void addToQueue(Renderable *obj_);
	void render();
	void logic();
	bool init();

	Engine* getEngine();
	ResourceManager* getResourceManager();

	static void reportError(const char *err_);
    static void reportError(int errCode);
	static void writeToOutput(const char *out_);
};

extern Game *controller;

#endif