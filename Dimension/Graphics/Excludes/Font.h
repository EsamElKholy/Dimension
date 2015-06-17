#pragma once

#include <string>
#include "..\Core\ScreenManager.h"
#include <map>

struct Character
{
	GLuint TextureID;  
	vec2 Size;       
	vec2 Bearing;    
	GLuint Advance;    
};

class Font
{
public:
	Font(const std::string &path ,const int &size);
	~Font();

	inline const std::map<GLchar, Character>& getCharacters(){ return characters; }

private:
	std::map<GLchar, Character> characters;
};