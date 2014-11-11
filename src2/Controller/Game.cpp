#include "Game.h"
#include "../View/SDLmodule.h"
#include "../Model/Player.h"
#include "../View/SDLmodule.h"
    
Game::Game()
{
	char buff[256];
	time_t rawTime;

	ferr = fopen("stderr.txt", "a+");
	fout = fopen("stdout.txt", "a+");

	dup2(fileno(fout), STDOUT_FILENO);
	dup2(fileno(ferr), STDERR_FILENO);

	time(&rawTime);
	sprintf(buff, "DATE: %s", ctime(&rawTime));
	fprintf(stderr, "%s", buff);
	fprintf(stdout, "%s", buff);

	engine = new SDL();

	resources = new ResourceManager();
	running = true;
}

Game::~Game()
{
	delete engine;
	delete resources;

	fprintf(stderr, "------------\n\n");
	fprintf(stdout, "------------\n\n");

	fclose(fout);
	fclose(ferr);
}

bool Game::init()
{
    return engine->init();
}

void Game::mainLoop()
{
	EventCode eventCode;
	EventType eventType;
    int screenWidth = engine->getGraphicsModule()->getScreenWidth();
    int screenHeight = engine->getGraphicsModule()->getScreenHeight();
    
	//Initialization
    levelZero = new Level();
    
    srand((unsigned)time(NULL));
    engine->startTimer();

	while(running)
	{
		engine->pollEvent(&eventType, &eventCode);

		if(eventType == KEYUP)
		{
			if(eventCode == KEY_ESC)
				running = false;
        }
        
        levelZero->handleEvents(eventType, eventCode);
		levelZero->logic();

		if(engine->shouldRender())
		{
            levelZero->render();
			render();
			engine->updateContext();
		}
	}

}

void Game::addToQueue(Renderable *obj_)
{
	renderQ.push(obj_);
}

void Game::logic()
{
    
}

void Game::render()
{
	engine->clear();

	while(!renderQ.empty())
	{
		Renderable *obj = renderQ.front();
		obj->render();
		renderQ.pop();
	}
}

void Game::reportError(const char *err_)
{
	fprintf(stderr, "%s", err_);
}

void Game::reportError(int errCode)
{
    fprintf(stderr, "%d", errCode);
}

void Game::writeToOutput(const char *out_)
{
	fprintf(stdout, "%s", out_);
}

Engine* Game::getEngine()
{
	return engine;
}

ResourceManager* Game::getResourceManager()
{
	return resources;
}

