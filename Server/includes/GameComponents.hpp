//
// Created by nhyarlathotep on 19/11/18.
//

#pragma once

#include "Utils.hpp"
#include "../../libs/ECS/ComponentManager.hpp"

struct PowerUpShield : public ecs::Component {
        static const ecs::ComponentType m_type;
};

struct PowerUpSpeed : public ecs::Component {
    static const ecs::ComponentType m_type;

    explicit PowerUpSpeed(size_t speed) : _speed(speed) {}

    float _speed;
};

/**
 * Define a Type of enemy or player
 */
struct EntityType : public ecs::Component {
        static const ecs::ComponentType m_type;

        explicit EntityType(size_t type) : _type(type) {}

	size_t _type;
};

/**
 * Defines a team (Game::Team::ally / Game::Team::ennemy)
 */
struct TeamComponent : public ecs::Component {
    static const ecs::ComponentType m_type;

    explicit TeamComponent(Game::Team &&team) : _team(team) {}
    explicit TeamComponent(const Game::Team &team) : _team(team) {}

    Game::Team _team;
};

/**
 * Defines a player with a unique id and direction for his movements
 */
struct Player : public ecs::Component {
    static const ecs::ComponentType m_type;

    explicit Player(ecs::Entity &id, ecs::Entity idShield) : _id(id), _shieldEntity(idShield) {}

    Player &operator+=(const PowerUpSpeed &powerUp) {
        _speed += powerUp._speed;
        return *this;
    }

    float _speed { 0 };
    size_t _shield { 1 };
    ecs::Entity _id;
    ecs::Entity _shieldEntity;
    Game::vector2f _dir;
};

/**
 * Defines a Monster with a unique id and direction for his movements
 */
struct Monster : public ecs::Component {
    static const ecs::ComponentType m_type;

    explicit Monster(ecs::Entity &id) : _id(id) {}

    ecs::Entity _id;
};

/**
 * Defines a Missile
 */
struct Missile : public ecs::Component {
    static const ecs::ComponentType m_type;

    explicit Missile(int charge, const Game::vector2f &dir) : _charge(charge), _dir(dir) {}

    int _charge { 0 };
    Game::vector2f _dir;
};

/**
 * Defines an hitbox with position and dimensions
 */
struct MovableHitBox : public ecs::Component {
    static const ecs::ComponentType m_type;

    MovableHitBox(const Game::box &dims, const Game::vector2f &pos, size_t spriteId, size_t animSize, float frameRate = 0.1f)
    : _dims(dims), _pos(pos), _spriteType(spriteId), _animSize(animSize), _frameRate(frameRate) {}

    /**
     * @brief Checks collision between two hitboxes
     * @param [in] Second hitbox
     * @return boolean [out] If there is a collision
     */
    bool checkCollide(const MovableHitBox &other) const {
        if (this->_pos.x + this->_dims.width >= other._pos.x)
            if ((this->_pos.x <= other._pos.x + other._dims.width) &&
                (this->_pos.y + this->_dims.height >= other._pos.y) &&
                (this->_pos.y <= other._pos.y + other._dims.height))
                return true;
        return false;
    }

    /**
     * @brief choose wich animation to draw
     * @param timeSinceLastFrame [in] Added time
     * @return [ou] drawed animation
     */
    size_t addTime(float timeSinceLastFrame) noexcept {
        _time += timeSinceLastFrame;
        if (_time > _frameRate * _animSize) {
            _time = 0;
            _animTime = 0;
        }
        if (_time > _frameRate * (_animTime + 1))
            _animTime += 1;
        return _animTime;
    }

    Game::box _dims;
    Game::vector2f _pos;
    size_t _spriteType { 1 };

private:
    float _time { 0 };
    size_t _animSize { 0 };
    size_t _animTime { 0 };
    float _frameRate;
};