/*
*	Final Project Milestone 5 - Perishable Module
*	Good.cpp
*	Date 2019-09-02
*	Auther B. Alfanous
*/

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <iomanip>
#include <fstream>
#include "Perishable.h"

using namespace std;
namespace ama {

	Perishable::Perishable(char pType) : Good(pType) {
	
	}

	std::fstream& Perishable::store(std::fstream& file, bool newLine) const {
		Good::store(file, false);
		file << "," << mo_date;
		if (newLine)
			file << "\n";
		return file;
	}

	std::fstream& Perishable::load(std::fstream& file) {
		Good::load(file);
		file << mo_date;
		return file;
	}

	std::ostream& Perishable::write(std::ostream& os, bool linear) const {
		Good::write(os, linear);
		if (Good::isClear() && !Good::isEmpty()) {
			if (linear)
				os << " " << std::right << mo_date << " |";
			else
				os << std::right << "Expiry Date: " << mo_date << endl;
		}
		return os;
	}

	std::istream& Perishable::read(std::istream& is) {
		Date temp;
		Good::read(is);
		
		cout << "Expiry date (YYYY/MM/DD): ";
		is >> temp;
		if (!(is.fail()))
			mo_date = temp;
		else if (is.fail()) {
			is.setstate(ios::failbit);
			message("Invalid Date Entry");
		}
		else if (temp.errCode() == YEAR_ERROR) {
			is.setstate(ios::failbit);
			message("Invalid Year in Date Entry");
		}
		else if (temp.errCode() == MON_ERROR) {
			is.setstate(ios::failbit);
			message("Invalid Month in Date Entry");
		}
		else if (temp.errCode() == DAY_ERROR) {
			is.setstate(ios::failbit);
			message("Invalid Day in Date Entry");
		}
		else if (temp.errCode() == PAST_ERROR) {
			is.setstate(ios::failbit);
			message("Invalid Expiry Datein Date Entry");
		}
				
		//is >> mo_date;
		is.ignore(1000, '\n');
		
		return is;
	}

	const Date& Perishable::expiry() const {
		return mo_date;
	}

	iGood* CreateProduct(char tag) {
		if (tag == 'N' || tag == 'n') {
			iGood* product = nullptr;
			product = new Good();
			return product;
		}
		else if (tag == 'P' || tag == 'p') {
			Perishable* perishable = nullptr;
			perishable = new Perishable();
			return perishable;
		}
		else {
			return nullptr;
		}
	}

}
