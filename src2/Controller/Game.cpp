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
    
    //Load
    fontArial = resources->loadFontFromPath("img/Arial.ttf", "font-arial-16", 16);
    bgMusic = resources->loadAudioFromPath("img/music.ogg", "bg-music", MUSIC);
    
    spawnText = engine->getTTFmodule()->makeText("Press 'space' to spawn", fontArial, 128, 255, 128, 255);
    spawnText->setPosition(100, 50);
    
    bgMusic->play();
    //bgMusic->setVolume(0.5);

	//Initialization
    srand((unsigned)time(NULL));
    engine->startTimer();

	while(running)
	{
		engine->pollEvent(&eventType, &eventCode);

		if(eventType == KEYUP)
		{
			if(eventCode == KEY_ESC)
				running = false;
            else if(eventCode == KEY_SPACE)
            {
                spawnChar(rand()%screenWidth, rand()%(screenHeight-150));
            }
		}

		logic();

		if(engine->shouldRender())
		{
			render();
            spawnText->render();
			engine->updateContext();
		}
	}
    
    for(unsigned long i = 0; i < clones.size(); i++)
    {
        delete clones[i];
    }
    clones.clear();
    
    bgMusic->stop();
    delete bgMusic;
    delete fontArial;
    delete spawnText;
}

void Game::addToQueue(Renderable *obj_)
{
	renderQ.push(obj_);
}

void Game::logic()
{
    int screenWidth = engine->getGraphicsModule()->getScreenWidth();
    int screenHeight = engine->getGraphicsModule()->getScreenHeight();
    
    for(unsigned long i = 0; i < clones.size(); i++)
    {
        Player *p = clones[i];
        Dimension2D newPos = p->getPosition();
        
        //Apply gravity
        newPos.setPosition(newPos.getX(), newPos.getY()+2);
        
        if(newPos.getY() > screenHeight-150)
            newPos.setPosition(newPos.getX(), screenHeight-150);
        
        p->setPosition(newPos);
        
        //Add clone to drawing queue
        addToQueue(clones[i]->getSprite());
    }
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
	fprintf(stderr, "%s\n", err_);
}

void Game::writeToOutput(const char *out_)
{
	fprintf(stdout, "%s\n", out_);
}

Engine* Game::getEngine()
{
	return engine;
}

ResourceManager* Game::getResourceManager()
{
	return resources;
}


/*** TESTING ***/
void Game::spawnChar(int posX_, int posY_)
{
    clones.push_back(new Player(posX_, posY_));
}





