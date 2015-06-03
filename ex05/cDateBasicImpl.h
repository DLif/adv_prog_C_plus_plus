#ifndef __ABS_DATE_IMP_
#define __ABS_DATE_IMP_

#include "absDateImp.h"
#include <time.h>
#include <iostream>

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
	//~cDateBasicImpl();									   default enough  

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
	virtual void setDate(size_t day = 0, size_t month = 0, size_t year = 0);
	virtual void advanceDay();

	// prototype design pattern
	virtual absDateImpl* clone() const;

	virtual std::ostream& print(std::ostream& os) const;

	virtual bool operator==(const cDateBasicImpl& other) const;

private:
	size_t day;
	size_t month;
	size_t year;
	size_t dayOfMonth_var;
	size_t dayOfYear_var;
};

inline size_t cDateBasicImpl::currentDay() const
{
	return day;
}
inline size_t cDateBasicImpl::currentMonth() const
{
	return month;
}
inline size_t cDateBasicImpl::currentYear() const
{
	return year;
}
inline size_t cDateBasicImpl::dayOfMonth() const
{
	return dayOfMonth_var;
}
inline size_t cDateBasicImpl::dayOfYear() const
{
	return dayOfYear_var;
}


#endif