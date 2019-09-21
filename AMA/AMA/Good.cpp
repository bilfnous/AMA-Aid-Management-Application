/*
*	Final Project Milestone 3 - Error Module
*	Good.cpp
*	Date 2019-07-06
*	Auther B. Alfanous
*/

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "Good.h"

using namespace std;
namespace ama {

	Good::Good(char gType) {
		m_productType = gType;
		ma_sku[0] = '\0';
		ma_unit[0] = '\0';
		mp_goodName = nullptr;
		m_qtyOnHand = 0;
		m_qtyNeeded = 0;
		m_price = 0.0;
		m_taxable = false;
	}

	Good::Good(const char* gsku, const char* gName, const char* gUnit, int gOnHand, bool gTaxable, double gPrice, int gNeeded) {
		strncpy(ma_sku, gsku, max_sku_length);
		ma_sku[max_sku_length] = '\0';

		name(gName);

		strncpy(ma_unit, gUnit, max_unit_length);
		ma_unit[max_unit_length] = '\0';

		m_qtyNeeded = gNeeded;
		m_qtyOnHand = gOnHand;
		m_price = gPrice;
		m_taxable = gTaxable;
	} // Good constructor 

	//Copy Constructor 
	Good::Good(const Good& src) {
		*this = src;
	}

	Good::~Good() {
		delete[] mp_goodName;
		mp_goodName = nullptr;
	}

	Good& Good::operator=(const Good &src) {
		if (this != &src) {
			strncpy(ma_sku, src.ma_sku, max_sku_length);
			ma_sku[max_sku_length] = '\0';

			name(src.mp_goodName);

			strncpy(ma_unit, src.ma_unit, max_unit_length);
			ma_unit[max_unit_length] = '\0';

			m_qtyNeeded = src.m_qtyNeeded;
			m_qtyOnHand = src.m_qtyOnHand;
			m_price = src.m_price;
			m_taxable = src.m_taxable;
		}
		return *this;
	}

	void Good::name(const char* src) {
		if (src != nullptr || strlen(src) > 0) {
			//delete product_name;
			mp_goodName = nullptr;
			size_t length = strlen(src);
			if (length > max_name_length) {
				mp_goodName = new char[max_name_length + 1];
				strncpy(mp_goodName, src, max_name_length);
				mp_goodName[max_name_length] = '\0';
			}
			else {
				mp_goodName = new char[length + 1];
				strncpy(mp_goodName, src, length);
				mp_goodName[length] = '\0';
			}
		}
		else {
			delete[] mp_goodName;
			mp_goodName = nullptr;
		}
	}// name

	const char* Good::name() const {
		return mp_goodName;
	}

	const char* Good::sku() const {
		return ma_sku;
	}

	const char* Good::unit() const {
		return ma_unit;
	}

	bool Good::taxed() const {
		return m_taxable;
	}

	double Good::itemPrice() const {
		return m_price;
	}

	double Good::itemCost() const {
		return m_price * (1 + tax_rate);
	}

	void Good::message(const char* msg) {
		mo_error.message(msg);
	}

	bool Good::isClear() const {
		return mo_error.isClear();
	}

	/*This query returns the total cost of all available units of product, including tax.*/
	double Good::total_cost() const {
		if (m_taxable) {
			return itemCost() * m_qtyOnHand;
		}
		return m_price;
	}

	/*this query returns true if the object is in the empty state; false otherwise.*/
	bool Good::isEmpty() const {
		if (mp_goodName == nullptr)
			return true;
		return false;
	}

	int Good::qtyNeeded() const {
		return m_qtyNeeded;
	}

	int Good::quantity() const {
		return m_qtyOnHand;
	}

	void Good::quantity(int qty) {
		if (qty > 0)
			m_qtyOnHand = qty;
	}


	/*This query returns true if the SKU attribute from the current instance
is greater than the string stored at the received address
(according to how the string comparison functions define ‘greater than’); false otherwise.*/
	bool Good::operator> (const char* sku) const {
		if (strcmp(this->sku(), sku) > 0)
			return true;
		return false;
	}

	/*This query returns true if the name of the current object is greater
	than the name of the Product received as parameter object
	(according to how the string comparison functions define ‘greater than’); false otherwise.*/
	bool Good::operator> (const Good& left) const {
		if (strcmp(this->name(), left.name()) > 0)
			return true;
		return false;
	}


	/*This modifier receives an integer identifying the number of units to be added
to the available quantity attribute and returns the updated number of units on hand.
If the integer received is positive-valued, this function adds it to the quantity on hand.
If the integer is negative-valued or zero, this function does nothing and returns the quantity
on hand (without modification).*/
	int Good::operator+=(int cnt) {
		if (cnt > 0) {
			m_qtyOnHand += cnt;
			return m_qtyOnHand;
		}
		return m_qtyOnHand;
	}

	/*This query returns true if the string specified in the parameter
is the same as the string stored in the SKU attribute of the current instance;
false otherwise.*/
	bool Good::operator==(const char* sku) const {
		if (strcmp(this->sku(), sku) == 0)
			return true;
		return false;
	}


	std::fstream& Good::store(std::fstream& file, bool newLine) const {
		
		return file;
	}

	std::fstream& Good::load(std::fstream& file) {
	
		return file;
	}

	std::ostream& Good::write(std::ostream& os, bool linear) const {
	
		return os;
	}

	std::istream& Good::read(std::istream& is) {
	
		return is;
	}


	std::ostream& operator<<(std::ostream& os, const Good& rhs) {
		
		return os;
	}

	std::istream& operator>>(std::istream& is, Good& rhs) {
		
		return is;
	}
	
	double operator+=(double& cost, const Good& rhs) {
		
		return cost;//TODO: updated double
	}


} // namespace ama
