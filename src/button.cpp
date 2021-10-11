#include "button.hpp"

#include "config.hpp"
#include "resourcesmanager.hpp"

#include <iostream>

namespace sp
{

Button::Button(const sf::Texture& texutre, std::string const& label)
    : sf::Sprite(texutre)
{
    this->setOrigin(this->getLocalBounds().width / 2,
                    this->getLocalBounds().height / 2);
    this->label.setFont(
        ResourceManager::getFont(RESOURCES_DIR "Inconsolata-Regular.ttf"));
    this->setLabel(label);
}

void
Button::setLabel(std::string const& label)
{
    this->label.setString(label);
    auto labelBounds = this->label.getLocalBounds();
    this->label.setOrigin(labelBounds.left + labelBounds.width / 2,
                          labelBounds.top + labelBounds.height / 2);
    this->label.setPosition(this->getPosition());
}

const sf::String
Button::getLabel() const
{
    return this->label.getString();
}

const sf::Text&
Button::getText() const
{
    return this->label;
}

void
Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    this->Sprite::draw(target, states);
    target.draw(this->label);
}

void
Button::move(float offsetX, float offsetY)
{
    this->label.move(offsetX, offsetY);
    this->Sprite::move(offsetX, offsetY);
}

void
Button::move(sf::Vector2f const& offset)
{
    this->label.move(offset);
    this->Sprite::move(offset);
}

void
Button::setPosition(float positionX, float positionY)
{
    this->label.setPosition(positionX, positionY);
    this->Sprite::setPosition(positionX, positionY);
}

void
Button::setPosition(sf::Vector2f const& position)
{
    this->label.setPosition(position);
    this->Sprite::setPosition(position);
}

void
Button::onClick(void (*func)())
{
    if(func != nullptr) {
        this->callback = func;
    }
}

void
Button::update(sf::Window const& window)
{
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if(this->getGlobalBounds().contains(
               static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)))) {
            if(this->callback != nullptr) {
                this->callback();
            }
        }
    }
}

}