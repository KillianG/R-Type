//
// Created by nhyarlathotep on 27/11/18.
//

#pragma once

#include <map>
#include <Server/includes/DynamicLoaderManager.hpp>
#include "../../../libs/GFX/Singleton.hpp"
#include "../../../libs/ECS/Manager.hpp"
#include "../../../libs/EventManager/EventManager.hpp"
#include "../../levelParsing/ParsingLevel.hpp"
#include "../GameEvents.hpp"
#include "../GameComponents.hpp"
#include "../DynamicLoader.hpp"

class EnnemySystem : public ecs::System, public Receiver<EnnemySystem> {
public:
    explicit EnnemySystem(ecs::Manager &ecsMgr, EventManager &evtMgr) : System(ecsMgr), _loader(gfx::Singleton<game::DynamicLoaderManager>::get()){
        evtMgr.subscribe<Game::RemoveEvent>(*this);

        setNeededComponent({ Monster::m_type, MovableHitBox::m_type, TeamComponent::m_type });

        _parsingLevel.startGame();
    }

    void updateEntities(float timeSinceLastFrame) override {
        auto &&monsters = _parsingLevel.getMonster(timeSinceLastFrame);

        for (auto &monster : monsters){
            auto entity{ m_manager.createEntity() };
            _monstersList[entity] = { _loader.getMonster(monster._type) };
            m_manager.addComponent<Monster>(entity, Monster(entity));
            m_manager.addComponent<TeamComponent>(entity, TeamComponent(Game::Team::ennemy));
            m_manager.addComponent<MovableHitBox>(entity, _monstersList[entity]->initEnnemy(monster._pos));
            m_manager.registerEntity(entity);
        }

        for (auto &it : m_entities)
            updateEntity(timeSinceLastFrame, it);
    }

    void updateEntity(float timeSinceLastFrame, ecs::Entity it) override {
        auto &hitBox { m_manager.getComponentManager<MovableHitBox>().getComponent(it) };
        hitBox._pos = _monstersList[it]->move(timeSinceLastFrame);
    }

    void receive(const Game::RemoveEvent &event) {
        _monstersList.erase(event._id);
    }

private:
    Game::ParsingLevel _parsingLevel;
    game::DynamicLoaderManager &_loader;
    std::map<ecs::Entity, IEnnemy::Ptr> _monstersList;
};
