/*
*	Final Project Milestone 3 - Error Module
*	Good.cpp
*	Date 2019-07-06
*	Auther B. Alfanous
*/

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <iomanip>
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

	/*
		Destructor
	*/
	Good::~Good() {
		delete[] mp_goodName;
		mp_goodName = nullptr;
	}

	/*
		Copy Assignment
	*/
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
	
	/*
		This function receives the address of a C-style null-terminated string that holds the name of the Good. 
		This functionStores the name of the Goodin dynamicallyallocated memory;Replaces any namepreviously stored;
		If theincoming parameter is thenullptraddress, this function removes the name of the Good, if any, from memory.
	*/
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

	/*
		This  query  returns  the  address  of  the  C-style  null-terminated string that holds the name of the Good. 
		If the Goodhas no name, this query returns nullptr.
	*/
	const char* Good::name() const {
		return mp_goodName;
	}

	/*
		This query returns the address of the C-style null-terminated string that holds the SKUof the Good. 
	*/
	const char* Good::sku() const {
		return ma_sku;
	}

	/*
		This  query  returns  the  address  of  the  C-style  null-terminated string that holds the unit of the Good.
	*/
	const char* Good::unit() const {
		return ma_unit;
	}

	/*
		This query returns the taxable status of the Good.
	*/
	bool Good::taxed() const {
		return m_taxable;
	}

	/*
		This query returns the price of a single item of the Goodwithout tax.
	*/
	double Good::itemPrice() const {
		return m_price;
	}

	/*
		This query returns the price of a single item of the Goodplus any tax that applies to the Good.
	*/
	double Good::itemCost() const {
		return m_price * (1 + (taxed() ? tax_rate : 0));
	}


	/*
		This  functionreceives  the  address  of  a  C-style  null-terminated  string  holding  an  error  
		message  and  stores  that  message  in  the Errorobject to the current object.
	*/
	void Good::message(const char* msg) {
		mo_error.message(msg);
	}


	/*
		This  query  returns  true  if  the Errorobject  is  clear;  false otherwise.
	*/
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

	/*
		This query returns true if the object is in the empty state; false otherwise.
	*/
	bool Good::isEmpty() const {
		if (mp_goodName == nullptr)
			return true;
		return false;
	}

	/*
		This query that returns the number of units of the Goodthat are needed.
	*/
	int Good::qtyNeeded() const {
		return m_qtyNeeded;
	}

	/*
		This query returns the number of units of the Goodthat are on hand.
	*/
	int Good::quantity() const {
		return m_qtyOnHand;
	}

	/*
		 This modifier that receives an integer holding the number of units of the Goodthat are on hand.
		 If this number is positive-valued this function resets the number  of  units  that  are  on  
		 hand  to  the  number  received;  otherwise,  this  function does nothing.
	*/
	void Good::quantity(int qty) {
		if (qty > 0)
			m_qtyOnHand = qty;
	}


	/*
		This query returns true if the SKU attribute from the current instance
		is greater than the string stored at the received address
		(according to how the string comparison functions define ‘greater than’); false otherwise.
	*/
	bool Good::operator> (const char* sku) const {
		if (strcmp(this->sku(), sku) > 0)
			return true;
		return false;
	}

	/*
		This query returns true if the name of the current object is greater
		than the name of the Product received as parameter object
		(according to how the string comparison functions define ‘greater than’); false otherwise.
	*/
	bool Good::operator> (const Good& left) const {
		if (strcmp(this->name(), left.name()) > 0)
			return true;
		return false;
	}


	/*
		This modifier receives an integer identifying the number of units to be added
		to the available quantity attribute and returns the updated number of units on hand.
		If the integer received is positive-valued, this function adds it to the quantity on hand.
		If the integer is negative-valued or zero, this function does nothing and returns the quantity
		on hand (without modification).
	*/
	int Good::operator+=(int cnt) {
		if (cnt > 0) {
			m_qtyOnHand += cnt;
			return m_qtyOnHand;
		}
		return m_qtyOnHand;
	}

	/*
		This query returns true if the string specified in the parameter
		is the same as the string stored in the SKU attribute of the current instance;
		false otherwise.
	*/
	bool Good::operator==(const char* sku) const {
		if (strcmp(this->sku(), sku) == 0)
			return true;
		return false;
	}

	/*
		This query  receives  a  reference  to  an std::fstreamobject  and  an  optional  bool  and returns a 
		reference to the std::fstreamobject. This function 
			* inserts into the std::fstreamobject the character that identifies the Goodtype as the first field in the record. 
			* inserts into the std::fstreamobject the data for the current object incomma separated fields.
			* if the bool parameter is true, inserts a newline at the end of the record.
	*/
	std::fstream& Good::store(std::fstream& file, bool newLine) const {
		char taxed = 'N';

		if (m_taxable)
			taxed = 'Y';

		file << m_productType << "," << sku() << "," << name() << "," << unit() << ",";
		file << taxed << "," << itemCost() << "," << quantity() << "," << qtyNeeded();

		if (newLine)
			file << '\n';

		return file;
	}

	/*
		This modifier receives a reference to an std::fstreamobject  and  returns  a  reference  to  that std::fstreamobject.  
		This function:
			* extracts the fields for a single record from thestd::fstream objecto
			* creates a temporary object from the extracted field data 
			* copy assigns the temporaryobject to the current object.
	*/
	std::fstream& Good::load(std::fstream& file) {
		string temp;
		char sku[max_sku_length];
		char* name = new char[max_name_length + 1];
		char unit[max_unit_length + 1];
		char* tax = nullptr;
		double price;
		int qtyOnHand, qtyNeeded;
		bool taxable = true;

		getline(file, temp, ',');
		strcpy(sku, temp.c_str());

		getline(file, temp, ',');
		strcpy(name, temp.c_str());

		getline(file, temp, ',');
		strcpy(unit, temp.c_str());

		getline(file, temp, ',');
		strcpy(tax, temp.c_str());
		if (strcmp(tax, "Y") || strcmp(tax, "y"))
			taxable = true;
		else
			taxable = false;

		//stod() converts to double
		getline(file, temp, ',');
		price = stod(temp);

		getline(file, temp, ',');
		qtyOnHand = stoi(temp);

		getline(file, temp, ',');
		qtyNeeded = stoi(temp);

		if (!file.fail()) {
			Good temp = Good(sku, name, unit, qtyOnHand, taxable, price, qtyNeeded);
			*this = temp;
		}
		delete[] name;
		name = nullptr;
		delete[] tax;
		tax = nullptr;

		return file;
	}

	/*
		This query receives a  reference  to  an std::ostream object  and  a booland  returns  a  reference  to  the 
		std::ostreamobject. If the current object is in an error state, this function displays the  error  message.  
		If  the  current  object  is  empty,  this  function  does  not  display anything further and returns. 
		If the current object is not empty, this function inserts the data fields for the current object into the 
		std::ostream object in the following order and separates them by a vertical bar character (‘|’). 
		If the bool parameter is true,  the  output  is  on  a  single  line  with  the  field  widths.
	*/
	std::ostream& Good::write(std::ostream& os, bool linear) const {
		if (!isClear()) {
			os << mo_error.message();
			return os;
		}
		else if (isEmpty()) {
			return os;
		}
		else if (linear) {
			os << " " << std::right << setfill(' ') << setw(max_sku_length) << sku() << " | ";

			os << std::left;
			if (strlen(name()) > 20) {
				for (int i = 0; i < 17; i++)
					os << mp_goodName[i];
				os << "... | ";
			}
			else
				os << setfill(' ') << setw(16) << name() << " | ";

			os << std::right;
			os << setfill(' ') << setw(7);
			os.setf(ios::fixed);
			os.precision(2);
			os << itemCost() << " | ";

			os << setfill(' ') << setw(4) << quantity() << " | ";
			os << setfill(' ') << setw(10) << unit() << " | ";
			os << setfill(' ') << setw(4) << qtyNeeded() << " |";
		}
		else {
			os << "Sku: " << sku() << endl;
			os << "Name: " << name() << endl;
			os << "Price: ";
			os.setf(ios::fixed);
			os.precision(2);
			os << itemCost() << endl;
			os << "Quantity Available: " << quantity();
			os << "Quantity Needed: " << qtyNeeded();
		}
		return os;
	}

	/*
		This  modifier  receives  a  reference  to  an std::istreamobject  and  returns  a reference  to the 
		std::istreamobject.  This function extracts the data fields for the current object in the following order, 
		line by line.  This  function  stops  extracting  data  once  it  encounters  an  error.
			* If this function encounters an error for the Taxed input option, it setsthe failure bit  of  the 
			std::istreamobject  (calling std::istream::setstate(std::ios::failbit))and sets the error object to 
			the error message noted in brackets.
			* 15If the std::istreamobject is not in a failed state and this function encounters an error on 
			accepting Price input, it sets the error object to the error message noted in brackets.   
			The   function   that   reports   failure   of   an std::istreamobject   is std::istream::fail().
			* If the std::istreamobject is not in a failed state and this function encounters an error  on  the  
			Quantity  input,  it  sets  the  error  object  to  the  error  message  noted  in brackets.
			* If the std::istreamobject is not in a failed state and this function encounters an error on the 
			Quantity needed input, it sets the error object to the error message noted in brackets. 
			* If the std::istreamobject has accepted all input successfully, this function stores the  input  
			values  accepted  in  a  temporary  object  and  copy  assigns  it  to  the  current object. 
	*/
	std::istream& Good::read(std::istream& is) {
		string temp;
		char sku[max_sku_length];
		char* name = new char[max_name_length + 1];
		char unit[max_unit_length + 1];
		char tax;
		double price = 0.0;
		int qtyOnHand = 0, qtyNeeded = 0;
		bool taxable = true;

		//getline() extracts information from a string till it gets to the specified delimiter
		//.c_str() converts a string to a char array
		cout << "Sku: ";
		is >> sku;
		if (is.fail()) {
			is.setstate(std::ios::failbit);
			mo_error.message("<input value –C-style string>");
		}

		if (!(is.fail())) {
			cout << "Name (no spaces): ";
			is >> name;
			if (is.fail()) {
				is.setstate(std::ios::failbit);
				mo_error.message("<input value –C-style string>");
			}
		}

		if (!(is.fail())) {
			cout << "Unit: ";
			is >> unit;
			if (is.fail()) {
				is.setstate(std::ios::failbit);
				mo_error.message("<input value –C-style string>");
			}
		}

		if (!(is.fail())) {
			cout << "Taxed? (y/n): ";
			is >> tax;
			if (is.fail()) {
				is.setstate(std::ios::failbit);
				mo_error.message("<input character –y,Y,n, or N> [“Only (Y)es or (N)o are acceptable”]");
			}
			else if (tax == 'n' || tax == 'N') {
				taxable = false;
			}
		}

		if (!(is.fail())) {
			cout << "price: ";
			is >> price;
			if (is.fail()) {
				is.setstate(std::ios::failbit);
				mo_error.message("<input value –double> [“Invalid Price Entry”]");
			}
		}

		if (!(is.fail())) {
			cout << "Quantity on hand: ";
			is >> qtyOnHand;
			if (is.fail()) {
				is.setstate(std::ios::failbit);
				mo_error.message("<input value –integer> [“Invalid Quantity Entry”]");
			}
		}

		if (!(is.fail())) {
			cout << "Quantity needed: ";
			is >> qtyNeeded;
			if (is.fail()) {
				is.setstate(std::ios::failbit);
				mo_error.message("<input value –integer> [“Invalid Quantity Needed Entry”]");
			}
		}
		
		if (!is.fail()) {
			Good temp = Good(sku, name, unit, qtyOnHand, taxable, price, qtyNeeded);
			*this = temp;
		}
		delete[] name;
		name = nullptr;
		return is;
	}

	/*
		This helper receives a reference to an std::ostreamobjectand an unmodifiable reference 
		to a Goodobject and  returns  a  reference  to  the std::ostreamobject.  
		Your  implementation  of  this function will insert a Goodrecord into the std::ostream.
	*/
	std::ostream& operator<<(std::ostream& os, const Good& rhs) {
		return rhs.write(os);
	}

	/*
		std::istream& operator>>(std::istream&, Good&): This   helper   receives   a reference to 
		an std::istreamobject and a reference to a Goodobject and returns a 
		reference to the std::istreamobject. Your implementation of this function 
		extracts the Goodrecord from the std::istream.
	*/
	std::istream& operator>>(std::istream& is, Good& rhs) {
		return rhs.read(is);;
	}
	
	/* 
		This  helper  receives  a  reference  to  a doubleand an unmodifiable reference to a
		Good object and returns a double. Your implementation of this function adds the total 
		cost of the Goodobject to the doublereceivedand returns the updated double.
	*/
	double operator+=(double& cost, const Good& rhs) {
		return cost += (rhs.total_cost() * rhs.quantity());
	}

} // namespace ama
