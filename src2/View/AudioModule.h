#ifndef __AUDIOMODULE_H__
#define __AUDIOMODULE_H__

typedef enum {MUSIC, SFX} AudioType;

/**/
class Audio
{
protected:
	double volume;

public:
	Audio() {volume = 1.0;}
    
    virtual ~Audio() {}

	virtual void play() = 0;
	virtual double getVolume() {return volume;}
	virtual void setVolume(double volume_) {volume = volume_;}
    virtual void stop() {}
};

/**/
class AudioModule
{
protected:

public:

	virtual bool init() = 0;
	virtual Audio* loadMusic(std::string path_) = 0;
	virtual Audio* loadSFX(std::string path_) = 0;
};


#endif
