/*
** EPITECH PROJECT, 2018
** Epitech scolarship project (4 years remaining)
** File description:
**      Made on 2018/11 by ebernard
*/

#ifndef R_TYPE_MANAGER_HPP
#define R_TYPE_MANAGER_HPP

#include <memory>
#include <map>
#include <vector>
#include "utiles.hpp"
#include "System.hpp"
#include "ComponentManager.hpp"

namespace ecs {
    /**
     * a class that manage the ecs environment
     * So it create and manage his own Entity
     * that has there Components updated by systems
     */
    class Manager {
    public:
        Manager() = default;

        Entity createEntity();

        void removeEntity(Entity entity);

        void registerEntity(ecs::Entity entity);

        void updateSystems(float updateTime);

        void addSystem(System::Ptr system);

        void removeSystem(System::Ptr system);

        /**
         * Create a ComponentManager and store it.
         * With C::m_type as key and the pointer as data
         * @tparam C The Component type for the ComponentManager to creat
         */
        template<typename C>
        void createComponentManager() {
            static_assert(std::is_base_of<Component, C>::value, "C must derived from the Component struct");
            static_assert(C::m_type != unsetComponentType, "C must define a valid non-zero m_type");

            m_componentManager[C::m_type] = IComponentManager::Ptr(new ComponentManager<C>());
        }

        /**
         * Get the ComponentManager for a Given Component
         * @tparam C The Component type for the ComponentManager
         * @return a ref to the ComponentManager
         */
        template<typename C>
        ComponentManager<C> &getComponentManager() {
            static_assert(std::is_base_of<Component, C>::value, "C must derived from the Component struct");
            static_assert(C::m_type != unsetComponentType, "C must define a valid non-zero m_type");

            if (m_componentManager.find(C::m_type) == m_componentManager.end())
                throw std::runtime_error(
                        std::string("there is no ComponentManager of type: ") + std::to_string(C::m_type));
            return reinterpret_cast<ComponentManager<C> &>(*(m_componentManager.at(C::m_type)));
        }

        /**
         * add a component to his ComponentManager for a given Entity
         * @tparam C The Component type for the ComponentManager
         * @param entity the Entity  link with the Component
         * @param component the Component to be added
         */
        template<typename C>
        void addComponent(Entity entity, C &&component) {
            static_assert(std::is_base_of<Component, C>::value, "C must derived from the Component struct");
            static_assert(C::m_type != unsetComponentType, "C must define a valid non-zero m_type");

            if (m_componentManager.find(C::m_type) == m_componentManager.end())
                throw std::runtime_error("there is no componentManger set for this id");

            auto &manager = reinterpret_cast<ComponentManager<C> &>(*(m_componentManager[C::m_type]));
            manager.addComponent(entity, std::move(component));
            m_entities[entity].insert(C::m_type);
        }

        template<typename C>
        void addComponent(Entity entity, C &component) {
            static_assert(std::is_base_of<Component, C>::value, "C must derived from the Component struct");
            static_assert(C::m_type != unsetComponentType, "C must define a valid non-zero m_type");

            if (m_componentManager.find(C::m_type) == m_componentManager.end())
                throw std::runtime_error("there is no componentManger set for this id");

            auto &manager = reinterpret_cast<ComponentManager<C> &>(*(m_componentManager[C::m_type]));
            manager.addComponent(entity, std::move(component));
            m_entities[entity].insert(C::m_type);
        }

    private:
        Entity m_nbEntity { 1 };

        std::vector<System::Ptr> m_systems;
        std::map<ComponentType, IComponentManager::Ptr> m_componentManager;
        std::unordered_map<Entity, std::set<ComponentType>> m_entities;
    };
}

#else

namespace ecs{
    class Manager;
}


#endif //R_TYPE_MANAGER_HPP
