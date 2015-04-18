#include "MeetingLocation_t.h"
#include <vector>

template <class T> DayCalendar_t{

	friend ostream& operator<<(ostream& os, const DayCalendar_t<T>& dayCalendar);
public:

	virtual ~DayCalendar_t();
	// DayCalendar_t();                           /* default constructor will suffice      */
	// DayCalendar_t(const DayCalendar_t<T>& other)  /* default copy constructor will suffice */
	virtual DayCalendar_t& operator=(const DayCalendar_t<T>& other);
	
	virtual void addMeeting(Meeting_t<T>* meeting);
	virtual bool removeMeeting(T startingTime);
	virtual Meeting_t<T>* findMeeting(T startingTime);



protected:
	vector<Meeting_t<T>*> meetings;     /* dynamic array of meetings */

};

