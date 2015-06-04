#ifndef __CDATE_T
#define __CDATE_T

#include "Observer.h"
#include "cTime_t.h"

class cDate_t : public Observer
{

public:


	cDate_t();                                          // object will hold current date

	cDate_t(const cDate_t& other);                      // copy date representation
														// subject (if exists) is not copied

	// construct from given date
	// if date is invalid, an exception will be thrown
	// valid input:
	//		1 <= day <= 31
	//      1 <= month <= 12
	//      1900 <= year
	// plus, day must be a valid day in given month

	cDate_t(size_t day, size_t month, size_t year);     
	virtual ~cDate_t();

	// copy date representation. subject (if exists) is not copied
	cDate_t& operator=(const cDate_t& other);

	// returns true iff represented date is exactly the same
	bool operator==(const cDate_t& other) const;

	// set date according to given parameters
	// throws an exception if arguments represent an invalid date
	// valid input is as mentioned before
	virtual void setDate(size_t day, size_t month, size_t year);

	// outputs date representation into given os
	// format values:
	//		"EU-TEXT" - 22/Jan/2001
	//      "EU"      - 22/01/2001
	//      "US"      - 01/22/2001
	virtual std::ostream& print(std::ostream& os, const std::string& format) const;


	virtual size_t currentDay() const;         // returns current day of the week, values between 1-7
	virtual size_t currentMonth() const;       // returns current month,           values between 1-31
	virtual size_t currentYear() const;        // returns current year,            values 1900+

	virtual size_t dayOfYear() const;          // returns values in 1-365 (or 366 on leap years)
	virtual size_t dayOfMonth() const;         // returns values in 1-31

	virtual bool isLeapYear() const;
	virtual std::string nameOfDay() const;
	virtual std::string nameOfMonth() const;

	// increase day by one
	virtual void advanceDay();

	// observer pattern update method implementation
	// cTime_t objects will call this method when addition was performed and a day needs to be increased
	// if given changedSubject is not observed, nothing will be changed
	virtual void update(Subject* changedSubject);

	

protected:

	// valides given date
	// valid input:
	//		1 <= day <= 31
	//      1 <= month <= 12
	//      1900 <= year
	// plus, day must be a valid day in given month
	// if input is invalid, throwns an exception

	virtual void validateDate(size_t day, size_t month, size_t year);

	size_t day;      // holds values between 1-31
	size_t month;    // holds values between 1-12
	size_t year;     // holds years 1900+

private:
	// create a tm struct representing given date
	// note that the struct is statically allocated and should not be freed
	static struct tm* createDateRepresentation(size_t day, size_t month, size_t year);

	// create a tm struct representing current date
	// note that the struct is statically allocated and should not be freed
	struct tm* cDate_t::createCurrentDateRepresentation() const;

};




inline void cDate_t::update(Subject* changedSubject)
{
	if (subject == changedSubject){

		// some cTime_t object we're indeed observing.
		// advance day by one
		//
		advanceDay();
	}
}



inline bool cDate_t::isLeapYear() const
{
	// according to Yosi's definition
	return currentYear() % 4 == 0 && currentYear() % 400 == 0;
}

inline void cDate_t::advanceDay()
{
	// receive time struct for next day
	struct tm* timeStruct = createDateRepresentation(day + 1, month, year);
	// set time according to the struct
	setDate(timeStruct->tm_mday, timeStruct->tm_mon + 1, timeStruct->tm_year + 1900);
}

inline struct tm* cDate_t::createCurrentDateRepresentation() const
{
	return cDate_t::createDateRepresentation(day, month, year);
}

inline size_t cDate_t::currentDay() const
{
	return createCurrentDateRepresentation()->tm_wday + 1;
}

inline size_t cDate_t::currentMonth() const
{
	return month;
}

inline size_t cDate_t::currentYear() const
{
	return year;
}

inline size_t cDate_t::dayOfMonth() const
{
	return day;
}

inline size_t cDate_t::dayOfYear() const
{
	return createCurrentDateRepresentation()->tm_yday + 1;
}

inline bool cDate_t::operator==(const cDate_t& other) const{
	return day == other.day && month == other.month && year == other.year;
}




#endif