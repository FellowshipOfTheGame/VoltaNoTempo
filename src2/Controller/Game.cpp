#include "Game.h"
#include "SDLmodule.h"

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
	running = false;
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

void Game::init()
{
	}

void Game::mainLoop()
{
	EventCode eventCode;
	EventType eventType;

	//Initialization
    running = engine->init();
    //engine->startTimer();

	while(running)
	{
		engine->pollEvent(&eventType, &eventCode);

		if(eventType == KEYUP)
		{
			if(eventCode == KEY_ESC)
				running = false;
		}

		logic();

		if(engine->shouldRender())
		{
			render();
			engine->updateContext();
		}
        
        //Game::writeToOutput("running\n");
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


