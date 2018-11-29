/*
** EPITECH PROJECT, 2018
** Epitech scolarship project (4 years remaining)
** File description:
**      Made on 2018/11 by ebernard
*/

#ifndef R_TYPE_DYNAMICLOADERMANAGER_HPP
#define R_TYPE_DYNAMICLOADERMANAGER_HPP

#include <map>
#include "DynamicLoader.hpp"
#include "../Monsters/includes/IEnnemy.hpp"

namespace game
{
	class DynamicLoaderManager
	{
	public:
		DynamicLoaderManager();

		void loadLibs();
		IEnnemy::Ptr getMonster(std::string &type);
		std::vector<network::EntityInfo> getInit();

	private:
		std::map<std::string, DynamicLoader> m_loaders;
		std::vector<std::string> m_libsToLoad;
	};
}

#endif //R_TYPE_DYNAMICLOADERMANAGER_HPP
