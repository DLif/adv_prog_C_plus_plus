#ifndef __CTIME_H_
#define __CTIME_H_

#include <iostream>
#include <time.h>
#include "ObserverPattern.h"

class cTime_t : public Subject
{
public:

	enum PrintFormat { TwentyFourHours = 1, TwelveHours};

	cTime_t();                                // construct with current time

	cTime_t(const cTime_t& other);            // copies the time representation
											  // observers are not copied
	cTime_t& operator=(const cTime_t& other); // copies the time representation
	                                          // observers are not copied


	cTime_t(size_t hour, size_t minutes, size_t seconds); // construct cTime_t object with given hour:minutes:seconds time
														  // note: 
	                                                      // hour is mod 24
														  // minutes is mod 60
														  // seconds is mod 60

	virtual ~cTime_t();
	
	// set time, all the setters are modulo
	void setTime(size_t hour, size_t minutes, size_t seconds);
	void setHour(size_t hour);        // modulu 24
	void setMinutes(size_t minutes);  // modulu 60
	void setSeconds(size_t seconds);  // modulu 60

	// get time
	size_t getHour() const;
	size_t getMinutes() const;
	size_t getSeconds() const;

	// output time representation to given output-stream
	virtual std::ostream& print(std::ostream& os, const PrintFormat& printFormat) const;

	// perform addition
	// if time changes to the next day, notify observing cDate_t object (if any exist)
	cTime_t& operator+=(const cTime_t& other);

	// perform addition
	// if time changes to the next day, notify observing cDate_t object (if any exist)
	// note that the new cTime_t object does not inherit current observers
	cTime_t operator+(const cTime_t& other) const;

protected:

	// methods checks whether addition with other cTime_t object
	// will advance the day by one, returns true if so, otherwise returns false
	bool cTime_t::willAdditionAdvanceDay(const cTime_t& other) const;


private:

	// inner time representation
	size_t hour;
	size_t minutes;
	size_t seconds;

};



inline void cTime_t::setTime(size_t hour, size_t minutes, size_t seconds)
{
	setHour(hour);
	setMinutes(minutes);
	setSeconds(seconds);
}

inline void cTime_t::setHour(size_t hour)
{
	this->hour = hour % 24;
}

inline void cTime_t::setMinutes(size_t minutes)
{
	this->minutes = minutes % 60;
}

inline void cTime_t::setSeconds(size_t seconds)
{
	this->seconds = seconds % 60;
}

inline size_t cTime_t::getHour() const
{
	return hour;
}

inline size_t cTime_t::getMinutes() const
{
	return minutes;
}

inline size_t cTime_t::getSeconds() const
{
	return seconds;
}


inline cTime_t cTime_t::operator+(const cTime_t& other) const
{
	return cTime_t(*this) += other;
}

#endif