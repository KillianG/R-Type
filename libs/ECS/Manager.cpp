/*
** EPITECH PROJECT, 2018
** Epitech scolarship project (4 years remaining)
** File description:
**      Made on 2018/11 by ebernard
*/

#include <cassert>
#include <algorithm>
#include "Manager.hpp"

/**
 * Creat an Entity and stor it.
 * #TODO save unused Entity and reuse it.
 * @return
 */
ecs::Entity ecs::Manager::createEntity() {
//	m_activeEntity.insert((Entity)m_activeEntity.size() + 1);
	return m_nbEntity++;
}

/**
 * Register an Entity to all System
 * throw exception if it's  not a valid Entity
 * @param entity the entity to register
 */
void ecs::Manager::registerEntity(ecs::Entity entity)
{
//	if (m_activeEntity.find(entity) == m_activeEntity.end())
//		throw (std::runtime_error("Entity must be created by the Manager"));

	std::set<ComponentType> needed;

	for (auto &sys : m_systems) {
	    for (auto &neededComponents : sys->getNeededComponents()) {
            if (std::includes(m_entities[entity].begin(),  m_entities[entity].end(), neededComponents.begin(), neededComponents.end()) && !sys->hasEntity(entity))
                sys->addEntity(entity);
	    }
	}
}

/**
 * Remove an Entity from all System
 * @param entity the Entity to remove
 */
void ecs::Manager::removeEntity(ecs::Entity entity) {
//	if (m_activeEntity.find(entity) == m_activeEntity.end())
//		throw (std::runtime_error("Entity must be created by the Manager"));
//	m_activeEntity.erase(entity);
	for (auto &system : m_systems) {
		if (system->hasEntity(entity))
			system->removeEntity(entity);
	}
}

/**
 * Add a System pointeur to the Manager
 * @param system the System to add
 */
void ecs::Manager::addSystem(System::Ptr system)
{
	if (!system)
		throw std::runtime_error("system is NULL");
	if (system->getNeededComponents().empty())
		throw std::runtime_error("system has no needed Component");
    for (auto &elems : system->getNeededComponents()) {
        for (auto &it : elems) {
			if (m_componentManager.find(it) == m_componentManager.end())
			{
#ifdef __linux__ 

				throw std::runtime_error(std::string("This system need a ComponentManager that is not created: ") + std::to_string(it));
#endif

			}
        }
    }
	m_systems.push_back(system);
}

/**
 * Remove System pointeur from the Manager
 * @param system to remove
 */
void ecs::Manager::removeSystem(ecs::System::Ptr system)
{
	if (!system || system->getNeededComponents().empty())
		throw std::runtime_error("system is NULL or has no needed Component");
	if (std::find(m_systems.begin(), m_systems.end(), system) == m_systems.end())
		throw std::runtime_error("There are no such system: " + std::string(typeid(system).name()));

	m_systems.erase(std::find(m_systems.begin(), m_systems.end(), system));
}

/**
 * Update all System
 * @param updateTime time laps the system will be updated
 */
void ecs::Manager::updateSystems(float updateTime)
{
	for (auto &elem : m_systems){
		elem->updateEntities(updateTime);
	}
}

