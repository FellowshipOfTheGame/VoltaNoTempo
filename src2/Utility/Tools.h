

#ifndef __TOOLS_H__
#define __TOOLS_H__

#include "../syslibs.h"

class Dimension2D
{
private:
	double x;
	double y;
	int w;
	int h;

public:
	Dimension2D() {}
	Dimension2D(double x_, double y_);
	Dimension2D(double x_, double y_, int w_, int h_);
	~Dimension2D();

	void setPosition(double x_, double y_);
	void setSize(int w_, int h_);

	double getX();
	double getY();
	int getW();
	int getH();
};


class ClipAtlas
{
private:
	std::vector<Dimension2D> clip;
	int curClipIndex;

public:
	ClipAtlas() {}
	ClipAtlas(int x_, int y_, int w_, int h_);
	~ClipAtlas();

	void setClipping(int x_, int y_, int w_, int h_);
	void clipAsGrid(int nrow_, int ncol_, int clipWidth_, int clipHeight_);
	void addClipping(int x_, int y_, int w_, int h_);

	int getCurX();
	int getCurY();
	int getCurW();
	int getCurH();
	Dimension2D getCurDimension();
};

#endif
