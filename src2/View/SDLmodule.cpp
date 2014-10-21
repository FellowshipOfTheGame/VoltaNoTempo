#include "SDLmodule.h"

#include "../Controller/Game.h"

/* **************************** */
/* **************************** */

SDL::SDL()
{
    graphics = new SDLgraphics();
    event = new SDLinput();
    ttf = new SDLttf();
    mixer = new SDLmixer();
    
    graphics->setScreenSize(640, 480);
    graphics->setCapFPS(60);
}

SDL::~SDL()
{
    SDL_Quit();
}

bool SDL::init()
{
    bool success = true;
    
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        Game::reportError("[ENGINE] Could not initialize SDL 2.0");
        return false;
    }
    
    success = graphics->init();
    success = success && ttf->init();
    success = success && mixer->init();
    
    return success;
    
}

void SDL::pollEvent(EventType *type_, EventCode *code_)
{
    event->pollEvent(type_, code_);
}

bool SDL::shouldRender()
{
    //If frame finished early
    int frameTicks = fpsTimer.getTicks();
    
    //Wait remaining time
    if(frameTicks < graphics->getTicksPerFrame())
    {
        SDL_Delay(graphics->getTicksPerFrame() - frameTicks);
    }
    
    return true;
}

void SDL::updateContext()
{
    graphics->updateContext();
}

void SDL::clear()
{
    graphics->clear();
}



/* **************************** */
/* **************************** */


SDLgraphics::SDLgraphics()
{
	window = NULL;
	renderer = NULL;
}

SDLgraphics::~SDLgraphics()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);

	IMG_Quit();
}

