//
// Created by nhyarlathotep on 27/11/18.
//

#pragma once

#include <deque>
#include <map>
#include "../../../libs/ECS/Manager.hpp"
#include "../GameComponents.hpp"
#include "../DynamicLoader.hpp"
#include "../../levelParsing/ParsingLevel.hpp"

#include <iostream>

class SpawnSystem : public ecs::System {
public:
    explicit SpawnSystem(ecs::Manager &ecsMgr) : System(ecsMgr) {
        setNeededComponent({ Player::m_type, MovableHitBox::m_type, TeamComponent::m_type });

        _parsingLevel.startGame();
        try {
                DynamicLoader d("./Monsters/lib_bird.so");
                _loaders[d.call<std::string>("getName")] = d;

		d = DynamicLoader("Monsters/lib_bird2.so");
		_loaders[d.call<std::string>("getName")] = d;

        } catch (std::logic_error &e) {
                DynamicLoader d2("../Monsters/lib_bird.so");
                _loaders[d2.call<std::string>("getName")] = d2;

		d2 = DynamicLoader("../Monsters/lib_bird2.so");
		_loaders[d2.call<std::string>("getName")] = d2;
        }
    }

    void updateEntities(float timeSinceLastFrame) override {
        auto &&monsters = _parsingLevel.getMonster(timeSinceLastFrame);

        for (auto &monster : monsters){
            auto entity{ m_manager.createEntity() };

            Monster _monster(entity);
            _monster._ptr = _loaders[monster._type].call<IMonster::Ptr>("getMonsterLibrary");
            _monster._ptr->setPosition(monster._pos);
            m_manager.addComponent<EntityType>(entity, EntityType(_monster._ptr->getType()));
            m_manager.addComponent<Monster>(entity, _monster);
            m_manager.addComponent<TeamComponent>(entity, TeamComponent(Game::Team::ennemy));
            m_manager.addComponent<MovableHitBox>(entity, MovableHitBox(Config::playerHitBox, {1200, 200}));
            m_manager.registerEntity(entity);
        }
    }
    void updateEntity(float, ecs::Entity) override {}

private:
    Game::ParsingLevel _parsingLevel;
    std::map<std::string, DynamicLoader> _loaders;
};
