/*
*	Final Project Milestone 4 - iGood Module
*	iGood.h
*	Date 2019-09-27
*	Auther B. Alfanous
*/

/*
	The iGoodclass is  an  interface  that  exposes  the Good hierarchy  to  client  applications.  
	This class  is  abstract  and  cannot  be  instantiated.
*/

#include<iostream>

#ifndef AMA_iGood_H
#define AMA_iGood_H

namespace ama {

	class iGood {

	public:
		/*
			This query will receive a reference to an std::fstream object and an optional bool and return  a  
			reference  to  the std::fstreamobject.  The  bool  argument  will  specify whether   or   not   
			a   newline   should   be   inserted   after   each iGoodrecord. Implementations of this function 
			will insert the Goodrecords into the std::fstreamobject.
		*/
		virtual std::fstream& store(std::fstream& file, bool newLine = true) const = 0;

		/*
			This modifier will receive a reference to an std::fstreamobject  and  return  a  reference  to  
			that std::fstream object. Implementations of this function will extract iGood
			records from the std::fstreamobject.	
		*/
		virtual std::fstream& load(std::fstream& file) = 0;
		
		/*
			This  query  will receive a reference to an std::ostream object and a bool and return 
			a reference to the std::ostream object. The bool argument will specify whether or not the
			records should be listed on a single line or on separate lines. 
			Implementations of this function will insert the iGood record for the current object into 
			the std::ostreamobject.
		*/
		virtual std::ostream& write(std::ostream& os, bool linear) const = 0;

		/*
			This modifier will receive a reference to an std::istream object   and   returns   a   
			reference   to   the std::istreamobject. Implementations of this function will extract the 
			iGood record for the current object from the std::istreamobject.
		*/
		virtual std::istream& read(std::istream& is) = 0;

		/*
			This  query  will  receive  the  address  of  an unmodifiable C-style null-terminated string and 
			return true if the string is identical to the stock keeping unit of an iGoodrecord; false otherwise.
		*/
		virtual bool operator==(const char* sku) const = 0;

		/*
			This query will return the cost of a single unit of an iGoodwith taxes included.	
		*/
		virtual double total_cost() const = 0;

		/*
			This query returns the address of the string storing the name of the product.
		*/
		virtual const char* name() const = 0;

		/*
			This query will return the number of units of an iGoodthat are needed.
		*/
		virtual int qtyNeeded() const = 0;

		/*
			This query will return the number of units of an iGood that are currently available.
		*/
		virtual int quantity() const = 0;

		/*
			This modifier will receive an integer holding the number of units of  an iGoodthat  are  currently  available.  
			This  function  will  set  the  number  of  units available.
		*/
		virtual void quantity(int) = 0;

		/*
			This  modifier  will  receive  an  integer  identifying the  number  of units  to  be  
			added  to  the iGood and  return  the  updated  number  of  units  currently available. 
		*/
		virtual int operator+=(int qty) = 0;

		/*
			This query returns true if the name of the current products is greater than the name
			of the iProduct received as parameter (according to how the string comparison functions
			define ‘greater than’); false otherwise
		*/
		virtual bool operator>(const iGood& other) const = 0;

	};
}
#endif