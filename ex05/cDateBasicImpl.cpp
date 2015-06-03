#define _CRT_SECURE_NO_WARNINGS
#include "cDateBasicImpl.h"



cDateBasicImpl::cDateBasicImpl(){
	cDateBasicImpl::setDate();
}


cDateBasicImpl::cDateBasicImpl(size_t day, size_t month, size_t year){
	
	cDateBasicImpl::setDate(day,month,year);
}

/*
	This function can take a lot of pain - it will normalize any date given by parameters, and fills the datamembers accordingly
	if called without parameters, wil set the current date
*/
void cDateBasicImpl::setDate(size_t day, size_t month, size_t year){
	struct tm* cur_date;

	if (day == 0 && month == 0 && year == 0){ // call witth no values - use current time
		time_t 	time_date = time(0);
		cur_date = localtime(&time_date); // copy the given struct to the one we allocated on the stack
	}
	else {
		time_t rawtime;

		time(&rawtime); // get current time into rawtime
		cur_date = localtime(&rawtime); // get struct tm from rawtime (should not make one on our own)
		cur_date->tm_year = year - 1900; // fill the wanted date parameters
		cur_date->tm_mon = month - 1;
		cur_date->tm_mday = day;
		mktime(cur_date); //normalize date by day,month,year
	}

	this->day = cur_date->tm_wday;
	this->month = cur_date->tm_mon + 1;
	this->year = cur_date->tm_year + 1900;
	this->dayOfMonth_var = cur_date->tm_mday;
	this->dayOfYear_var = cur_date->tm_yday;
}

void cDateBasicImpl::advanceDay(){
	setDate(dayOfMonth_var + 1, month, year);
}


absDateImpl* cDateBasicImpl::clone() const
{
	return new cDateBasicImpl(*this);
}

std::string cDateBasicImpl::nameOfDay() const{
	switch (day){
		case 0:return "Sunday" ;
		case 1:return "Monday";
		case 2:return "Tuesday";
		case 3:return "Wednesday";
		case 4:return "Thursday";
		case 5:return "Friday";
		case 6:return "Saturday";
		default: return "ERROR nameOfDay";
	}
}

std::string cDateBasicImpl::nameOfMonth() const{
	switch (month){
	case 1:return "January";
	case 2:return "Febuary";
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

std::ostream& cDateBasicImpl::print(std::ostream& in) const{
	in << "\n";
	in << day << "," << month << "," << year;
	in << "\ndayOfMonth: " << dayOfMonth_var << "\ndayOfYear: " << dayOfYear_var << "\n";
	return in;
}

bool cDateBasicImpl::operator==(const cDateBasicImpl& other) const{
	return day == other.day && month == other.month && year == other.year;
}