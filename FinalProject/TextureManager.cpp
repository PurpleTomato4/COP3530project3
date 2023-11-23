#include <SFML/Graphics.hpp>
#include "TextureManager.h"

// "redeclare" this variable so file knows it exists and can use it, important for static variables 
unordered_map<string, sf::Texture> TextureManager::textures;

void TextureManager::LoadTexture(string fileName) {
	string path = "images/";
	path += fileName + ".png";
	textures[fileName].loadFromFile(path);
}

sf::Texture& TextureManager::GetTexture(string textureName) {
	// if texture does not exist load it first and then return it 
	if (textures.find(textureName) == textures.end())
		LoadTexture(textureName);

	return textures[textureName];
}

void TextureManager::Clear() {
	textures.clear();
}