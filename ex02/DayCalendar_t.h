#ifndef _DAY_CALENDAR_H
#define _DAY_CALENDAR_H

#include "Meeting_t.h"
#include <vector>

using namespace std;

// class template declaration
template <class T>
class DayCalendar_t;

// << operator method declaration
template <class T>
ostream& operator<< (ostream& os, const DayCalendar_t<T>& dayCalendar);


template <class T> class DayCalendar_t {

	// output a representation of the day calendar
	friend ostream& operator<< <T>(ostream& os, const DayCalendar_t& dayCalendar);
																 
public:

	virtual ~DayCalendar_t();										   // empty destructor will suffice
	// DayCalendar_t();												   // default constructor will suffice      
	// DayCalendar_t(const DayCalendar_t<T>& other)					   // default copy constructor will suffice
	// DayCalendar_t<T>& operator=(const DayCalendar_t<T>& other);      default assignment operator will suffice
	
	inline bool operator==(const DayCalendar_t<T>& other) const;        // returns true iff the other calendar contains
																		// exactly the same meetings

	virtual void addMeeting(const Meeting_t<T>* meeting);				// add a meeting to the calendar
																		// if the meeting's time overlaps(intersects) with an existing meeting
																		// then invalid_argument exception will be thrown
																	    // the meeting will be added in such a manner that the calendar will
																		// remain sorted by meetings' starting hour

	virtual Meeting_t<T>* removeMeeting(const T& startingTime);			// remove a meeting by its starting time
																		// returns the removed meeting if found
																		// otherwise, if no such meeting exists, returns NULL

	virtual Meeting_t<T>* findMeeting(const T& startingTime) const;    // find a meeting by its starting time
																	   // if no such meeting is found, returns NULL

	inline virtual bool isEmpty() const;                               // returns true iff day calendar has no meetings
	inline virtual size_t getMeetingsCount() const;					   // returns the number of meetings currently in day calendar

	virtual void deleteAll();										   // remove + delete all meetings in calendar

	inline virtual void removeAll();                                   // empty calendar, removing all meetings (without deleting)


protected:


	virtual ostream& outputTo(ostream& os) const;					   // a printing method
																	   // outputs a textual representation of the calendar
																	   // to the given output stream
																	   // it is called from the << friend operator
																	   // virtual in order to ensure polymorphic calls from <<
																	   // protected in order to enable deriving classes to call it

	vector<Meeting_t<T>*> meetings;									   // dynamic array/vector of meetings
																	   // in the base implementation, the vector is sorted according to the meetings' starting times
																	   // this data member is protected, since we cannot predit all possible deriving classes
																	   // for example, a RemoteDayCalendar that syncs the calendar with a cloud, will require access to the vector


private:

	// helper methods, to make the implementation of the base class functionalities more modular

	bool doesMeetingIntersect(const Meeting_t<T>* meeting) const;      // returns true iff given meeting's time duration intersects
																	   // some other meeting that is already in the calendar

	size_t findInsertionIndex(const Meeting_t<T>* meeting) const;	   // find the the index in the meetings vector where the meeting should be inserted
																	   // meetings vector is sorted, so the insertion index is the required index to 
																	   // insert given meeting, so that the vector will remain sorted (by meetings starting time)

	size_t findIndexOfMeeting(const T& startingTime, bool& found) const; // method performs a binary search on the sorted vector
																		 // in order to find a meeting with given startingTime
																		 // found will hold the result, true if such a meeting was found, false otherwise
};

// 
// member functions implementation
//

template <class T> DayCalendar_t<T>::~DayCalendar_t() {
	// empty destructor will suffice
	// simply destory all data members
}


/*
	This function adds a given meeting pointer into the calendar.
	The meeting pointer will be inserted to the vector according to its starting time - the pointers in the vector are sorted by their starting time.

	if given meeting's time intersects with an existing meeting, an invalid_argument exception will be thrown

*/
template <class T>
void DayCalendar_t<T>::addMeeting(const Meeting_t<T>* meeting) {

	if (doesMeetingIntersect(meeting)) {
		throw invalid_argument("Given meeting's time intersects with an existing meeting's time");
	}
	else {
		// find the insertion index of the meeting
		vector<Meeting_t<T>*>::iterator it_on_insert_loc = meetings.begin() + findInsertionIndex(meeting);
		// do the insertion
		meetings.insert(it_on_insert_loc, (Meeting_t<T>*)meeting);
	}

}

