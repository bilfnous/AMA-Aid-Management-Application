/*
*	Final Project Milestone 1 - Date Module
*	Date.h
*	Date 2019-07-01
*	Auther B. Alfanous
*/

#include <iostream>

#ifndef AMA_DATE_H
#define AMA_DATE_H

#define NO_ERROR 0		//No error - the date is valid
#define CIN_FAILED 1	//istream failed on information entry
#define DAY_ERROR 2		//Day value is invalid
#define MON_ERROR 3		//Month value is invalid
#define YEAR_ERROR 4	//Year value is invalid
#define PAST_ERROR 5	//Date value is invalid

namespace ama {
	const int min_year = 2018;	 //This represents the minimum year acceptable for a valid date.
	const int max_year = 2038;	 //This represents the maximum year for a valid date.
	const int min_date = 751098; //This represents the date 2018/12/30; m_comparator = year * 372 + month * 31 + day;

	class Date {
		int m_year, m_month, m_day_of_the_month;
		int m_comparator, m_errorCode;

		void errCode(int errorCode);
		int mdays(int year, int month) const;

	public:
		Date();
		Date(int, int, int);
		int errCode() const;
		bool bad() const;

		bool operator==(const Date& rhs) const;
		bool operator!=(const Date& rhs) const;
		bool operator<(const Date& rhs) const;
		bool operator>(const Date& rhs) const;
		bool operator<=(const Date& rhs) const;
		bool operator>=(const Date& rhs) const;

		std::istream& read(std::istream& is);
		std::ostream& write(std::ostream& os) const;
	};
	std::istream& operator>>(std::istream&, Date&);
	std::ostream& operator<<(std::ostream&, const Date&);
}

#endif
