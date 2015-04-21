#ifndef MEETING_H
	#define MEETING_H
	#include "Meeting_t.h"
#endif

template <class T> class MeetingLocation_t : public Meeting_t<T>
{
public:
	virtual ~MeetingLocation_t<T>();
	MeetingLocation_t<T>(const MeetingLocation_t<T>& other);
	MeetingLocation_t<T>();

	void init(const string& meetingTopic, const T& startingTime, const T& finishTime, const string& location);   //exceptoin-throwing "invalid input"

	MeetingLocation_t<T>& operator=(const MeetingLocation_t<T>& other) const;

	inline string getMeetingLocation() const;

private:
	string location;

};

/*
	A get function for the field
*/
template <class T> 
inline string MeetingLocation_t<T>::getMeetingLocation() const
{
	return location;
}

//not virtual so WTF now with operator==?

template <class T> MeetingLocation_t<T>::MeetingLocation_t() {}	//Default constructor. Empty implemenation (all we need is the object space initialization. we will fill the variables with the function init()).

//Copy constructor. Simply copy each of the fields from the given meeting_t object
template <class T> MeetingLocation_t<T>::MeetingLocation_t(const MeetingLocation_t<T>& other) 
	: Meeting_t(other) { //call to father copy constructor. this will handle the copying of the father fields

		this->location = other.location;
}

//Destructor. Simply call destructor on each of the objects
template <class T> MeetingLocation_t<T>::~MeetingLocation_t() {
	delete (&location);
	//auto call to father destructor
} 

/*
	Assigment operator.
	Because the == operator is overriden, we will check if the object is equal to the other (and then no assingment needed) by it's address
	Simply copy each of the fields from the given meeting_t object, if they are valid.
*/
template <class T> 
MeetingLocation_t<T>& MeetingLocation_t<T>::operator=(const MeetingLocation_t<T>& other) const {
	 father_obj = (*(&Meeting_t<T>)this); 
	 father_obj = (*(&Meeting_t<T>)other); //CHECK does it changes this object? - the idea is to use the father's operator= for the inherited fields
	 if(&this != &other){
		 this->location = other.location;
	 }
	 return *this;
}


/* 
	This functions act almost like constructor which initialize object fields from given parameters.
	Only here because the object is already allocated, throwing an exception won't give us "broken" object (like in a constructor). This allows us to check the arguments given to the object for validity.
*/
template <class T> 
void MeetingLocation_t<T>::init(const string& meetingTopic, const T& startingTime, const T& finishTime, const string& location){
	Meeting_t<T>::init(meetingTopic,startingTime,finishTime);
	this->location = location;  //if we reach till here no exception will be thrown and we need only init the location
}