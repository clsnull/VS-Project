#include "TextureHolder.h"
#include <iostream>
#include <assert.h>

TextureHolder* TextureHolder::m_s_Instance = nullptr;

TextureHolder::TextureHolder()
{
	assert(m_s_Instance == nullptr);
	m_s_Instance = this;
}

sf::Texture& TextureHolder::getTexture(std::string const& filename) {
	std::map<std::string, sf::Texture> m = m_s_Instance->m_textures;

	auto keyValuePair = m.find(filename);

	if(keyValuePair != m.end()) {
		return keyValuePair->second;
	}
	else {
		sf::Texture texture = m[filename];
		if (!texture.loadFromFile(filename)) {
			std::cout << "Failed to load texture: " << filename << std::endl;
		};

		return texture;
	}
}