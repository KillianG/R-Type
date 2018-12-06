//
// EPITECH PROJECT, 2018
// oui
// File description:
// DynamicLoader Class header
//

#pragma once

#include <dlfcn.h>
#include <string>
#include <functional>

class DynamicLoader {
public:
	DynamicLoader() = default;
	explicit DynamicLoader(std::string const &dlname);
	void closeDl();

	template<typename Ret, typename ... Params>
	Ret call(std::string const &functionName, const Params& ... par) const {
		void *sym = dlsym(handle, functionName.c_str());
		if (!sym)
			throw std::logic_error(dlerror());
		Ret (*ptr_f)(Params...);
		*(void **) (&ptr_f) = sym;
		return (ptr_f(par...));
	}

	template<typename Ret, typename ... Params>
	std::function<Ret (Params...)> get(std::string const &functionName) const {
		void *sym = dlsym(handle, functionName.c_str());
		if (!sym)
			throw std::logic_error(dlerror());
		std::function<Ret(const Params &...)> f;
		f = [sym](const Params &... par) -> Ret {
			Ret(*ptr_f)(Params...);
			*(void **) (&ptr_f) = sym;
			return (ptr_f(par...));
		};
		return (f);
	}
private:
	void *handle;
};