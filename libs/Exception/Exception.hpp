//
// Created by prat on 07/11/18.
//

#ifndef R_TYPE_EXCEPTION_HPP
#define R_TYPE_EXCEPTION_HPP

#include <exception>
#include <iostream>

namespace rtype {
	class Exception : public std::exception {
	public:
		explicit Exception(std::string msg);
		virtual ~Exception() = default;
		const std::string getErrorMsg() const;
		const char* what() const noexcept;

	private:
		std::string errorMsg;
	};
}

#endif //R_TYPE_EXCEPTION_HPP
