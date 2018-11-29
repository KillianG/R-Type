/*
** EPITECH PROJECT, 2018
** Epitech scolarship project (4 years remaining)
** File description:
**      Made on 2018/11 by ebernard
*/

#include "../includes/DynamicLoaderManager.hpp"

game::DynamicLoaderManager::DynamicLoaderManager()
{
	m_libsToLoad.emplace_back("./Monsters/lib_bird.so");
	m_libsToLoad.emplace_back("./Monsters/lib_bird2.so");
}

void game::DynamicLoaderManager::loadLibs()
{
	DynamicLoader d;

	try {
		for (auto &lib : m_libsToLoad) {
			d = DynamicLoader(lib);
			m_loaders.emplace(d.call<std::string>("getName"), d);
		}
	} catch (std::logic_error &e) {
		for (auto &lib : m_libsToLoad) {
			d = DynamicLoader("." + lib);
			m_loaders.emplace(d.call<std::string>("getName"), d);
		}

	}
}

IEnnemy::Ptr game::DynamicLoaderManager::getMonster(std::string &type)
{
	return  m_loaders[type].call<IEnnemy::Ptr>("getMonsterLibrary");
}

std::vector<network::EntityInfo> game::DynamicLoaderManager::getInit()
{
	std::vector<network::EntityInfo> init;

	for (auto &lib : m_loaders) {
		init.push_back(lib.second.call<network::EntityInfo>("getInit"));
	}
	return init;
}
