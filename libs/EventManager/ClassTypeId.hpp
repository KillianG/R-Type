#pragma once

#include <cstddef>

/**
 * @brief Give a unique identifier to a Type
 * @tparam Group Permit to create multiples groups of identifier
 */
template<typename Group>
class ClassTypeId {
public:
	using TypeId = std::size_t;
public:
	explicit ClassTypeId() = delete;

	/**
	 * @brief Give a unique identifier to a type
	 * @tparam NewType create one function per type used in the code
	 * @return The unique identifier of the given type(NewType)
	 */
	template<typename NewType>
	static inline TypeId getTypeId() noexcept {
		/**
	 	 * Each function will increment the static member { typeIdCounter } only once
	 	 * due to the static declaration inside this function
	 	 */
		static TypeId id{ generateTypeId() };

		return id;
	}

private:
	static inline TypeId generateTypeId() noexcept {
		/**
		 * Each group will have his own typeIdCounter
		 */
		static TypeId typeIdCounter{ 0 };

		return typeIdCounter++;
	}
};