#include "Meeting_t.h"

template <class T> class MeetingLocation_t : public Meeting_h<T>
{
public:
	virtual ~MeetingLocation();
	MeetingLocation(const MeetingLocation& other);
	MeetingLocation();

	//virtual init(const string& meetingTopic, const T& startingTime, const T& finishTime, const string& location);   //exceptoin-throwing "invalid input"

	virtual MeetingLocation_t& operator=(const MeetingLocation_t& other) const;

	inline string getMeetingLocation() const;

private:
	string location;

};


template <class T> 
inline string MeetingLocation_t<T>::getMeetingLocation() const
{
	return location;
}


