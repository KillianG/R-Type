/*
** EPITECH PROJECT, 2018
** Epitech scolarship project (4 years remaining)
** File description:
**      Made on 2018/11 by ebernard
*/

#include "catch.hpp"
#include "System.hpp"
#include "utilesBase.hpp"
#include "Manager.hpp"

class SystemTest1 : public ecs::System
{
public:
	explicit SystemTest1(ecs::Manager &manager) : System(manager) {
	}
	void updateEntity(float updatetime, ecs::Entity entity) override {

	}

};

TEST_CASE("System", "[ECS]") {
	ecs::Manager manager;
	ecs::Entity entity1 = 1;
	ecs::Entity entity2 = 2;
	ecs::System::Ptr system1 = std::shared_ptr<SystemTest1>(new SystemTest1(manager));

	SECTION("one Component") {
		REQUIRE_FALSE(system1->hasEntity(entity1));
		REQUIRE_NOTHROW(system1->addEntity(entity1));
		REQUIRE(system1->hasEntity(entity1));
	}

	SECTION("more Component") {
		REQUIRE_FALSE(system1->hasEntity(entity1));
		REQUIRE_FALSE(system1->hasEntity(entity2));

		REQUIRE_NOTHROW(system1->addEntity(entity1));
		REQUIRE(system1->hasEntity(entity1));
		REQUIRE_FALSE(system1->hasEntity(entity2));

		REQUIRE_NOTHROW(system1->removeEntity(entity1));
		REQUIRE_FALSE(system1->hasEntity(entity1));
		REQUIRE_FALSE(system1->hasEntity(entity2));

		REQUIRE_NOTHROW(system1->addEntity(entity1));
		REQUIRE_NOTHROW(system1->addEntity(entity2));
		REQUIRE(system1->hasEntity(entity1));
		REQUIRE(system1->hasEntity(entity2));

		REQUIRE_NOTHROW(system1->removeEntity(entity2));
		REQUIRE(system1->hasEntity(entity1));
		REQUIRE_FALSE(system1->hasEntity(entity2));

		REQUIRE_NOTHROW(system1->removeEntity(entity1));
		REQUIRE_FALSE(system1->hasEntity(entity1));
		REQUIRE_FALSE(system1->hasEntity(entity2));
	}
}
