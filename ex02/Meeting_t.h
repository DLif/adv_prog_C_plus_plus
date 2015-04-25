#ifndef MEETING_H
#define MEETING_H

#include <string>
#include <iostream>
#include <stdexcept>

using namespace std;

// declare class template
// (to make friend methods declarations possible)

template <class T>
class Meeting_t;

// friend methods declarations
template <class T>
ostream& operator<<(ostream&, const Meeting_t<T>&);

template <class T>
istream& operator>>(istream&, Meeting_t<T>& );


template <class T> class Meeting_t {

	friend ostream& operator<< <T> (ostream& os, const Meeting_t& meeting);
	friend istream& operator>> <T> (istream& is, Meeting_t& meeting); 

public:

	virtual ~Meeting_t<T>();                  // trivial (empty) implementation will suffice
	//Meeting_t<T>(const Meeting_t& other);   CCTOR default implementation will suffice
	//Meeting_t<T>();                         Default CTOR, default implementation will suffice



	//	This methods initializes the object's fields with giving parameteres
	//	This method MUST be called after the constructor and before using the object
	//	An initialization method enables us to throw exceptions (since we do not want to throw exceptions from the constructor)
	//	
	//	NOTES:
	//		1. if startingTime >= finishTime then invalid_argument exception will be thrown 
	//      2. if startingTime or finishTime are out of valid bounds (0-24) invalid_argument exception will be thrown
	
	 void init(const string& meetingTopic, const T& startingTime, const T& finishTime);

	// the assignment operator is virtual, in case deriving classes will want to handle such an assignment
	// in a different way, for example setting extra fields to a some value
	// virtual Meeting_t<T>& operator=(const Meeting_t<T>& other) const; 



	//	GENERAL NOTE: all logic regarding meeting time managment and meeting topic
	//	is encapsulated in the base class, therefore the operators ==, <
	//	and the getter methods are not virtual, since the desired functionallity is already provided
	//	in the base class and is expected to remain the same in all Meeting_t objects



	//	returns true iff two meetings occur in time ranges that overlap (intersect)		
	//
	//	NOTE: this functionality is expected from all Meeting_t objects and is encapsulated entirely in the base class 
	//	thus this method must not be virtual
	inline bool operator==(const Meeting_t& other) const;


	//	returns true iff this meeting occurs BEFORE other given meeting
	//	We say that meeting A is < than B if they have:
	//		1) Do not intersect in time ranges (!(A==B)) 
	//		2) A's starting time is smaller than B's starting time 
	//		(These two together also imply that A's finish time is smaller than B's finish time)
	// 
	//	NOTE: this functionality is expected from all Meeting_t objects and is encapsulated entirely in the base class 
	//	thus this method must not be virtual
	inline bool operator <(const Meeting_t& other) const;


	//	get meeting starting time 
	inline T getStartingTime() const;

	// get meeting finish time
	inline T getFinishTime() const;

	//	get meeting topic (title)
	inline string getMeetingTopic() const;

	// change the meeting's topic
	// virtual because basic implementation may not suffice (for example if meeting is syncronized with the cloud)
	inline virtual void changeMeetingTopic(const string& topic);



protected:

	// input/ouput methods. The reason they are protected is to enable friend
	// <<, >> overloads to call them (polymorphically, note the virtual) without exposing these methods as public

	// read into the meeting from given stream
	virtual istream& readFrom(istream& is);

	// output textual representation to the stream
	virtual ostream& outputTo(ostream& os) const;


private:

	// method checks if given arguments represent a valid time range
	// 1. startingTime < finishTime
	// 2. startingTime and finishTime are both in valid range 0-24
	// if any error found, invalid_argument exception is thrown
	void validateInitArguments(const T& startingTime, const T& finishTime);

	// meeting starting time
	T startingTime;

	// meeting finish time
	T finishTime;

	// the topic of the meeting
	string meetingTopic;


	

};

//
//	memeber function implementations
//

template <class T>
Meeting_t<T>::~Meeting_t() {
	// empty  destructor will suffice
	// destorys all data members
};


template <class T>
inline T Meeting_t<T>::getStartingTime() const
{
	return startingTime;
}

template <class T>
inline T Meeting_t<T>::getFinishTime() const
{
	return finishTime;
}

template <class T>
inline string Meeting_t<T>::getMeetingTopic() const
{
	return meetingTopic;
}

template <class T>
inline void changeMeetingTopic(const string& topic)
{
	this->meetingTopic = topic;
}


template <class T>
inline bool Meeting_t<T>::operator==(const Meeting_t<T>& other) const
{
	return (startingTime > other.startingTime && startingTime < other.finishTime)  // current meeting starts after given meeting
		|| (other.startingTime > startingTime && other.startingTime < finishTime)  // current meeting starts before given meeting
		|| (startingTime == other.startingTime);                                   // start at the same time
}



template <class T>
void Meeting_t<T>::init(const string& meetingTopic, const T& startingTime, const T& finishTime){

	// ensure arguments correctness
	validateInitArguments(startingTime, finishTime);
	// if arguments are correct, initialize the meeting object
	this->startingTime = startingTime;
	this->finishTime = finishTime;
	this->meetingTopic = meetingTopic;
	
}


template <class T>
void Meeting_t<T>::validateInitArguments(const T& startingTime, const T& finishTime)
{
	if (startingTime >= finishTime)
	{
		throw invalid_argument("Meeting starting time cannot be equal or later than the finishing time");
	}
	if (startingTime < 0 || startingTime > 24)
	{
		throw invalid_argument("Meeting starting time, is out of valid time bounds: 0-24");
	}
	if (finishTime < 0 || finishTime > 24)
	{
		throw invalid_argument("Meeting finish time, is out of valid time bounds: 0-24");
	}
}

template <class T>
bool Meeting_t<T>::operator < (const Meeting_t& other) const {
	if (!(*this == other) && this->startingTime < other->startingTime) {
		return true;
	}
	else {
		return false;
	}
}

template <class T>
ostream& Meeting_t<T>::outputTo(ostream& os) const
{
	os << startingTime << " - " << finishTime << ": " << meetingTopic;
	return os;
}



template <class T>
istream& Meeting_t<T>::readFrom(istream& is)
{
	T startingTime, finishTime;
	string meetingTopic;
	if (!(is >> startingTime))
	{
		throw invalid_argument("Invalid meeting starting time");
	}

	if (!(is >> finishTime))
	{
		throw invalid_argument("Invalid meeting finish time");
	}

	if (!(is >> meetingTopic))
	{
		throw invalid_argument("Invalid meeting Topic");
	}

	// initialize the object with given arguments, may throw an invalid_argument exception
	init(meetingTopic, startingTime, finishTime);
	return is;
}


// read into a meeting object, uses the polymorphic method to read into the object
// may throw an invalid argument exception
template <class T>
istream& operator>>(istream& is, Meeting_t<T>& meeting)
{
	// polymorphic call
	return meeting.readFrom(is);
}



// output a representation of the meeting
template <class T>
ostream& operator<<(ostream& os, const Meeting_t<T>& meeting){

	// note that this is a polymorphic call
	return meeting.outputTo(os);
}


// update the meeting topic
template <class T>
inline void Meeting_t<T>::changeMeetingTopic(const string& topic){
	this->meetingTopic = topic;
}

#endif