#ifndef __CTIME_H_
#define __CTIME_H_

#include <iostream>
#include <stdexcept>
#include "Subject.h"


class cTime_t : public Subject
{

public:

	cTime_t();                                // construct with current time

	cTime_t(const cTime_t& other);            // copies the time representation
											  // observers are NOT copied

	cTime_t& operator=(const cTime_t& other); // copies the time representation
											  // observers are NOT copied


	// construct cTime_t object from given time
	// note that if the input is not valid an exception will be thrown
	// input should hold:
	//		0 <= hour < 24
	//		0 <= minutes < 59
	//		0 <= seconds < 59
	cTime_t(size_t hour, size_t minutes, size_t seconds);


	virtual ~cTime_t();

	// set time, all the setters will throw an exception if input is invalid
	// input should hold:
	//		0 <= hour < 24
	//		0 <= minutes < 59
	//		0 <= seconds < 59
	void setTime(size_t hour, size_t minutes, size_t seconds);
	void setHour(size_t hour);
	void setMinutes(size_t minutes);
	void setSeconds(size_t seconds);

	// get time
	size_t getHour() const;
	size_t getMinutes() const;
	size_t getSeconds() const;

	// output time representation to given output-stream
	// print formats:
	//      TwentyFourHours - 24 hours format
	//      TwelveHours     - 12 hours format (with AM/PM)
	virtual std::ostream& print(std::ostream& os, const std::string& printFormat) const;

	// perform addition
	// if time changes to the next day, notify observing cDate_t object(s) (if any exist)
	cTime_t& operator+=(const cTime_t& other);

	// returns true iff represented time is the same
	bool operator==(const cTime_t& other) const;

protected:

	// method checks whether addition with other cTime_t object
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
	if (hour >= 24)
	{
		throw std::invalid_argument("Error: invalid hour value");
	}
	this->hour = hour;
}

inline void cTime_t::setMinutes(size_t minutes)
{
	if (minutes >= 60)
	{
		throw std::invalid_argument("Error: invalid minutes value");
	}
	this->minutes = minutes;
}

inline void cTime_t::setSeconds(size_t seconds)
{
	if (seconds >= 60)
	{
		throw std::invalid_argument("Error: invalid seconds value");
	}
	this->seconds = seconds;
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

inline bool cTime_t::operator==(const cTime_t& other) const{
	return hour == other.hour && minutes == other.minutes && seconds == other.seconds;
}



#endif