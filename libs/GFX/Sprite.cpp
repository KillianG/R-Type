//
// Created by killian on 01/11/18.
// Epitech 3 years remaining
// See http://github.com/KillianG
//

#include "Sprite.hpp"
#include "../LOG/Logger.hpp"

/**
 * Constructor of sprite
 * @param path path of the image (relative or absolute)
 * @param name name of the sprite
 */
gfx::Sprite::Sprite(std::string path, std::string name) : toDraw(true) {
    texture = *ResourceManager::get().loadTexture(path);
    this->name = name;
    sprite = sf::Sprite();
    sprite.setTexture(texture);
}

/**
 * Set a position of a sprite
 * @param pos the position you want to set to your sprite
 */
void gfx::Sprite::setPosition(gfx::Vector2Float pos) {
    this->sprite.setPosition(pos.x, pos.y);
}

/**
 * getter of sprite
 * @return the sprite
 */
sf::Sprite gfx::Sprite::getSprite() {
    return this->sprite;
}

/**
 * getter of name
 * @return the name
 */
const std::string gfx::Sprite::getName() {
    return this->name;
}

/**
 * Cut a part of the texture and take it as the new texture
 * @param pos position IN you image you want to start your rectangle
 * @param size the size of the rectangle you want
 */
void gfx::Sprite::clip(gfx::Vector2Int pos, gfx::Vector2Int size) {
    sf::IntRect rect;
    rect.top = pos.x;
    rect.left = pos.y;
    rect.width = size.x;
    rect.height = size.y;
    this->sprite.setTextureRect(rect);
}

/**
 * move a sprite in the direction dir at speed speed
 * @param dir the direction
 * @param speed the speed
 */
void gfx::Sprite::move(gfx::direction dir, float speed) {
    switch (dir) {
        case gfx::direction::DOWN:
            this->sprite.move({0, speed});
            break;
        case gfx::direction::UP:
            this->sprite.move({0, -speed});
            break;
        case gfx::direction::RIGHT:
            this->sprite.move({speed, 0});
            break;
        case gfx::direction::LEFT:
            this->sprite.move({-speed, 0});
            break;
        default:
            break;
    }
}

/**
 * set the scale of a sprite
 * @param scale the scale to set to the sprite
 */
void gfx::Sprite::setScale(gfx::Vector2Float scale) {
    this->sprite.setScale({scale.x, scale.y});
}

/**
 * Check if the sprite collide with an other sprite as parameter
 * @param sprite the sprite you want to know if collide with this one
 * @return boolean true if collide false if not
 */
bool gfx::Sprite::collide(gfx::Sprite sprite) {
    auto box = this->sprite.getGlobalBounds();
    auto testBox = sprite.getSprite().getGlobalBounds();

    return (box.intersects(testBox));
}

/**
 * get the bounds of the sprite
 * @return a rect
 */

gfx::rect gfx::Sprite::getBounds() const {
    auto rect = this->sprite.getGlobalBounds();
    return {
        rect.left, (rect.left + rect.width), rect.top, (rect.top + rect.height)
    };
}


/**
 * rotate a sprite
 * @param degree degree of rotation
 */
void gfx::Sprite::rotate(float degree) {
    this->sprite.rotate(degree);
}

/**
 * change the center point to pos
 * @param pos the position
 */
void gfx::Sprite::setCenter(gfx::Vector2Float pos) {
    this->sprite.setOrigin(pos.x, pos.y);
}

/**
 * set sprite to repeated
 * @param repeat true for repeat false for not
 */
void gfx::Sprite::setRepeated(bool repeat) {
    this->texture.setRepeated(repeat);
    this->sprite.setTexture(this->texture);
}

/**
 * get the position of the sprite
 * @return the position
 */
const gfx::Vector2Float &gfx::Sprite::getPosition() const {
    return std::forward<gfx::Vector2Float>({this->sprite.getPosition().x, this->sprite.getPosition().y});
}

void gfx::Sprite::setToDraw(bool b) {
    this->toDraw = b;
}

const bool gfx::Sprite::getToDraw() const {
    return this->toDraw;
}
