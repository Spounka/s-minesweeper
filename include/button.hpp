#ifndef SMINESWEEPER_INCLUDE_BUTTON_H
#define SMINESWEEPER_INCLUDE_BUTTON_H

#include <SFML/Graphics.hpp>
#include <string>

namespace sp
{
class Button : public sf::Sprite
{
  public:
    Button(const sf::Texture& texture, std::string const& label = "Button");
    ~Button() = default;

    void setString(std::string const& label);
    const sf::String getString() const;

    const sf::Text& getLabelObject() const;

    // overloads the actual Transformable functions to transform children along
    // TODO: This is hacky and ugly, add a hierarchy or node system
    void move(float offsetX, float offsetY);
    void move(sf::Vector2f const& offset);

    void setPosition(float positionX, float positionY);
    void setPosition(sf::Vector2f const& position);

    // * On click callback function
    void onClick(void (*callback)());

    // * Updates the button (currently calls the callback function only)
    // TODO: Add animations
    void update(sf::Window const&);

  protected:
    // ! This function was exposed from the SFML library, Find a better fix
    virtual void draw(sf::RenderTarget& target,
                      sf::RenderStates states) const override;

  private:
    sf::Text label; //< The button display text
    sf::RectangleShape boundingBox; //< Bounding box surrounding the rectangle // ! Remove

    void (*callback)(void); //< Callback variable
};
}

#endif