/*
	Find the index where we can insert the new meeting such that the vector will remain sorted by the starting time of the meetings
*/
template <class T>
size_t DayCalendar_t<T>::findInsertionIndex(const Meeting_t<T>* meeting) const{

	size_t insertion_index = 0;

	for (insertion_index = 0; insertion_index < meetings.size(); insertion_index++) {
		if (meeting->getStartingTime() < meetings[insertion_index]->getStartingTime()){
			//insertion_index is the index where we can put the new meetig and still keep them sorted
			break;
		}
	}

	return insertion_index;
}

/*
	This function checks if there is a meeting which intersects with the time of given meeting
	If there is return true, else false.
*/
template <class T>
bool DayCalendar_t<T>::doesMeetingIntersect(const Meeting_t<T>* meeting) const{

	for (size_t i = 0; i<meetings.size(); i++){
		if (*(meetings[i]) == *meeting) {
			// found intersection
			return true;
		}
	}

	return false;
}

/*
	iterate over meetings, and return a pointer to a meeting with given startingTime
	If there is no such meeting, return NULL.
*/
template <class T>
Meeting_t<T>* DayCalendar_t<T>::findMeeting(const T& startingTime) const {

	// locate the meeting in the vector (binary search)
	bool exists;
	size_t meetingIndex = findIndexOfMeeting(startingTime, exists);

	if (exists)
	{
		return meetings[meetingIndex];
	}

	return NULL;
}

/*
	This function finds the a meeting with the given startingTime, and if such found, removes it from the array
	if such a meeting was found, the method returns it, otherwise returns NULL
*/
template <class T>
Meeting_t<T>* DayCalendar_t<T>::removeMeeting(const T& startingTime) {

	
	// locate the meeting in the vector (binary search)
	bool exists; 
	size_t meetingIndex = findIndexOfMeeting(startingTime, exists);

	if (exists)
	{
		// if found, remove from array and return it
		Meeting_t<T>* meeting = meetings[meetingIndex];
		meetings.erase(meetings.begin() + meetingIndex);
		return meeting;
	}
	// not found
	return NULL;
}

/*	
	returns true iff the calendar is empty
*/
template <class T>
inline bool DayCalendar_t<T>::isEmpty() const {
	return meetings.empty();
}

/*
	This function removes all the meetings inside the calendar, without deleting them
*/

template <class T>
inline void DayCalendar_t<T>::removeAll()
{
	meetings.clear();
}

/*
	get the number of meetings currently in calendar
*/
template <class T>
inline size_t DayCalendar_t<T>::getMeetingsCount() const
{
	return meetings.size();
}


/*
	This function removes all the meetings from the calendar and also deletes them
*/
template <class T>
void DayCalendar_t<T>::deleteAll() {
	for (size_t i = 0; i< meetings.size(); i++){
		delete meetings[i];
	}
	removeAll();
}

/*
	output to ostream method
	each instantiated method is a friend of the correspoding DayCalendar_t class
*/

template <class T>
ostream& operator<<(ostream& os, const DayCalendar_t<T>& dayCalendar)
{
	// polymorphic call
	return dayCalendar.outputTo(os);
}



template <class T>
ostream& DayCalendar_t<T>::outputTo(ostream& os) const
{
	os << "Day Calendar\n\n Meetings:\n" << endl;
	for (size_t i = 0; i< meetings.size(); i++){
		os << *(meetings[i]) << endl;
	}

	if (meetings.size() == 0)
	{
		os << "No meetings in calendar\n" << endl;
	}

	return os;
}

/*
	simple binary search on the sorted vector to find the a meeting with given starting time
	
	if such a meeting exists, its index will be returned and found will be true
	otherwise, found will be false (ignore startingTime in this case)
	
*/

template <class T>
size_t DayCalendar_t<T>::findIndexOfMeeting(const T& startingTime, bool& found) const
{
	size_t mid;
	if (isEmpty()){
		found = false;
		return 0;
	}

	size_t max = meetings.size() - 1;
	size_t min = 0;

	while (max >= min){
		mid = (min + max) / 2;

		if ((meetings[mid])->getStartingTime() < startingTime)
			min = mid + 1;
		else if ((meetings[mid])->getStartingTime() > startingTime){
			
			if (mid == 0)
			{
				// we already know the meeting does not exist
				break;
			}
			max = mid - 1;
		}

		else
		{
			found = true;
			return mid;
		}

	}
	found = false;
	return 0;
}

// comparsion operators returns true iff the calendars contain exactly the same meetings
template <class T>
inline bool DayCalendar_t<T>::operator==(const DayCalendar_t<T>& other) const
{
	return this->meetings == other.meetings;
}

#endif