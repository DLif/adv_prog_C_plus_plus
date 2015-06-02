#ifndef __ABS_DATE_IMP_
#define __ABS_DATE_IMP_

#include "absDateImp.h"


//
// Basic date implementation
// NOTE: find a better name for class

class cDateBasicImpl : public absDateImpl
{

public:

	cDateBasicImpl();                                          // initialize as current date
	cDateBasicImpl(size_t day, size_t month, size_t year);     // initalize from given date
	// cDateBasicImpl(const cDateBasicImpl& other);            simply copy object
	// cDateBasicImpl& operator=(const cDateBasicImpl& other)  simply copy object
	// ~cDateBasicImpl();                                      default suffices

	// pure virtual method implementations
	// basic getters
	virtual size_t currentDay() const;
	virtual size_t currentMonth() const;
	virtual size_t currentYear() const;
	virtual size_t dayOfYear() const;
	virtual size_t dayOfMonth() const;

	virtual std::string nameOfDay() const;
	virtual std::string nameOfMonth() const;

	// manipulators
	virtual void setDate(size_t day, size_t month, size_t year);
	virtual void advanceDay();

	// prototype design pattern
	virtual absDateImpl* clone() const;

private:
	size_t day;
	size_t month;
	size_t year;
};

#endif