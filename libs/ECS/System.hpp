/*
** EPITECH PROJECT, 2018
** Epitech scolarship project (4 years remaining)
** File description:
**      Made on 2018/11 by ebernard
*/

#pragma once

#include <set>
#include <vector>
#include <memory>
#include "utiles.hpp"

namespace ecs
{
	class Manager;
	/**
	 * Update Component linked to given Entity
	 */
	class System {
	public:
		typedef std::shared_ptr<System> Ptr;

		explicit System(Manager &manager);

		virtual void updateEntities(float updateTime);
		virtual void updateEntity(float updateTime, Entity entity) = 0;

		const std::vector<std::set<ComponentType>> &getNeededComponents() const;

		void addEntity(Entity);
		size_t removeEntity(Entity);
		bool hasEntity(Entity) const;
	protected:
		const std::set<Entity> &getEntities() const;
		void setNeededComponent(std::set<ComponentType>);

		Manager &m_manager;
		std::set<Entity> m_entities;
	private:
		std::vector<std::set<ComponentType>> m_neededComponents;
	};
}