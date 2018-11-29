//
// Created by killian on 01/11/18.
// Epitech 3 years remaining
// See http://github.com/KillianG
//

#ifndef R_TYPE_SPRITE_HPP
#define R_TYPE_SPRITE_HPP

#include <SFML/Graphics.hpp>
#include "GfxManager.hpp"
#include "Window.hpp"

namespace gfx {

    enum direction {
        RIGHT,
        LEFT,
        UP,
        DOWN
    };

    struct rect {
        float left;
        float right;
        float up;
        float down;
    };

    class Sprite {
    public:

        friend class gfx::Window;

        Sprite(std::string path, std::string name);
        ~Sprite() = default;

        void setScale(gfx::Vector2Float scale);
        void setPosition(gfx::Vector2Float pos);
        const std::string getName();
        void clip(gfx::Vector2Int pos, gfx::Vector2Int size);
        void move(gfx::direction dir, float speed);
        bool collide(gfx::Sprite);
        gfx::rect getBounds() const;
        void rotate(float degree);
        void setCenter(gfx::Vector2Float pos);
        void setRepeated(bool repeat);
        const gfx::Vector2Float &getPosition() const;
        void setToDraw(bool b);
        const bool getToDraw() const;

    private:
        sf::Sprite getSprite();
        sf::Sprite sprite;
        sf::Texture texture;
        std::string name;
        bool toDraw;
    };
}
#else
namespace gfx{
    class Sprite;
};

#endif //R_TYPE_SPRITE_HPP
