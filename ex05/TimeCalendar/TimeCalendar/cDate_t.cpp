#include "cDate_t.h"
#include "cDateBasicImpl.h"

cDate_t::cDate_t()
{
	// hold current date
	date = new cDateBasicImpl;
}
cDate_t::cDate_t(const cDate_t& other)
{
	// clone implementation
	date = other.date->clone();
}
cDate_t::cDate_t(size_t day, size_t month, size_t year){
	date = new cDateBasicImpl(day, month, year);
}

cDate_t::~cDate_t()
{
	std::vector<Subject*>::iterator iter = subjects.begin();
	while (iter != subjects.end())
	{
		(*iter)->detach(this);
	}

	delete date;
}

// copy date representation (subjects are not copied)
cDate_t& cDate_t::operator=(const cDate_t& other)
{
	if (this != &other)
	{
		delete date;
		date = other.date->clone();
	}

	return *this;
	
}