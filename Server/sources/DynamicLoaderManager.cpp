/*
** EPITECH PROJECT, 2018
** Epitech scolarship project (4 years remaining)
** File description:
**      Made on 2018/11 by ebernard
*/

#include <experimental/filesystem>
#include "DynamicLoaderManager.hpp"

game::DynamicLoaderManager::DynamicLoaderManager() {
    try {
        for (auto &p : std::experimental::filesystem::directory_iterator("./Monsters"))
            m_libsToLoad.emplace_back(p.path());
    } catch (std::exception &e) {
        /* ServerTest */
        for (auto &p : std::experimental::filesystem::directory_iterator("../Monsters"))
            m_libsToLoad.emplace_back(p.path());
    }
}


game::DynamicLoaderManager::~DynamicLoaderManager() {
	for (auto  &elem : m_loaders)
		elem.second.closeDl();
}

void game::DynamicLoaderManager::loadLibs() {
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

IEnnemy::Ptr game::DynamicLoaderManager::getMonster(std::string &type) {
	if (m_loaders.find(type) == m_loaders.end())
		return nullptr;
	return  m_loaders[type].call<IEnnemy::Ptr>("getMonsterLibrary");
}

std::vector<network::EntityInfo> game::DynamicLoaderManager::getInit() {
	std::vector<network::EntityInfo> init;

	for (auto &lib : m_loaders) {
		init.push_back(lib.second.call<IEnnemy::Ptr>("getMonsterLibrary")->getInit());
	}
	return init;
}
