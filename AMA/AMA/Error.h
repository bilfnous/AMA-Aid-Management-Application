/*
*	Final Project Milestone 1 - Error Module
*	Error.h
*	Date 2019-07-01
*	Auther B. Alfanous
*/

#include <iostream>

#ifndef AMA_ERROR_H
#define AMA_ERROR_H

namespace ama {

	class Error {
		char* m_errorMessage; //stores the address of the message, if any, in the current instance.

	public:
		explicit Error(const char* errorMessage = nullptr);
		void clear();
		bool isClear() const;
		void message(const char* pText);
		const char* message() const;
		~Error();
	
	};
	std::ostream& operator<<(std::ostream&, const Error&);
}

#endif
