/*
** EPITECH PROJECT, 2018
** Epitech scolarship project (4 years remaining)
** File description:
**      Made on 2018/11 by ebernard
*/

#ifndef R_TYPE_NETWORKUTILS_HPP
#define R_TYPE_NETWORKUTILS_HPP

#include <cstddef>
#include <string>
#include <vector>
#include "../../Server/includes/Utils.hpp"
#include "../ECS/utiles.hpp"
#include "../EventManager/BaseEvent.hpp"

namespace network
{
	/**
	 * Data structure for the entity type GFX information (mainly sprite path)
	 * These data are for the gfx environment
	 */
	struct EntityInfo {
		EntityInfo(ecs::Entity e, std::string p, int x, int y) : entityType(e), path(p), sizeX(x), sizeY(y){};
		EntityInfo(ecs::Entity e, std::string p, Game::box size) : entityType(e), path(p), sizeX(size.width), sizeY(size.height){};
		std::string to_str() {
			std::string str;

			str += "type: " + std::to_string(entityType) + " ";
			str += "sprite:" + path + " ";
			str += "size: " + std::to_string(sizeX) + " " + std::to_string(sizeY);
			return str;
		}
		ecs::Entity entityType;
		std::string path;

		int sizeX;
		int sizeY;
	};

	/**
	 * Data structure for every printable entity
	 * Pos and type
	 * These data are for the gfx environment
	 */
	struct EntityPos {
		EntityPos(ecs::Entity e, size_t type, size_t time, float mx, float my) : entityId(e), entityType(type), animTime(time), X(mx), Y(my) {}
		EntityPos(std::string e, std::string type, std::string animT, std::string mx, std::string my) : entityId(stoi(e)), entityType(stoi(type)), animTime(stoi(animT)), X(stof(mx)), Y(stof(my)){}
		std::string to_str() const
		{
			std::string req;

			req += "id: " + std::to_string(entityId) + " ";
			req += "type: " + std::to_string(entityType) + " ";
			req += "animTime: " + std::to_string(animTime) + " ";
			req += "pos: " + std::to_string(X) + " " + std::to_string(Y);
			return req;
		}
		ecs::Entity entityId;
		ecs::Entity entityType;
		size_t animTime;
		float X;
		float Y;
	};

	/**
	 * Rfc event triggerd in the main client class
	 */
	struct RfcInfoEvent : BaseEvent
	{
		std::vector<EntityInfo> data;
	};

	struct RfcUpdateEvent : BaseEvent
	{
		std::vector<EntityPos> data;
	};

	/**
	 * Data structure for the request
	 * mainly used by the Rfc encapsulation
	 */
	struct requestInfo
	{
		int sender;
		std::string data;
	};

	struct gameInfo
	{
		int port;
		std::string ip;
	};

	enum class playerMove
	{
		UP,
		DOWN,
		RIGHT,
		LEFT,
		NONE
	};
}

#endif //R_TYPE_NETWORKUTILS_HPP
