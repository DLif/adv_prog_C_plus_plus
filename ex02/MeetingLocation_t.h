#ifndef MEETING_LOCATION_H
#define MEETING_LOCATION_H


#include "Meeting_t.h"

template <class T> class MeetingLocation_t : public Meeting_t<T>
{


public:
	virtual ~MeetingLocation_t<T>();                            // empty destructor will suffice, destorys all data members
	//MeetingLocation_t<T>(const MeetingLocation_t<T>& other);  // default CCTOR will suffice, copies all data members
	//MeetingLocation_t<T>();                                   // default CTOR will suffice, calls empty constructor of all data members
	//MeetingLocation_t<T>& operator=(const MeetingLocation_t<T>& other) ;  // default assignment operator will suffice
																			// copies all data members


	//	This methods initializes the object's fields with giving parameteres
	//	This method MUST be called after the constructor and before using the object
	//	An initialization method enables us to throw exceptions (since we do not want to throw exceptions from the constructor)
	//	
	//	NOTES:
	//		1. if startingTime >= finishTime then invalid_argument exception will be thrown 
	//      2. if startingTime or finishTime are out of valid bounds (0-24) invalid_argument exception will be thrown
	inline void init(const string& meetingTopic, const T& startingTime, const T& finishTime, const string& location);

	
	// get the meeting location
	inline string getMeetingLocation() const;

	

protected:

	// input/ouput methods. override definitions from base class

	// read into the meeting from given stream
	virtual istream& readFrom(istream& is);

	// output textual representation to the stream
	virtual ostream& outputTo(ostream& os) const;

private:

	// meeting location
	string location;

};

//
// member functions' implementations 
//

template <class T>
inline string MeetingLocation_t<T>::getMeetingLocation() const
{
	return location;
}


template <class T> MeetingLocation_t<T>::~MeetingLocation_t() {

	// empty destructor suffices, simply destorys all data members (including base class)
}



template <class T>
inline void MeetingLocation_t<T>::init(const string& meetingTopic, const T& startingTime, const T& finishTime, const string& location){

	// init the base object
	Meeting_t<T>::init(meetingTopic, startingTime, finishTime);

	// all we have to do now is set the location
	this->location = location;

}


template <class T>
inline ostream& MeetingLocation_t<T>::outputTo(ostream& os) const
{
	Meeting_t<T>::outputTo(os);
	os << ", at " << this->location;
	return os;
}


template <class T>
istream& MeetingLocation_t<T>::readFrom(istream& is)
{
	// fill base class
	Meeting_t<T>::readFrom(is);

	// fill location
	if (!(is >> this->location))
	{
		throw invalid_argument("Invalid meeting location");
	}

	return is;
}





#endif