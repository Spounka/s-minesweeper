#ifndef INCLUDE_RESOURCESMANAGER_HPP
#define INCLUDE_RESOURCESMANAGER_HPP

#include <map>

#include <SFML/Graphics.hpp>

namespace sp
{
// Singleton Class handle resources
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

    // default destructor
    ~ResourceManager() = default;

    // prevent copy constructor
    ResourceManager(ResourceManager&) = delete;

    // prevent copy semantics
    ResourceManager(ResourceManager&&) = delete;

    // prevent assignment operator
    ResourceManager& operator=(const ResourceManager&) = delete;
    ResourceManager& operator=(ResourceManager&&) = delete;

  protected:
    // private constructor for singleton
    ResourceManager(){};

  private:
    // Maps for holding resources, string refers to path
    std::map<std::string, sf::Texture> textures;
    std::map<std::string, sf::Font> fonts;
};
}

#endif