#ifndef SMINESWEEPER_INCLUDE_BUTTON_H
#define SMINESWEEPER_INCLUDE_BUTTON_H

#include <SFML/Graphics.hpp>
#include <string>

namespace sp
{
class Button : public sf::Sprite
{
  public:
    Button(const sf::Texture& texutre, std::string const& label = "Button");
    ~Button() = default;

    void setLabel(std::string const& label);
    const sf::String getLabel() const;
    const sf::Text& getText() const;

    void move(float offsetX, float offsetY);
    void move(sf::Vector2f const& offset);

    void setPosition(float positionX, float positionY);
    void setPosition(sf::Vector2f const& position);

    void onClick(void (*callback)());
    void update(sf::Window const&);

  protected:
    virtual void draw(sf::RenderTarget& target,
                      sf::RenderStates states) const override;

  private:
    sf::Text label;
    sf::RectangleShape boundingBox;

    void (*callback)(void);
};
}

#endif