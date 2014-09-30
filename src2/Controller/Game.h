#ifndef __GAME_H__
#define __GAME_H__

#include "syslibs.h"
#include "GraphicsModule.h"
#include "EventHandler.h"
#include "TTFmodule.h"
#include "AudioModule.h"
#include "ResourceManager.h"
#include "Tools.h"

#define PROJECT_PATH	"/home/guicc/Documents/Development/JutsuBattle/"            //TODO: Ler de um arquivo de configuracao
#define makePath(p)		s.assign(PROJECT_PATH).append(p)

class Game
{
private:
	GraphicsModule *graphics;   //TODO: unir todos elementos visuais e auditivos aqui

	ResourceManager *resources;
    std::queue<Renderable*> renderQ;
	bool running;

	FILE *ferr;
	FILE *fout;

public:
    Game();
	~Game();


	void mainLoop();
	void addToQueue(Renderable *obj_);
	void render();
	void logic();
	void init();

	GraphicsModule* getGraphics();
	ResourceManager* getResourceManager();

	static void reportError(const char *err_);
	static void writeToOutput(const char *out_);
};

extern Game *controller;

#endif
