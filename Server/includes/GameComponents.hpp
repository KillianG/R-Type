//
// Created by nhyarlathotep on 19/11/18.
//

#pragma once

#include <string>
#include <functional>
#include "GameConfig.hpp"
#include "../../libs/ECS/ComponentManager.hpp"

class IEnnemy;
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

    explicit Player(ecs::Entity &id) : _id(id) {}

    ecs::Entity _id;
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

    explicit Missile(int charge) : _charge(charge) {}

    int _charge { 0 };
};

/**
 * Defines an hitbox with position and dimensions
 */
struct MovableHitBox : public ecs::Component {
    static const ecs::ComponentType m_type;

    MovableHitBox(const Game::box &dims, const Game::vector2f &pos, size_t spriteId, size_t animSize) : _dims(dims), _pos(pos), _spriteType(spriteId), _animSize(animSize) {}

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

    /**
     * @brief Sets the animation's informations
     * @param spriteType [in] which sprite
     * @param animSize [in] Nb frames in the animation
     */
    void setAnimInfos(size_t spriteType, size_t animSize) {
        _spriteType = spriteType;
        _animSize = animSize;
    }

    Game::box _dims;
    Game::vector2f _pos;
    size_t _spriteType { 1 };

private:
    float _time { 0 };
    size_t _animSize { 5 };
    size_t _animTime { 0 };
    float _frameRate { 0.2f };
};