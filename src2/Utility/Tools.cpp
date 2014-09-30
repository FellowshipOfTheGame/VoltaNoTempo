#include "Tools.h"


Dimension2D::Dimension2D(int x_, int y_)
{
	x = x_;
	y = y_;
}

Dimension2D::Dimension2D(int x_, int y_, int w_, int h_)
{
	x = x_;
	y = y_;
	w = w_;
	h = h_;
}

Dimension2D::~Dimension2D()
{

}

void Dimension2D::setPosition(int x_, int y_)
{
	x = x_;
	y = y_;
}

void Dimension2D::setSize(int w_, int h_)
{
	w = w_;
	h = h_;
}

int Dimension2D::getX()
{
	return x;
}

int Dimension2D::getY()
{
	return y;
}

int Dimension2D::getW()
{
	return w;
}

int Dimension2D::getH()
{
	return h;
}

/* **************************** */

ClipAtlas::ClipAtlas(int x_, int y_, int w_, int h_)
{
	clip.push_back(Dimension2D(x_, y_, w_, h_));
}

ClipAtlas::~ClipAtlas()
{
	clip.clear();
}

void ClipAtlas::clipAsGrid(int nrow_, int ncol_, int clipWidth_, int clipHeight_)
{
	//Remove any other previous clipping
	if(clip.size() > 0)
	{
		clip.clear();
		curClipIndex = 0;
	}

	for(int i = 0; i < nrow_; i++)
	{
		for(int j = 0; j < ncol_; j++)
		{
			addClipping(i*clipHeight_, j*clipWidth_, clipWidth_, clipHeight_);
		}
	}
}

void ClipAtlas::addClipping(int x_, int y_, int w_, int h_)
{
	Dimension2D d = Dimension2D(x_, y_, w_, h_);

	clip.push_back(d);
}

void ClipAtlas::setClipping(int x_, int y_, int w_, int h_)
{
	if(clip.size() == 0)
	{
		clip.push_back(Dimension2D(0,0,0,0));
		curClipIndex = 0;
	}

	clip[curClipIndex].setPosition(x_, y_);
	clip[curClipIndex].setSize(w_, h_);
}

int ClipAtlas::getCurX()
{
	return clip[curClipIndex].getX();
}

int ClipAtlas::getCurY()
{
	return clip[curClipIndex].getY();
}

int ClipAtlas::getCurW()
{
	return clip[curClipIndex].getW();
}

int ClipAtlas::getCurH()
{
	return clip[curClipIndex].getH();
}

Dimension2D ClipAtlas::getCurDimension()
{
	return clip[curClipIndex];
}
