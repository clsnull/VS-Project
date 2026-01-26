#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <string>

#ifndef TEXTURE_HOLDER_H
#define TEXTURE_HOLDER_H

class TextureHolder
{
public:
	TextureHolder();
	static sf::Texture& getTexture(std::string const& filename);

private:
	std::map<std::string, sf::Texture> m_textures;

	static TextureHolder* m_s_Instance;
};


#endif // !TEXTURE_HOLDER_H
