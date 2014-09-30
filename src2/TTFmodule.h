#ifndef __TTF_MODULE_H__
#define __TTF_MODULE_H__

#include "../utility/Tools.h"

/**/
class Font
{
private:
	int sizePt;

public:
	Font(int sizePt_)
	{
		sizePt = sizePt_;
	}

	virtual int getSizePt() {return sizePt;}
	virtual void* getFontStructure() = 0;

	virtual void setSizePt(int sizePt_) {sizePt = sizePt_;}
};

/**/
class Text : public Renderable
{
protected:
	Dimension2D dimension;
	ClipAtlas clip;
	std::string text;
	Font *font;

public:
	Text(std::string text_, Font *font_)
	{
		int width;
		int height;

		text.assign(text_);
		font = font_;

		width = font_->getSizePt() * text_.size();
		height = font->getSizePt();

		dimension.setPosition(0, 0);
		dimension.setSize(width, height);
		clip.setClipping(0, 0, width, height);
	}

	virtual void render() = 0;
	virtual void update(std::string newText_) = 0;

	virtual int getWidth() {return dimension.getW();}
	virtual int getHeight() {return dimension.getH();}
	virtual int getPosX() {return dimension.getX();}
	virtual int getPosY() {return dimension.getY();}
	virtual std::string getText() {return text;}

	virtual void setPosition(int x_, int y_) {dimension.setPosition(x_, y_);}
	virtual void setClipping(int x_, int y_, int w_, int h_) {clip.setClipping(x_, y_, w_, h_);}
	virtual void setClipping(ClipAtlas atlas_) {clip = atlas_;}
	virtual void setText(std::string text_) {text.assign(text_);}
};

/**/
class TTFmodule
{
protected:


public:
	TTFmodule() {}

	virtual bool init() = 0;
	virtual Font* loadFont(std::string path_, int sizePt_) = 0;
	virtual Text* makeText(std::string text_, Font *font_, int r_, int g_, int b_, int a_) = 0;
};

#endif
