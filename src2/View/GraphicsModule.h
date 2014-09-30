//
//  GraphicsModule.h
//  VoltaOSX
//
//  Created by Guilherme S.G. on 9/30/14.

#ifndef __GRAPHICS_MODULE_H__
#define __GRAPHICS_MODULE_H__

#include "syslibs.h"
#include "Tools.h"

/**/
class Image : public Renderable
{
protected:
    Dimension2D dimension;
    ClipAtlas clip;
    
public:
    Image() {}
    Image(int width_, int height_)
    {
        dimension.setPosition(0, 0);
        dimension.setSize(width_, height_);
        clip.setClipping(0, 0, width_, height_);
    }
    virtual ~Image() {}
    
    virtual void render() = 0;
    
    virtual int getWidth() {return dimension.getW();}
    virtual int getHeight() {return dimension.getH();}
    virtual int getPosX() {return dimension.getX();}
    virtual int getPosY() {return dimension.getY();}
    
    virtual void setPosition(int x_, int y_) {dimension.setPosition(x_, y_);}
    virtual void setClipping(int x_, int y_, int w_, int h_) {clip.setClipping(x_, y_, w_, h_);}
    virtual void setClipping(ClipAtlas atlas_) {clip = atlas_;}
};

/**/
class GraphicsModule
{
protected:
    int screenWidth;
    int screenHeight;
    
public:
    virtual int getScreenWidth() {return screenWidth;}
    virtual int getScreenHeight() {return screenHeight;}
    
    virtual void setScreenSize(int width_, int height_)
    {
        screenWidth = width_;
        screenHeight = height_;
    }
    
    virtual void* getRenderingContext() = 0;
    virtual bool init() = 0;
    virtual void updateContext() = 0;
    virtual void clear() = 0;
    virtual Image* loadImage(std::string path_) = 0;
    
};

#endif
