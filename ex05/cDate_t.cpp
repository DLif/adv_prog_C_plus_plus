#define _CRT_SECURE_NO_WARNINGS
#include "cDate_t.h"
#include <time.h>
#include <stdexcept>

using namespace std;

cDate_t::~cDate_t() {
	// default implementation suffices
	// base destructor will detach from subject
}

cDate_t::cDate_t()
{
	// get current date
	time_t 	time_date = time(0);
	struct tm* curr_date = localtime(&time_date);

	// set date
	setDate(curr_date->tm_mday, curr_date->tm_mon + 1, curr_date->tm_year + 1900);
}

cDate_t::cDate_t(const cDate_t& other)
{
	setDate(other.day, other.month, other.year);
}

cDate_t& cDate_t::operator=(const cDate_t& other)
{
	if (this != &other)
	{
		setDate(other.day, other.month, other.year);
	}
	return *this;
}

cDate_t::cDate_t(size_t day, size_t month, size_t year)
{
	setDate(day, month, year);
}


void cDate_t::setDate(size_t day, size_t month, size_t year)
{
	// check that given date is valid
	validateDate(day, month, year);

	// finally, set date
	this->day = day;
	this->month = month;
	this->year = year;
}



struct tm* cDate_t::createDateRepresentation(size_t day, size_t month, size_t year)
{
	time_t rawtime;
	// get current time into rawtime
	time(&rawtime);
	// get struct tm from rawtime (should not make one on our own)
	struct tm* cur_date = localtime(&rawtime);
	// fill current date
	cur_date->tm_year = year - 1900;
	cur_date->tm_mon = month - 1;
	cur_date->tm_mday = day;
	// fill rest of the fields
	mktime(cur_date);

	return cur_date;
}


std::string cDate_t::nameOfDay() const
{
	switch (currentDay()){
	case 1:return "Sunday";
	case 2:return "Monday";
	case 3:return "Tuesday";
	case 4:return "Wednesday";
	case 5:return "Thursday";
	case 6:return "Friday";
	case 7:return "Saturday";
	default: return "ERROR nameOfDay";
	}
}

std::string cDate_t::nameOfMonth() const
{
	switch (month){
	case 1:return "January";
	case 2:return "February";
	case 3:return "March";
	case 4:return "April";
	case 5:return "May";
	case 6:return "June";
	case 7:return "July";
	case 8:return "August";
	case 9:return "September";
	case 10:return "October";
	case 11:return "November";
	case 12:return "December";
	default: return "ERROR nameOfMonth";
	}
}


std::ostream& cDate_t::print(std::ostream& os, const std::string& format) const
{
	if (format == "EU-TEXT")
	{
		os << day << "/" << nameOfMonth().substr(0, 3).c_str() << "/" << year;
	}
	else if (format == "EU")
	{
		os << day << "/" << (month < 10 ? "0" : "") << month << "/" << year;
	}
	else if (format == "US")
	{
		os << (month < 10 ? "0" : "") << month << "/" << day << "/" << year;
	}
	return os;
}


void cDate_t::validateDate(size_t day, size_t month, size_t year)
{
	if (day < 1 || day > 31)
		throw std::invalid_argument("Error: invalid day, day should be in range 1-31");
	if (month < 1 || month > 12)
		throw std::invalid_argument("Error: invalid month, month should be in range 1-12");
	if (year < 1900)
		throw std::invalid_argument("Error: invalid year, year should be >= 1900");

	const size_t daysPerMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	if (month != 2)
	{
		// not feb
		if (day > daysPerMonth[month-1])
		{
			throw std::invalid_argument("Error: given month does not have so many days");
		}
	}
	else
	{
		// feb
		if (year % 4 == 0 && year % 400 == 0)
		{
			// leap year, 29 days in feb
			if (day > 29)
			{
				throw std::invalid_argument("Error: february does not contain so many days");
			}

		}
		else
		{
			// not a leap year
			if (day == 29)
			{
				throw std::invalid_argument("Error: february contains 28 days only on a non leap year");
			}
			else if (day > 28)
			{
				throw std::invalid_argument("Error: february does not contain so many days");
			}
		}
	}
}


