//
// EPITECH PROJECT, 2018
// Oui
// File description:
// oui
//

#include <dlfcn.h>
#include <iostream>
#include <Server/includes/DynamicLoader.hpp>

#include "../includes/DynamicLoader.hpp"

DynamicLoader::DynamicLoader(std::string const &dlname) {
	std::string name = (dlname.find('/') == std::string::npos) ? "./" + dlname : dlname;

	handle = dlopen(name.c_str(), RTLD_NOW);
	if (!handle) {
		std::cerr << "Error while loading " << dlname << std::endl;
		throw std::logic_error(dlerror());
	}
}
void DynamicLoader::closeDl()
{
	dlclose(handle);
}
