#include "ResourceManager.h"
#include "Controller/Game.h"

ResourceManager::ResourceManager()
{

}

ResourceManager::~ResourceManager()
{
	for(unsigned int i = 0; i < images.size(); i++)
		delete images[i];
	images.clear();

	for(unsigned int i = 0; i < fonts.size(); i++)
		delete fonts[i];
	fonts.clear();

	for(unsigned int i = 0; i < audios.size(); i++)
		delete audios[i];
	audios.clear();
}

int ResourceManager::getIndexForTag(std::string tag_)
{
	std::vector< std::pair<std::string,int> >::iterator iter = tags.begin();

	while(iter != tags.end())
	{
		if(tag_.compare((*iter).first) == 0)
		{
			return (*iter).second;
		}

		iter++;
	}

	return -1;
}

Image* ResourceManager::loadImageFromPath(std::string path_, std::string tag_)
{
	//Check tag
	std::vector<Image*>::iterator iter = images.begin();
	int index = getIndexForTag(tag_);

	if(index > 0)
		return *(iter+index);

	//Load image
	GraphicsModule *graphics = controller->getEngine()->getGraphicsModule();
	Image *img;

	img = graphics->loadImage(path_);

	images.push_back(img);
	tags.push_back(std::make_pair(tag_,images.size()-1));

	return img;
}

/*Image* ResourceManager::loadSpriteSheetXML(std::string path_, std::string tag_)
{
	Image *img = nullptr;
	std::string content = "";

	//Check tag
	std::vector<Image*>::iterator iter = images.begin();
	int index = getIndexForTag(tag_);

	if(index > 0)
		return *(iter+index);

	//Load image and create its clipatlas
	GraphicsModule *graphics = controller->getGraphics();
	XMLParser *parser = new XMLParser(path_);
	ClipAtlas clip;

	content = parser->getContentFromTag("TextureAtlas", "imagePath");
	img = graphics->loadImage(content);

	while(1)
	{
		int x, y, w, h;
		std::stringstream converter;

		content = parser->getContentFromTag("sprite", "n");
		if(content.compare("content-not-found") == 0)
			break;

		content = parser->getContentFromTag("sprite", "x");
		converter << content;
		if(!(converter >> x)) x = 0;

		content = parser->getContentFromTag("sprite", "y");
		converter << content;
		if(!(converter >> y)) y = 0;

		content = parser->getContentFromTag("sprite", "w");
		converter << content;
		if(!(converter >> w)) w = 0;

		content = parser->getContentFromTag("sprite", "h");
		converter << content;
		if(!(converter >> h)) h = 0;

		clip.addClipping(x, y, w, h);
	}

	img->setClipping(clip);

	images.push_back(img);
	tags.push_back(std::make_pair(tag_, images.size()-1));

	delete parser;

	return img;
}*/

Font* ResourceManager::loadFontFromPath(std::string path_, std::string tag_, int sizePt_)
{
	//Check tag
	std::vector<Font*>::iterator iter = fonts.begin();
	int index = getIndexForTag(tag_);

	if(index > 0)
		return *(iter+index);

	//Load Text
	TTFmodule *ttf = controller->getEngine()->getTTFmodule();
	Font *font;

	font = ttf->loadFont(path_, sizePt_);

	fonts.push_back(font);
	tags.push_back(std::make_pair(tag_,fonts.size()-1));

	return font;
}

Audio* ResourceManager::loadAudioFromPath(std::string path_, std::string tag_, AudioType type_)
{
	//Check tag
	std::vector<Audio*>::iterator iter = audios.begin();
	int index = getIndexForTag(tag_);

	if(index > 0)
		return *(iter+index);

	//Load Audio
	AudioModule *mixer = controller->getEngine()->getAudioModule();
	Audio *audio;

	if(type_ == MUSIC)
	{
		audio = mixer->loadMusic(path_);
	}
	else if(type_ == SFX)
	{
		audio = mixer->loadSFX(path_);
	}

	audios.push_back(audio);
	tags.push_back(std::make_pair(tag_,audios.size()-1));

	return audio;
}

Image* ResourceManager::getImageWithTag(std::string tag_)
{
	int index = getIndexForTag(tag_);

	if(index > 0)
	{
		return images[index];
	}

	return nullptr;
}

Font* ResourceManager::getFontWithTag(std::string tag_)
{
	int index = getIndexForTag(tag_);

	if(index > 0)
	{
		return fonts[index];
	}

	return nullptr;
}

Audio* ResourceManager::getAudioWithTag(std::string tag_)
{
	int index = getIndexForTag(tag_);

	if(index > 0)
	{
		return audios[index];
	}

	return nullptr;
}

