#ifndef __ABSDATEIMP__
#define __ABSDATEIMP__
#include <string>


// abstract date implementation class
// lists the basic, common, requirements of a date implementation
// could be: Hebrew date, Islamic date, Chinese date and so on..

class absDateImpl
{
public:

	// basic getters
	virtual size_t currentDay() const = 0;
	virtual size_t currentMonth() const = 0;
	virtual size_t currentYear() const = 0;
	virtual size_t dayOfYear() const = 0;
	virtual size_t dayOfMonth() const = 0;
	
	virtual std::string nameOfDay() const = 0;
	virtual std::string nameOfMonth() const = 0;
	
	// manipulators
	virtual void setDate(size_t day, size_t month, size_t year) = 0;
	virtual void advanceDay() = 0;

	// prototype design pattern
	virtual absDateImpl* clone() const = 0;

};

#endif