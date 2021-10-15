#include "button.hpp"

#include "config.hpp"
#include "resourcesmanager.hpp"

#include <iostream>

namespace sp
{

Button::Button(const sf::Texture& texture, std::string const& label)
    : sf::Sprite(texture)
{
    // Centering the origin for easier manipulation
    this->setOrigin(this->getLocalBounds().width / 2,
                    this->getLocalBounds().height / 2);
    // ! Hard codeded font, move this to config.hpp
    this->label.setFont(
        ResourceManager::getFont(RESOURCES_DIR "Inconsolata-Regular.ttf"));

    this->setString(label);
}

Button::Button(const Button& other)
{
    this->setTexture(*other.getTexture());

    this->label = sf::Text(other.label);
    this->label.setFont(
        ResourceManager::getFont(RESOURCES_DIR "Inconsolata-Regular.ttf"));
    this->setString(other.label.getString());

    this->callback = other.callback;

    this->setOrigin(this->getLocalBounds().width / 2,
                    this->getLocalBounds().height / 2);
    this->enabled = other.enabled;
}

ICloneable*
Button::clone() const
{
    return new Button(*this);
}

void
Button::setString(std::string const& label)
{
    this->label.setString(label);

    // Centering the font each time the label gets changed to make sure it's
    // always correct
    auto labelBounds = this->label.getLocalBounds();
    this->label.setOrigin(labelBounds.left + labelBounds.width / 2,
                          labelBounds.top + labelBounds.height / 2);

    this->label.setPosition(this->getPosition());
}

const sf::String
Button::getString() const
{
    return this->label.getString();
}

const sf::Text&
Button::getLabelObject() const
{
    return this->label;
}

void
Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // Drawing the sprite before the label, order is important to make sure text
    // is always on top
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
Button::onClick(void (*func)(void* arg), void* args)
{
    this->callback = func;
    this->callback_args = args;
}

void
Button::onRightClick(void (*func)(void* args))
{
    this->rightCallback = func;
}

void
Button::update(sf::Window const& window)
{
    // Check if mouse is pressed and is within button bounds
    //! Warning: The collision check doesn't work if the mouse is at the very
    //!          left / bottom of the button
    if(!window.hasFocus() || !this->enabled)
        return;

    if(this->elapsedTime > sf::milliseconds(0))
        this->elapsedTime -= sf::milliseconds(1);
    else if(this->elapsedTime < sf::milliseconds(0)) {
        this->elapsedTime = sf::milliseconds(0);
    }

    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if(this->getGlobalBounds().contains(
               static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)))) {
            if(this->callback != nullptr
               && this->elapsedTime <= sf::milliseconds(0)) {
                this->callback(this->callback_args);
                this->elapsedTime = sf::milliseconds(50);
            }
        }
    }
    if(sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
        if(this->getGlobalBounds().contains(
               static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)))) {
            if(this->rightCallback != nullptr
               && this->elapsedTime <= sf::milliseconds(0)) {
                this->rightCallback(this->callback_args);
                this->elapsedTime = sf::milliseconds(50);
            }
        }
    }
}

}