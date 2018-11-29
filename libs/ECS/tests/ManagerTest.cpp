/*
** EPITECH PROJECT, 2018
** Epitech scolarship project (4 years remaining)
** File description:
**      Made on 2018/11 by ebernard
*/

#include "catch.hpp"
#include "../Manager.hpp"
#include "../System.hpp"

struct ComponentTest3 : public ecs::Component
{
public:
	static const ecs::ComponentType m_type;

	explicit ComponentTest3(std::size_t value) {
		m_value = value;
	}
	float m_value;
};

const ecs::ComponentType  ComponentTest3::m_type = 3;

struct ComponentTest4 : public ecs::Component
{
public:
	static const ecs::ComponentType m_type;

	explicit ComponentTest4(std::size_t value1, std::size_t value2) {
		m_value1 = value1;
		m_value2 = value2;
	}
	float m_value1;
	float m_value2;
};

const ecs::ComponentType  ComponentTest4::m_type = 4;

class SystemTest3 : public ecs::System
{
public:
	explicit SystemTest3(ecs::Manager &manager) : System(manager) {
		std::set<ecs::ComponentType> comp;

		comp.insert(ComponentTest3::m_type);
		setNeededComponent(std::move(comp));
	}
	void updateEntity(float updatetime, ecs::Entity entity) override {
		auto &elem = m_manager.getComponentManager<ComponentTest3>().getComponent(entity);
		elem.m_value += updatetime;
	}
};

class SystemTest4 : public ecs::System
{
public:
	explicit SystemTest4(ecs::Manager &manager) : System(manager) {
		std::set<ecs::ComponentType> comp;

		comp.insert(ComponentTest3::m_type);
		comp.insert(ComponentTest4::m_type);
		setNeededComponent(std::move(comp));
	}

	void updateEntity(float updatetime, ecs::Entity entity) override
	{
		auto &elem1 = m_manager.getComponentManager<ComponentTest3>().getComponent(entity);
		auto &elem2 = m_manager.getComponentManager<ComponentTest4>().getComponent(entity);
		elem1.m_value += updatetime;
		elem2.m_value1 += updatetime * 2;
		elem2.m_value2 += updatetime * 2;
	}
};

TEST_CASE("ManagerTest", "[ECS]") {
	ecs::Entity entity1;
	ecs::Entity entity2;
	ecs::Entity entity3;

	SECTION("Entity Test") {
		ecs::Manager manager;
		entity1 = manager.createEntity();
		entity2 = manager.createEntity();
		entity3 = manager.createEntity();
		REQUIRE(entity1 == 1);
		REQUIRE(entity2 == 2);
		REQUIRE(entity3 == 3);
	}
	SECTION("TEST FOR ONE ENTITY"){
		ecs::Manager manager;
		entity1 = manager.createEntity();
		entity2 = manager.createEntity();
		auto sys3 = ecs::System::Ptr(new SystemTest3(manager));
		auto sys4 = ecs::System::Ptr(new SystemTest4(manager));
		REQUIRE(entity1 == 1);
		REQUIRE(entity2 == 2);
		REQUIRE_NOTHROW(manager.createComponentManager<ComponentTest3>());
		REQUIRE_THROWS_AS(manager.getComponentManager<ComponentTest4>(), std::runtime_error);
		REQUIRE_NOTHROW(manager.getComponentManager<ComponentTest3>());

		REQUIRE_NOTHROW(manager.addSystem(sys3));

		REQUIRE_NOTHROW(manager.addComponent<ComponentTest3>(entity1, ComponentTest3(1.0f)));
		REQUIRE_NOTHROW(manager.registerEntity(entity1));
		REQUIRE_NOTHROW(manager.registerEntity(entity2));
		REQUIRE_NOTHROW(manager.updateSystems(1.0f));
		REQUIRE(manager.getComponentManager<ComponentTest3>().getComponent(entity1).m_value == 2.0f);

		REQUIRE_NOTHROW(manager.createComponentManager<ComponentTest4>());
		REQUIRE_NOTHROW(manager.getComponentManager<ComponentTest4>());
		REQUIRE_NOTHROW(manager.addSystem(sys4));
		REQUIRE_NOTHROW(manager.addComponent<ComponentTest4>(entity1, ComponentTest4(0.0f, 1.0f)));
		REQUIRE_NOTHROW(manager.registerEntity(entity1));
		REQUIRE_NOTHROW(manager.updateSystems(1.0f));
		REQUIRE(manager.getComponentManager<ComponentTest3>().getComponent(entity1).m_value == 4.0f);
		REQUIRE(manager.getComponentManager<ComponentTest4>().getComponent(entity1).m_value1 == 2.0f);
		REQUIRE(manager.getComponentManager<ComponentTest4>().getComponent(entity1).m_value2 == 3.0f);

		REQUIRE_NOTHROW(manager.removeEntity(entity1));
		REQUIRE_NOTHROW(manager.updateSystems(2.0f));
		REQUIRE(manager.getComponentManager<ComponentTest3>().getComponent(entity1).m_value == 4.0f);
		REQUIRE(manager.getComponentManager<ComponentTest4>().getComponent(entity1).m_value1 == 2.0f);
		REQUIRE(manager.getComponentManager<ComponentTest4>().getComponent(entity1).m_value2 == 3.0f);

		REQUIRE_NOTHROW(manager.removeEntity(entity2));
		REQUIRE(manager.getComponentManager<ComponentTest3>().getComponent(entity1).m_value == 4.0f);
		REQUIRE(manager.getComponentManager<ComponentTest4>().getComponent(entity1).m_value1 == 2.0f);
		REQUIRE(manager.getComponentManager<ComponentTest4>().getComponent(entity1).m_value2 == 3.0f);

		REQUIRE_NOTHROW(manager.removeSystem(sys3));
		REQUIRE_NOTHROW(manager.removeSystem(sys4));
	}
	SECTION("TEST WITH TOW ENTITY") {
		ecs::Manager manager;
		entity1 = manager.createEntity();
		entity2 = manager.createEntity();
		auto sys3 = ecs::System::Ptr(new SystemTest3(manager));
		auto sys4 = ecs::System::Ptr(new SystemTest4(manager));
		REQUIRE(entity1 == 1);
		REQUIRE(entity2 == 2);
		REQUIRE_NOTHROW(manager.createComponentManager<ComponentTest3>());
		REQUIRE_NOTHROW(manager.createComponentManager<ComponentTest4>());
		REQUIRE_NOTHROW(manager.getComponentManager<ComponentTest4>());
		REQUIRE_NOTHROW(manager.getComponentManager<ComponentTest3>());

		REQUIRE_NOTHROW(manager.addSystem(sys3));
		REQUIRE_NOTHROW(manager.addSystem(sys4));

		REQUIRE_NOTHROW(manager.addComponent<ComponentTest3>(entity1, ComponentTest3(1.0f)));
		REQUIRE_NOTHROW(manager.addComponent<ComponentTest4>(entity1, ComponentTest4(0.0f, 1.0f)));
		REQUIRE_NOTHROW(manager.registerEntity(entity1));
		REQUIRE_NOTHROW(manager.registerEntity(entity2));
		REQUIRE_NOTHROW(manager.updateSystems(1.0f));
		REQUIRE(manager.getComponentManager<ComponentTest3>().getComponent(entity1).m_value == 3.0f);

		REQUIRE_NOTHROW(manager.removeSystem(sys3));
		REQUIRE_NOTHROW(manager.removeSystem(sys4));
	}
}
