/*
** EPITECH PROJECT, 2018
** Epitech scolarship project (4 years remaining)
** File description:
**      Made on 2018/11 by ebernard
*/

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "catch.hpp"
#include "../ComponentManager.hpp"
#include "utilesBase.hpp"

struct ComponentTest1 : public ecs::Component
{
public:
	static const ecs::ComponentType m_type;

	explicit ComponentTest1(std::size_t value) {
		m_value = value;
	}
	std::size_t m_value;
};

const ecs::ComponentType  ComponentTest1::m_type = 1;

TEST_CASE("ComponentStore", "[ECS]") {
	SECTION("one Component") {
		ecs::ComponentManager<ComponentTest1> compManager;
		ecs::Entity entity = 1;

		REQUIRE_FALSE(compManager.hasEntity(entity));
		REQUIRE_NOTHROW(compManager.addComponent(entity, ComponentTest1(2.0f)));
		REQUIRE(compManager.hasEntity(entity));
		REQUIRE(ComponentTest1::m_type == 1);
	}

	SECTION("one Component") {
		ecs::ComponentManager<ComponentTest1> compManager;
		ecs::Entity entity1 = 1;
		ecs::Entity entity2 = 2;

		REQUIRE_FALSE(compManager.hasEntity(entity1));
		REQUIRE_FALSE(compManager.hasEntity(entity2));
		REQUIRE_FALSE(compManager.hasEntity(entity2));
		REQUIRE_NOTHROW(compManager.addComponent(entity1, ComponentTest1(2.0f)));
		REQUIRE(compManager.getComponent(entity1).m_value == 2.0f);

		REQUIRE_NOTHROW(compManager.addComponent(entity2, ComponentTest1(2.0f)));

		REQUIRE_NOTHROW(compManager.exctractEntity(entity1));
		REQUIRE_FALSE(compManager.hasEntity(entity1));
		REQUIRE(compManager.hasEntity(entity2));

		REQUIRE_NOTHROW(compManager.exctractEntity(entity2));
		REQUIRE_FALSE(compManager.hasEntity(entity1));
		REQUIRE_FALSE(compManager.hasEntity(entity2));
	}
}
