#include "Game.h"
#include "SDLmodule.h"
#include <fcntl.h>

Game::Game()
{
	char buff[256];
	time_t rawTime;

	/*ferr = fopen("stderr.txt", "a+");
	fout = fopen("stdout.txt", "a+");

	dup2(fileno(fout), STDOUT_FILENO);
	dup2(fileno(ferr), STDERR_FILENO);

	time(&rawTime);
	sprintf(buff, "DATE: %s", ctime(&rawTime));
	fprintf(stderr, "%s", buff);
	fprintf(stdout, "%s", buff);*/

	graphics = nullptr;

	resources = new ResourceManager();
	running = false;
}

Game::~Game()
{
	delete graphics;
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

	//init
	//...

	while(running)
	{
		/*eventHandler->pollEvent(&eventType, &eventCode);

		if(eventType == KEYUP)
		{
			if(eventCode == KEY_ESC)
				running = false;
		}

		logic();

		if(eventHandler->shouldRender())
		{
			render();
			graphics->updateContext();
		}*/
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
	graphics->clear();

	while(!renderQ.empty())
	{
		Renderable *obj = renderQ.front();
		obj->render();
		renderQ.pop();
	}
}

/*void Game::setGraphicsModule(Module module_, int screenWidth_, int screenHeight_)
{
	switch(module_)
	{
		case ALLEGRO_GFX:
			graphics = new AllegroGraphics();
			break;

		case SDL_GFX:
			graphics = new SDLgraphics();
			break;

		default:
			running = false;
			return;
	}

	graphics->setScreenSize(screenWidth_, screenHeight_);
	running = graphics->init();
}*/

void Game::reportError(const char *err_)
{
	fprintf(stderr, "%s", err_);
}

void Game::writeToOutput(const char *out_)
{
	fprintf(stdout, "%s", out_);
}

GraphicsModule* Game::getGraphics()
{
	return graphics;
}

ResourceManager* Game::getResourceManager()
{
	return resources;
}


