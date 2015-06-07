#define _CRT_SECURE_NO_WARNINGS
#include "cTime_t.h"
#include <time.h>
#include <stdexcept>


cTime_t::~cTime_t(){
	// default implementation suffices
}

cTime_t::cTime_t()
{
	// get current time
	time_t now = time(0);
	struct tm* current_time = localtime(&now);
	// set time
	setTime(current_time->tm_hour, current_time->tm_min, current_time->tm_sec);
}

cTime_t::cTime_t(size_t hour, size_t minutes, size_t seconds)
{
	setTime(hour, minutes, seconds);
}

cTime_t::cTime_t(const cTime_t& other)
{
	// note that the observers are not copied! Only time representation is copied
	setTime(other.hour, other.minutes, other.seconds);
}

cTime_t& cTime_t::operator=(const cTime_t& other)
{
	if (this != &other){
		// note that the observers are not copied! Only time representation is copied
		setTime(other.hour, other.minutes, other.seconds);
	}
	return *this;
}

bool cTime_t::willAdditionAdvanceDay(const cTime_t& other) const
{
	if (hour + other.getHour() > 23)
		return true;
	else if (hour + other.getHour() == 23)
	{
		size_t total_minutes = minutes + other.getMinutes();
		if (seconds + other.getSeconds() > 59)
		{
			total_minutes++;
		}
		if (total_minutes > 59)
		{
			return true;
		}
	}
	return false;
}

cTime_t& cTime_t::operator+=(const cTime_t& other)
{
	bool notifyObservers = willAdditionAdvanceDay(other);
	// carry flags
	bool increaseMinute = false;
	bool increaseHour = false;

	if (seconds + other.getSeconds() > 59)
	{
		increaseMinute = true;
	}
	setSeconds((seconds + other.getSeconds()) % 60);
	if (minutes + other.getMinutes() + (increaseMinute ? 1 : 0) > 59)
	{
		increaseHour = true;
	}
	setMinutes((minutes + other.getMinutes() + (increaseMinute ? 1 : 0)) % 60);
	setHour((hour + other.getHour() + (increaseHour ? 1 : 0)) % 24);

	if (notifyObservers)
	{
		// notify all observers that a day has passed
		notify();
	}

	return *this;

}


cTime_t cTime_t::operator+(const cTime_t& other)
{
	bool notifyObservers = willAdditionAdvanceDay(other);
	cTime_t result = (cTime_t)(*this) += other;
	if (notifyObservers)
	{
		// notify all observers that a day has passed
		notify();
	}

	return result;

}

std::ostream& cTime_t::print(std::ostream& os, const std::string& printFormat) const
{

	if (printFormat == "TwelveHours")
	{
		os << (hour == 12 ? 12 : hour % 12) << ":" << minutes << ":" << seconds;

		if (hour >= 12) os << " PM";
		else            os << " AM";

	}
	else if (printFormat == "TwentyFourHours"){
		os << hour << ":" << minutes << ":" << seconds;

	}
	else
	{
		throw std::invalid_argument("Error: invalid print format");
	}

	return os;
}

