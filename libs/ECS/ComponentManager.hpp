/*
** EPITECH PROJECT, 2018
** Epitech scolarship project (4 years remaining)
** File description:
**      Made on 2018/11 by ebernard
*/

#pragma once

#include <unordered_map>
#include <set>
#include <memory>
#include <algorithm>
#include "utiles.hpp"

namespace ecs
{
	/***
	 * A small hack so i can save every ComponentManager in a list
	 */
	class IComponentManager
	{
	public:
		using Ptr=std::shared_ptr<IComponentManager>;
		IComponentManager() = default;
	};

	/***
	 * A template class for each Component to manage there linked Entity
	 * Only one Component pear Entity
	 * @tparam C The type of Component save, it must inherit of the base struct Component
	 */
	template<typename C>
	class ComponentManager : public IComponentManager
	{
		static_assert(std::is_base_of<Component, C>::value, "C must derived from the Component struct");
	public:
		ComponentManager() = default;

		/**
		 * A small function that check if the Entity is part of the Component Store
		 * @param entity the Entity to check
		 * @return true or false if  the entity is part of the Component Store
		 */
		bool hasEntity(Entity entity) const {
			return m_components.find(entity) != m_components.end();
		}

		/**
		 * Add a Component linked to an Entity
		 * It raise an error if this Entity is already linked to a Component
		 * @param entity the Entity to linked to the Component
		 * @param Component The data linked to the Entity
		 */
        void addComponent(Entity entity, C &&component) {
            if (m_components.find(entity) != m_components.end())
                throw std::runtime_error("Entity is already registered");
            m_components.emplace(entity, std::move(component));
        }

		/**
		 * Get the Component for a define Entity
		 * @param entity linked to the Component
		 * @return The Component
		 */
		const C &getComponent(Entity entity) const {
			if (m_components.find(entity) == m_components.end())
				throw std::runtime_error("Entity need to be registered");
			return m_components.at(entity);
		}

		/**
		 * Get the Component for a define Entity
		 * @param entity linked to the Component
		 * @return The Component
		 */
		C &getComponent(Entity entity) {
			if (m_components.find(entity) == m_components.end())
				throw std::runtime_error("Entity need to be registered");
			return m_components.at(entity);
		}

		/**
		 * remove and return a the Component for a given Entity
		 * @param entity linked to the Component
		 * @return the Component removed
		 */
		C exctractEntity(Entity entity) {
			if (m_components.find(entity) == m_components.end())
				throw std::runtime_error("Entity must be linked to a component");
			auto component = m_components.at(entity);
			m_components.erase(entity);
			return component;
		}
	private:
		std::unordered_map<Entity, C> m_components;
	};
}
