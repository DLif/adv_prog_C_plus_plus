#include "MeetingLocation_t.h"
#include <vector>

template <class T> DayCalendar_t{

	friend ostream& operator<<(ostream& os, const DayCalendar_t<T>& dayCalendar); //exceptoin-throwing "invalid input"
public:

	virtual ~DayCalendar_t();
	// DayCalendar_t();                           /* default constructor will suffice      */
	// DayCalendar_t(const DayCalendar_t<T>& other)  /* default copy constructor will suffice */
	virtual DayCalendar_t& operator=(const DayCalendar_t<T>& other);
	
	virtual void addMeeting(const Meeting_t<T>* meeting); //exceptoin-throwing "invalid timing"
	virtual bool removeMeeting(const T& startingTime);
	virtual Meeting_t<T>* findMeeting(const T& startingTime) const;

	// == default
	// destroy all
	// empty

protected:
	vector<Meeting_t<T>*> meetings;     /* dynamic array of meetings */

};