bool SDLgraphics::init()
{
	window = SDL_CreateWindow("Volta No Tempo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_MOUSE_FOCUS);

	if(window == NULL)
	{
		Game::reportError("[GRAPHICS_MODULE] Could not create a window using SDL 2.0");
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if(renderer == NULL)
	{
		Game::reportError("[GRAPHICS_MODULE] Could not create a window with accelerated rendering with SDL 2.0");
		return false;
	}

	int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
	if(!(IMG_Init(imgFlags) & imgFlags))
	{
		Game::reportError("[GRAPHICS_MODULE] Could not load extension SDL_image 2.0");
		return false;
	}

	//Set clear color to black
	 SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	return true;
}

void* SDLgraphics::getRenderingContext()
{
	return (SDL_Renderer*)renderer;
}

Image* SDLgraphics::loadImage(std::string path_)
{
	SDL_Texture *optimized = NULL;
	SDL_Surface *loaded = NULL;
	Image *image;

	loaded = IMG_Load(path_.c_str());
	if(loaded == NULL)
	{
		std::string err = "[GRAPHICS_MODULE] Could not load image at path ";
		err.append(path_);

		Game::reportError(err.c_str());
		return NULL;
	}

	optimized = SDL_CreateTextureFromSurface(renderer, loaded);
	if(optimized == NULL)
	{
		std::string err = "[GRAPHICS_MODULE] Unable to create texture, loaded from path ";
		err.append(path_);

		Game::reportError(err.c_str());
		return NULL;
	}

	image = new SDLimage(optimized, renderer, loaded->w, loaded->h);
	SDL_FreeSurface(loaded);

	return image;
}

void SDLgraphics::updateContext()
{
	SDL_RenderPresent(renderer);
}

void SDLgraphics::clear()
{
	SDL_RenderClear(renderer);
}


/* **************************** */
/* **************************** */

SDLinput::SDLinput()
{
	enableRendering = true;
}

SDLinput::~SDLinput()
{
	
}

bool SDLinput::init()  //previous definition has been erased, because code was simplified. TODO: cleanup
{
    return true;
}

void SDLinput::pollEvent(EventType *type_, EventCode *code_)
{
	*type_ = NOEVENT;
	*code_ = CODE_NULL;

	while(SDL_PollEvent(&event))
	{
		if(event.type == SDL_KEYUP)
		{
			*type_ = KEYUP;

			if(event.key.keysym.sym == SDLK_ESCAPE)
				*code_ = KEY_ESC;
            else if(event.key.keysym.sym == SDLK_SPACE)
                *code_  = KEY_SPACE;
		}
	}
}


/* **************************** */
/* **************************** */

SDLttf::SDLttf()
{

}

SDLttf::~SDLttf()
{
	TTF_Quit();
}

bool SDLttf::init()
{
	if(TTF_Init() < 0)
	{
		Game::reportError("[TTF_MODULE] Could not load extension SDL_ttf 2.0");
		return false;
	}

	return true;
}

Font* SDLttf::loadFont(std::string path_, int sizePt_)
{
	TTF_Font *rawFont = TTF_OpenFont(path_.c_str(), sizePt_);
	Font *font = NULL;

	if(rawFont == NULL)
	{
		std::string err = "[TTF_MODULE] Could not load font at path: ";
		err.append(path_);

		Game::reportError(err.c_str());
		return NULL;
	}

	font = new SDLfont(rawFont, sizePt_);

	return font;
}

Text* SDLttf::makeText(std::string text_, Font *font_, int r_, int g_, int b_, int a_)
{
	SDLtext *output;
	SDL_Color color = {(Uint8)r_, (Uint8)g_, (Uint8)b_, (Uint8)a_};

	output = new SDLtext(text_, font_, color);

	return output;
}


/* **************************** */
/* **************************** */

SDLmixer::SDLmixer()
{

}

SDLmixer::~SDLmixer()
{
	Mix_CloseAudio();
}

bool SDLmixer::init()
{
	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		Game::reportError("[AUDIO_MODULE] Could not load extension SDL_mixer 2.0");
		return false;
	}

	return true;
}

Audio* SDLmixer::loadMusic(std::string path_)
{
	Audio *audio = NULL;
	Mix_Music *rawAudio = Mix_LoadMUS(path_.c_str());

	if(rawAudio == NULL)
	{
		std::string err = "[AUDIO_MODULE] Could not load audio at path: ";
		err.append(path_);

		Game::reportError(err.c_str());
		return NULL;
	}

	audio = new SDLaudio(rawAudio);

	return audio;
}

Audio* SDLmixer::loadSFX(std::string path_)
{
	Audio *audio = NULL;
	Mix_Chunk *rawAudio = Mix_LoadWAV(path_.c_str());

	if(rawAudio == NULL)
	{
		std::string err = "[AUDIO_MODULE] Could not load audio at path: ";
		err.append(path_);

		Game::reportError(err.c_str());
		return NULL;
	}

	audio = new SDLaudio(rawAudio);

	return audio;
}


/* **************************** */
/* **************************** */

SDLimage::SDLimage(SDL_Texture *texture_, SDL_Renderer *context_, int width_, int height_) : Image(width_, height_)
{
	texture = texture_;
    context = context_;
}

SDLimage::~SDLimage()
{
	SDL_DestroyTexture(texture);
}

void SDLimage::render()
{
	SDL_Rect pos;
	SDL_Rect cut;

	pos.x = dimension.getX();
	pos.y = dimension.getY();
	pos.w = clip.getCurW();
	pos.h = clip.getCurH();

	cut.x = clip.getCurX();
	cut.y = clip.getCurY();
	cut.w = clip.getCurW();
	cut.h = clip.getCurH();

	SDL_RenderCopy(context, texture, &cut, &pos);
}


/* **************************** */
/* **************************** */

SDLfont::SDLfont(TTF_Font *loadedFont_, int sizePt_) : Font(sizePt_)
{
	font = loadedFont_;
}

SDLfont::~SDLfont()
{
	TTF_CloseFont(font);
}

void* SDLfont::getFontStructure()
{
	return (void*)font;
}


/* **************************** */
/* **************************** */

SDLtext::SDLtext(std::string text_, Font *font_, SDL_Color color_) : Text(text_, font_)
{
	color = color_;
	renderedText = NULL;
	renderedText = preRender();
}

SDLtext::~SDLtext()
{
	SDL_DestroyTexture(renderedText);
}

void SDLtext::render()
{
	SDL_Renderer *context = (SDL_Renderer*)controller->getEngine()->getGraphicsModule()->getRenderingContext();
	SDL_Rect pos;
	SDL_Rect cut;

	pos.x = dimension.getX();
	pos.y = dimension.getY();
	pos.w = clip.getCurW();
	pos.h = clip.getCurH();

	cut.x = clip.getCurX();
	cut.y = clip.getCurY();
	cut.w = clip.getCurW();
	cut.h = clip.getCurH();

	SDL_RenderCopy(context, renderedText, &cut, &pos);
}

void SDLtext::update(std::string newText_)
{
	int width = font->getSizePt() * (int)newText_.size();
	int height = font->getSizePt();

	text.assign(newText_);
	dimension.setSize(width, height);

	preRender();
}

SDL_Texture* SDLtext::preRender()
{
	SDL_Surface *tmp;
	TTF_Font *fnt = (TTF_Font*)font->getFontStructure();
	GraphicsModule *graphics = controller->getEngine()->getGraphicsModule();

	if(renderedText != NULL)
		SDL_DestroyTexture(renderedText);

	tmp = TTF_RenderText_Solid(fnt, text.c_str(), color);
	if(tmp == NULL)
	{
		std::string err = "[TTF_MODULE] Could not pre-render text: ";
		err.append(text);

		Game::reportError(err.c_str());
		return NULL;
	}

	renderedText = SDL_CreateTextureFromSurface((SDL_Renderer*)graphics->getRenderingContext(), tmp);
	if(renderedText == NULL)
	{
		std::string err = "[TTF_MODULE] Could not create texture from surface for text: ";
		err.append(text);

		Game::reportError(err.c_str());
		return NULL;
	}

	SDL_FreeSurface(tmp);

	return renderedText;
}


/* **************************** */
/* **************************** */

SDLaudio::SDLaudio(Mix_Music *music_) : Audio()
{
	music = music_;
	loop = -1; //loop forever
}

SDLaudio::SDLaudio(Mix_Chunk *sfx_) : Audio()
{
	sfx = sfx_;
	loop = 0;
}

SDLaudio::~SDLaudio()
{

}

void SDLaudio::play()
{
	if(music != NULL)
	{
		Mix_PlayMusic(music, loop);
	}
	else if(sfx != NULL)
	{
		Mix_PlayChannel(-1, sfx, loop);
	}
}




