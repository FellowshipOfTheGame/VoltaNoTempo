#ifndef __RESOURCE_MANAGER_H__
#define __RESOURCE_MANAGER_H__

#include "../syslibs.h"
#include "../View/GraphicsModule.h"
#include "../View/TTFmodule.h"
#include "../View/AudioModule.h"


class ResourceManager
{
private:
	std::vector<Image*> images;
	std::vector<Font*> fonts;
	std::vector<Audio*> audios;
	std::vector< std::pair<std::string,int> > tags;
    std::string folder;
	int getIndexForTag(std::string tag_);

public:
	ResourceManager();
	~ResourceManager();

	Image* loadImageFromPath(std::string path_, std::string tag_);
	Font* loadFontFromPath(std::string path_, std::string tag_, int sizePt_);
	Audio* loadAudioFromPath(std::string path_, std::string tag_, AudioType type_);

	Image* getImageWithTag(std::string tag_);
	Font* getFontWithTag(std::string tag_);
	Audio* getAudioWithTag(std::string tag_);

	Image *loadSpriteSheetXML(std::string tag_, std::string field_);

    void setFolderName(std::string name);

};

#endif