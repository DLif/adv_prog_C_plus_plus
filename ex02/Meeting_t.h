#include <string>
#include <iostream>
using namespace std;

//ostream& operator<<(ostream& os, const Meeting_t<T>& meeting); //check- why isn't it a part of the class.
//istream& operator>>(istream& is, Meeting_t<T>& meeting); //exceptoin-throwing "invalid input"

template <class T> class Meeting_t {

public:

	virtual ~Meeting_t<T>();
	Meeting_t<T>(const Meeting_t& other);
	Meeting_t<T>();

	void init(const string& meetingTopic, const T& startingTime, const T& finishTime);   //exceptoin-throwing "invalid input"

	Meeting_t<T>& operator=(const Meeting_t<T>& other) const;
	inline bool operator==(const Meeting_t& other) const;
	bool operator<(const Meeting_t& other) const;

	inline T getMeetingDuration() const;
	inline T getStartingTime() const;
	inline T getFinishTime() const;
	inline string getMeetingTopic() const;


private:
	bool check_args_valid_for_fields(const T& startingTime, const T& finishTime);
	T startingTime;
	T finishTime;
	string meetingTopic;

};

/*
	simple get functions for the fields
*/
template <class T>
inline T Meeting_t<T>::getMeetingDuration() const
{
	return finishTime - startingTime;
}

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

/*
	As instructed, the == operation check equeality by intersaction of the meetings occurence.
	if there is a time in which both of the meetings occur - they are equal.
*/
template <class T>
inline bool Meeting_t<T>::operator==(const Meeting_t<T>& other) const
{
	return (startingTime > other.startingTime && startingTime < other.finishTime)
		|| (other.startingTime > startingTime && other.startingTime < finishTime);
}

template <class T> Meeting_t<T>::Meeting_t() {}	//Default constructor. Empty implemenation (all we need is the object space initialization. we will fill the variables with the function init()).

//Copy constructor. Simply copy each of the fields from the given meeting_t object
template <class T> Meeting_t<T>::Meeting_t(const Meeting_t<T>& other) {
	startingTime = other.startingTime;
	finishTime = other.finishTime;
	meetingTopic = other.meetingTopic;
}

//Destructor. Simply call destructor on each of the objects
template <class T> Meeting_t<T>::~Meeting_t() {
	delete (&startingTime);
	delete (&finishTime);
	delete (&meetingTopic);
} 

/*
	Assigment operator.
	Because the == operator is overriden, we will check if the object is equal to the other (and then no assingment needed) by it's address
	Simply copy each of the fields from the given meeting_t object, if they are valid.
*/
template <class T> Meeting_t<T>& Meeting_t<T>::operator=(const Meeting_t<T>& other) const {
	if (&this != &other){
		this->startingTime= other.startingTime;
		this->finishTime= other.finishTime;
		this->meetingTopic= other.meetingTopic;
	}
	return *this;
}

/* 
	This functions act almost like constructor which initialize object fields from given parameters.
	Only here because the object is already allocated, throwing an exception won't give us "broken" object (like in a constructor). This allows us to check the arguments given to the object for validity.
*/
template <class T> 
void Meeting_t<T>::init(const string& meetingTopic, const T& startingTime, const T& finishTime){
	if (check_args_valid_for_fields(startingTime,finishTime) == true) {
		this-> startingTime = startingTime;
		this->finishTime = finishTime;
		this->meetingTopic = meetingTopic;
	}
	else {
		throw exception("invalid arguments");
	}
}

/*
	This function checks that the startingTime and finishTime "makes sense"- that the startingTime is earlier than the finishTime.
*/
template <class T>
bool Meeting_t<T>::check_args_valid_for_fields(const T& startingTime, const T& finishTime){
	if (startingTime >= finishTime){
		return false;
	}
	else {
		return true;
	}
}