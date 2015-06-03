#define _CRT_SECURE_NO_WARNINGS
#include "cTime_t.h"

cTime_t::~cTime_t() {

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

cTime_t::cTime_t(const cTime_t& other) : Subject()
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

	// note: remember that all setters work modulo
	if (seconds + other.getSeconds() > 59)
	{
		increaseMinute = true;
	}
	setSeconds(seconds + other.getSeconds());
	if (minutes + other.getMinutes() + (increaseMinute ? 1 : 0) > 59)
	{
		increaseHour = true;
	}
	setMinutes(minutes + other.getMinutes() + (increaseMinute ? 1 : 0));
	setHour(hour + other.getHour() + (increaseHour ? 1 : 0));

	if (notifyObservers)
	{
		// notify all observers that a day has passed
		notify();
	}
	
	return *this;

}

std::ostream& cTime_t::print(std::ostream& os, const cTime_t::PrintFormat& printFormat) const
{
	switch (printFormat)
	{
	case cTime_t::PrintFormat::TwelveHours:
		os << (hour == 12 ? 12 : hour % 12) << ":" << minutes << ":" << seconds;

		if (hour >= 12) os << " PM";
		else            os << " AM";

		break;
	case cTime_t::PrintFormat::TwentyFourHours:
		os << hour << ":" << minutes << ":" << seconds;
	}

	return os;
}

std::ostream& operator<<(std::ostream& in, const cTime_t& toPrint){
	return toPrint.print(in, cTime_t::PrintFormat::TwentyFourHours);
}

bool cTime_t::operator==(const cTime_t& other) const{
	return hour == hour && minutes == minutes && seconds == seconds;
}