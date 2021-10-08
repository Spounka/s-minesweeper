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
        exit(TEXTURE_LOAD_ERROR);
    }
    return texture;
}
}