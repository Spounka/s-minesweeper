#ifndef INCLUDE_RESOURCESMANAGER_HPP
#define INCLUDE_RESOURCESMANAGER_HPP

#include <map>

#include <SFML/Graphics.hpp>

namespace sp
{
class ResourceManager
{
  public:
    static auto&
    getInstance()
    {
        static ResourceManager instance;
        return instance;
    }

    static sf::Texture& getTexture(std::string const& filename);
    static sf::Font& getFont(std::string const& filename);

    ~ResourceManager() = default;
    ResourceManager(ResourceManager&) = delete;
    ResourceManager(ResourceManager&&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;
    ResourceManager& operator=(ResourceManager&&) = delete;

  protected:
    ResourceManager(){};

  private:
    std::map<std::string, sf::Texture> textures;
    std::map<std::string, sf::Font> fonts;
};
}

#endif