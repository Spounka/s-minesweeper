#include "resourcesmanager.hpp"

#include <cstdio>

#include "config.hpp"

namespace sp
{
sf::Texture&
ResourceManager::getTexture(std::string const& filename)
{
    auto& textureMap = getInstance().textures;
    auto texturePair = textureMap.find(filename);

    if(texturePair != textureMap.end()) {
        return texturePair->second;
    }

    auto& texture = textureMap[filename];
    if(!texture.loadFromFile(filename)) {
        std::fprintf(stderr, "Failed to load texture, aborting\n");
        exit(FILE_LOAD_ERROR);
    }
    return texture;
}

sf::Font&
ResourceManager::getFont(std::string const& filename)
{
    auto& fontMap = getInstance().fonts;
    auto fontPair = fontMap.find(filename);

    if(fontPair != fontMap.end()) {
        return fontPair->second;
    }

    auto& font = fontMap[filename];
    if(!font.loadFromFile(filename)) {
        std::fprintf(stderr, "Failed to load font, aborting\n");
        exit(FILE_LOAD_ERROR);
    }
    return font;
}
}