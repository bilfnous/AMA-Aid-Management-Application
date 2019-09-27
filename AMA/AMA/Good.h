/*
*	Final Project Milestone 3 - Error Module
*	Good.h
*	Date 2019-07-06
*	Auther B. Alfanous
*/

#ifndef AMA_GOOD_H
#define AMA_GOOD_H

#include "Error.h"

namespace ama {
	const int max_sku_length = 7;
	const int max_unit_length = 10;
	const int max_name_length = 75;
	const double tax_rate = 0.13;

	class Good {
	
		char m_productType;
		char ma_sku[max_sku_length + 1];
		char ma_unit[max_unit_length + 1];
		char* mp_goodName;
		int m_qtyOnHand;
		int m_qtyNeeded;
		double m_price;
		bool m_taxable;
		Error mo_error; // Holds the error state of the Goodobject.

	protected:
		void name(const char*);
		const char* name() const;
		const char* sku() const;
		const char* unit() const;
		bool taxed() const;
		double itemPrice() const;
		double itemCost() const;
		void message(const char*);
		bool isClear() const;

	public:
		Good(char gType = 'N');
		Good(const char* gsku, const char* gName, const char* gUnit, int gOnHand = 0, bool gTaxable = true, double gPrice = 0.0, int gNeeded = 0);
		Good(const Good &src);
		~Good();
		Good& operator=(const Good & src);
		std::fstream& store(std::fstream& file, bool newLine = true) const;
		std::fstream& load(std::fstream& file);
		std::ostream& write(std::ostream& os, bool linear = true) const;
		std::istream& read(std::istream& is);
		bool operator==(const char*) const;
		double total_cost() const;
		void quantity(int);
		bool isEmpty() const;
		int qtyNeeded() const;
		int quantity() const;
		bool operator>(const char*) const;
		bool operator>(const Good&) const;
		int operator+=(int);
	};

	std::ostream& operator<<(std::ostream&, const Good&);
	std::istream& operator>>(std::istream&, Good&);
	double operator+=(double&, const Good&);
}

#endif
