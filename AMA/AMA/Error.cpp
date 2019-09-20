/*
*	Final Project Milestone 2 - Error Module
*	Error.cpp
*	Date 2019-07-03
*	Auther B. Alfanous
*/

/*
		The Error class manages the error state of client code and encapsulates the last error message. 
		Any client can define and store an Error object. If a client encounters an error, the client can 
	set its Error object to an appropriate message. The client specifies the length of the message. 
		The Error object reports whether or not any error has occurred. 
		The isClear() query on the object reports if an error has occurred. If an error has occurred, 
	the object can display the message associated with that error. The object can be send its message
	to an std::ostream object.
*/

#define _CRT_SECURE_NO_WARNINGS

#include <cstring>
#include <iostream>
#include <string>
#include "Error.h"


using namespace std;
namespace ama {
	Error::Error(const char* _errorMessage) {
		if (_errorMessage == nullptr || strcmp(_errorMessage, "") == 0) {
			clear();
		}
		else {
			message(_errorMessage);
		}
	}

	Error::~Error() {
		delete[] m_errorMessage;
		m_errorMessage = nullptr;
	}

	/*
		This function stores a copy of the C-style string pointed to by str. 
		De-allocates any memory allocated for a previously stored message.
		If str points to a non-empty message, this function allocates the dynamic memory 
		needed to store a copy of str and copies the message into that memory with null terminator at the end.
		If str points to an empty message, this function puts the current object in a safe empty state.
	*/
	void Error::message(const char* pText) {
		if (pText != nullptr) {
			if (m_errorMessage != nullptr) {
				clear();
			}
			m_errorMessage = new char[strlen(pText) + 1];
			strncpy(m_errorMessage, pText, strlen(pText));
			if (m_errorMessage[strlen(pText)] != '\0')
				m_errorMessage[strlen(pText)] = '\0';
		}
		else {
			m_errorMessage = nullptr;
		}
	}

	/* 
		This query returns the address of the message stored in the current object.
		If the object is in the safe empty state, this function returns nullptr.
	*/
	const char* Error::message() const {
		if (m_errorMessage == nullptr || strlen(m_errorMessage) == 0)
			return nullptr;
		return m_errorMessage;
	}
	/*
		This function clears any message stored by the current object and initializes 
		the object to a safe empty state.
	*/
	void Error::clear() {
		delete[] m_errorMessage;
		m_errorMessage = nullptr;
	}

	/*
		This query returns true if the current object is in a safe empty state.
	*/
	bool Error::isClear() const {
		if (m_errorMessage == nullptr || strlen(m_errorMessage) == 0)
			return true;
		return false;
	}

	/*
		This operator sends an Error message, if one exists, to an std::ostream object 
		and returns a reference to the std::ostream object.
		If no message exists, this operator does not send anything to 
		the std::ostream object and returns a reference to the std::ostream object.
	*/
	std::ostream& operator<< (std::ostream& os, const Error& em) {
		if (em.message() != nullptr) {
			os << em.message();
		}
		return os;
	}

}
