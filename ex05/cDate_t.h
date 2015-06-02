#ifndef __CDATE_T
#define __CDATE_T

#include "ObserverPattern.h"
#include "cTime_t.h"
#include "absDateImp.h"
#include <iostream>
#include <string>

class cDate_t : public Observer
{
public:

	//
	// haven't figured out what he means exactly in the printing format yet
	//
	enum PrintFormat { a, b, c };

	cDate_t();                                          // object will hold current date
	cDate_t(const cDate_t& other);                      // copy date representation
														// subjects are not copied
	cDate_t(size_t day, size_t month, size_t year);   
	virtual ~cDate_t();

	// copy date representation, subjects are not copied
	cDate_t& operator=(const cDate_t& other);           
	
	virtual void setDate(size_t day, size_t month, size_t year);
	virtual std::ostream& print(std::ostream& os, const PrintFormat& format) const;

	// getters
	size_t currentDay() const;
	size_t currentMonth() const;
	size_t currentYear() const;
	size_t dayOfYear() const;          // returns values in 1-365
	size_t dayOfMonth() const;         // returns values in 1-31 (28, 29 need to be taken into account)
	bool isLeapYear() const;
	std::string nameOfDay() const;
	std::string nameOfMonth() const;



	// observer pattern update method implementation
	// cTime_t objects will call this method when addition was performed and a day needs to be increased
	// if given changedSubject is not observed, nothing will be changed
	virtual void update(Subject* changedSubject);

	// add current cTime_t subject object
	// thus, if the given time object's day will increase by one
	// our date object should be notified via update()
	void addTimeSubject(cTime_t* timeObj);

protected:

	// bridge design pattern
	// inner implementation
	// 
	absDateImpl* date;


};



inline void cDate_t::setDate(size_t day, size_t month, size_t year)
{
	date->setDate(day, month, year);
}

inline void cDate_t::update(Subject* changedSubject)
{
	if (std::find(subjects.begin(), subjects.end(), changedSubject) != subjects.end())
	{
		
		// some cTime_t object we're indeed observing.
		// advance day by one
		//
		date->advanceDay();
	}
}

inline void cDate_t::addTimeSubject(cTime_t* timeObj)
{
	subjects.push_back(timeObj);
	timeObj->attach(this);
}
inline size_t cDate_t::currentDay() const
{
	return date->currentDay();
}
inline size_t cDate_t::currentMonth() const
{
	return date->currentMonth();
}
inline size_t cDate_t::currentYear() const
{
	return date->currentYear();
}
inline size_t cDate_t::dayOfYear() const
{
	return date->dayOfYear();
}
inline size_t cDate_t::dayOfMonth() const
{
	return date->dayOfMonth();
}
inline bool cDate_t::isLeapYear() const
{
	return currentYear() % 4 == 0 && currentYear() % 400 == 0;
}
inline std::string cDate_t::nameOfDay() const
{
	return date->nameOfDay();
}
inline std::string cDate_t::nameOfMonth() const
{
	return date->nameOfMonth();
}

#endif