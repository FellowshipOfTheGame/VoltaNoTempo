#ifndef __SDL_MODULE_H__
#define __SDL_MODULE_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include "../syslibs.h"
#include "Engine.h"


class SDLgraphics : public GraphicsModule
{
private:
	SDL_Window *window;
	SDL_Renderer *renderer;

public:
	SDLgraphics();
	~SDLgraphics();

	bool init();
	void updateContext();
	void clear();
	void* getRenderingContext();
	Image* loadImage(std::string path_);

};

class SDLinput : public EventHandler
{
private:
	SDL_Event event;
	

public:
	SDLinput();
	~SDLinput();

	bool init();
	void pollEvent(EventType *type_, EventCode *code_);
};

class SDLttf : public TTFmodule
{
private:


public:
	SDLttf();
	~SDLttf();

	bool init();
	void render();
	Font* loadFont(std::string path_, int sizePt_);
	Text* makeText(std::string text_, Font *font_, int r_, int g_, int b_, int a_);

};

class SDLmixer : public AudioModule
{
private:


public:
	SDLmixer();
	~SDLmixer();

	bool init();
	Audio* loadMusic(std::string path_);
	Audio* loadSFX(std::string path_);
};


/*****************************************/
/*****************************************/

class SDLimage : public Image
{
private:
	SDL_Texture *texture;
    SDL_Renderer *context;

public:
	SDLimage(SDL_Texture *texture_, SDL_Renderer *context_, int width_, int height_);
	~SDLimage();

	void render();
};

class SDLfont : public Font
{
private:
	TTF_Font *font;

public:
	SDLfont(TTF_Font *loadedFont_, int sizePt_);
	~SDLfont();

	void* getFontStructure();
};

class SDLtext : public Text
{
private:
	SDL_Texture *renderedText;
	SDL_Color color;

public:
	SDLtext(std::string text_, Font *font_, SDL_Color color_);
	~SDLtext();

	void render();
	void update(std::string newText_);
	SDL_Texture* preRender();

};

class SDLaudio : public Audio
{
private:
	Mix_Music *music;
	Mix_Chunk *sfx;
	int loop;

public:
	SDLaudio(Mix_Music *music_);
	SDLaudio(Mix_Chunk *sfx_);
	~SDLaudio();

    void play();
    void stop();
    void setVolume(double volume_);
};


/*****************************************/
/*****************************************/

class SDL : public Engine
{
private:

    
public:
    SDL();
    ~SDL();
    
    bool init();
    void pollEvent(EventType *type_, EventCode *code_);
    bool shouldRender();
    void updateContext();
    void clear();
    
};



#endif
