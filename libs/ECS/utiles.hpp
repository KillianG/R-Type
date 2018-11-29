/*
** EPITECH PROJECT, 2018
** Epitech scolarship project (4 years remaining)
** File description:
**      Made on 2018/11 by ebernard
*/

#ifndef R_TYPE_UTILES_HPP
#define R_TYPE_UTILES_HPP

#include <cstddef>

namespace ecs
{
	using Entity=std::size_t;
	using ComponentType=std::size_t;
	static constexpr ComponentType unsetComponentType = 0;

	/**
	 * Base struct for all Component
	 * m_type is an unique id for each Component. It must be UNIQUE
	 * #TODO static function that automatically give this id
	 */
	struct Component
	{
	public:
		static const ComponentType m_type = ecs::unsetComponentType;;
	};
}


#endif //R_TYPE_UTILES_HPP
