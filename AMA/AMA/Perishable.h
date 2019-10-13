/*
*	Final Project Milestone 5 - Perishable Module
*	Good.cpp
*	Date 2019-09-02
*	Auther B. Alfanous
*/

#ifndef AMA_PERISHABLE_H
#define AMA_PERISHABLE_H

#include "Good.h"
#include "Date.h"

namespace ama {

	class Perishable : public Good {
		Date mo_date;

	public:
		Perishable(char pType = 'P');
		std::fstream& store(std::fstream& file, bool newLine = true) const;
		std::fstream& load(std::fstream& file);
		std::ostream& write(std::ostream& os, bool linear) const;
		std::istream& read(std::istream& is);
		const Date& expiry() const;
	};
	iGood* CreateProduct(char tag);
}
#endif
