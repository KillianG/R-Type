/*
** EPITECH PROJECT, 2018
** Epitech scolarship project (4 years remaining)
** File description:
**      Made on 2018/11 by ebernard
*/

#include "System.hpp"

/**
 * This constructor just like the manager to the Systme so it can get
 * any component from it
 * @param manager ecs::Manager
 */
ecs::System::System(ecs::Manager &manager) : m_manager(manager)
{
}

/**
 * Update any entity linked to the system
 * @param updateTime time laps the system need to update each entity
 */
void ecs::System::updateEntities(float updateTime) {
	for (auto elem = m_entities.begin(); elem != m_entities.end();)
		updateEntity(updateTime, *elem++);
}

/**
 * get the needed Components for this system
 * It contains every Component that is update by this system
 * @return needed Components for this system
 */
const std::vector<std::set<ecs::ComponentType>> &ecs::System::getNeededComponents() const
{
    return m_neededComponents;
}

/**
 * remove an Entity from this system. So it will no longeur update it
 * @param entity The Entity to remove
 */
size_t ecs::System::removeEntity(ecs::Entity entity)
{
	if (m_entities.find(entity) == m_entities.end())
		throw (std::runtime_error("there is no such Entity registered"));
	return m_entities.erase(entity);
}

/**
 * Check if the Entity is updated by the System
 * @param entity the Entity to check
 * @return true or false if it updated by this system
 */
bool ecs::System::hasEntity(ecs::Entity entity) const
{
	return m_entities.find(entity) != m_entities.end();
}

/**
 * Add an Entity to the System so it will update it
 * @param entity The Entity to add
 */
void ecs::System::addEntity(ecs::Entity entity)
{
	if (m_entities.find(entity) != m_entities.end())
		throw (std::runtime_error("Entity already registered"));
	m_entities.insert(entity);
}

/**
 * Set the need Component
 * @param elem a std::set container that contain every needed Component
 */
void ecs::System::setNeededComponent(std::set<ComponentType> elem)
{
	m_neededComponents.push_back(std::move(elem));
}

/**
 * Get entity if systeme need to interact with them
 * @return linked entity to this system
 */
const std::set<ecs::Entity> &ecs::System::getEntities() const
{
	return m_entities;
}
