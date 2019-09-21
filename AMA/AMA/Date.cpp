/*
*	Final Project Milestone 1 - Date Module
*	Date.cpp
*	Date 2019-07-01
*	Auther B. Alfanous
*/

/*
		To start this project, clone/download milestone 1 from the course repository and code the missing 
	parts of the Date class. 
		The Date class encapsulates a date that is readable by an std::istream object and printable by 
	an std::ostream object using the following format: YYYY/MM/DD, where YYYY refers to a four-digit 
	value for the year, MM refers to a two-digit value for the month and DD refers to a two-digit 
	value for the day in the month.
*/

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <iomanip>
#include <string>
#include "Date.h"

using namespace std;
namespace ama {

	Date::Date() {
		m_year = 0;
		m_month = 0;
		m_day_of_the_month = 0;
		m_comparator = 0;
		m_errorCode = NO_ERROR;
	}

	Date::Date(int _year, int _month, int _day) {
		*this = Date();

		if ((_year >= min_year) && (_year <= max_year) &&
			(_month >= 1) && (_month <= 12) &&
			(_day <= mdays(_year, _month)) && (_day > 0)) {
			m_comparator = _year * 372 + _month * 31 + _day;
			if (m_comparator >= min_date) {
				m_year = _year;
				m_month = _month;
				m_day_of_the_month = _day;
			}
			else
				m_comparator = 0;
		}
		else if ((_year < min_year) || (_year > max_year))
			errCode(YEAR_ERROR);
		else if ((_month < 1) || (_month > 12))
			errCode(MON_ERROR);
		else if ((_day > mdays(_year, _month)) || (_day <= 0))
			errCode(DAY_ERROR);
	}

	//This function sets the error state variable
	void Date::errCode(int errorCode) {
		m_errorCode = errorCode;
	}

	//This query returns the error state as an error code value.
	int Date::errCode() const{
		return m_errorCode;
	}

	//This query returns true if the error state is not NO_ERROR.
	bool Date::bad() const {
		if (errCode() != NO_ERROR)
			return true;
		return false;
	}

	/*This function returns the number of days in a given month for a given year.*/
	int Date::mdays(int year, int mon) const {
		int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
		int month = mon >= 1 && mon <= 12 ? mon : 13;
		month--;
		return days[month] + int((month == 1)*((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
	}

	/*
	A query that returns true if two date objects store the same date
	(does not check error code of either object). */
	bool Date::operator==(const Date& rhs) const {
		if (m_comparator == rhs.m_comparator)
			return true;
		return false;
	}

	/*A query that returns true if two date objects store different dates
	(does not check error code of either object).*/
	bool Date::operator!=(const Date& rhs) const{
		if (m_comparator != rhs.m_comparator)
			return true;
		return false;
	}

	/*A query that returns true if the current object stores a date that
	is before the date stored in rhs (does not check error code of either object).*/
	bool Date::operator<(const Date& rhs) const {
		if (m_comparator < rhs.m_comparator)
			return true;
		return false;
	}

	/*A query that returns true if the current object stores a date that is after
	the date stored in rhs (does not check error code of either object).*/
	bool Date::operator>(const Date& rhs) const {
		if (m_comparator > rhs.m_comparator)
			return true;
		return false;
	}

	/*A query that returns true if the current object stores a date
	that is before or equal to the date stored in rhs
	(does not check error code of either object).*/
	bool Date::operator<=(const Date& rhs) const {
		if (m_comparator <= rhs.m_comparator)
			return true;
		return false;
	}

	/*
	A query that returns true if the current object stores a date that
	is after or equal to the date stored in rhs (does not check error code of either object).
	*/
	bool Date::operator>=(const Date& rhs) const {
		if (m_comparator >= rhs.m_comparator)
			return true;
		return false;
	}


	std::istream& Date::read(istream& is) {
		char delimiter;
		int year, month, day, comparator;

		//*this = Date();

		is >> year >> delimiter >> month >> delimiter >> day;
		comparator = year * 372 + month * 31 + day;
		if (is.fail()) {
			errCode(CIN_FAILED);
			//is.clear();
			//string trash;
			//is >> trash;
		}
		else {
			if ((year > max_year) || (year < min_year))
				errCode(YEAR_ERROR);
			else if ((month > 12) || (month < 1))
				errCode(MON_ERROR);
			else if (day > mdays(year, month) || day <= 0)
				errCode(DAY_ERROR);
			else if(comparator < min_date)
				errCode(PAST_ERROR);
			else if ((errCode() == NO_ERROR) && (comparator >= min_date)) {
				m_year = year;
				m_month = month;
				m_day_of_the_month = day;
				m_comparator = year * 372 + month * 31 + day;
			}
		}
		return is;
	}


	/*A query that writes the date to an std::ostream object in the following format:
	YYYY/MM/DD, and then returns a reference to the std::ostream object.*/
	std::ostream& Date::write(ostream& os) const {
		os << setfill('0') << setw(4) << m_year << "/";

		if (m_month < 10 && m_month != 0)
			os << "0" << m_month << "/";
		else if (m_month == 0)
			os << "00" << "/";
		else
			os << m_month << "/";

		if (m_day_of_the_month < 10 && m_day_of_the_month != 0)
			os << "0" << m_day_of_the_month << setfill(' ');
		else if (m_day_of_the_month == 0)
			os << "00" << setfill(' ');
		else
			os << m_day_of_the_month << setfill(' ');

		return os;
	}

	/*Reads the date from the first parameter (use Date::read(…)).*/
	std::istream& operator>>(std::istream& is, Date& date) {
		date.read(is);
		return is;
	}

	/*Prints the date to the first parameter (use Date::write(…)).*/
	std::ostream& operator<<(std::ostream& os, const Date& date) {
		date.write(os);
		return os;
	}

}
