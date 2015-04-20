#ifndef MEETING_H
	#define MEETING_H
	#include "Meeting_t.h"
#endif
#include <vector>

template <class T> class DayCalendar_t{

	//friend ostream& operator<<(ostream& os, const DayCalendar_t<T>& dayCalendar); //exceptoin-throwing "invalid input"
public:

	virtual ~DayCalendar_t();
	// DayCalendar_t();                           /* default constructor will suffice      */
	// DayCalendar_t(const DayCalendar_t<T>& other)  /* default copy constructor will suffice */
	DayCalendar_t<T>& operator=(const DayCalendar_t<T>& other);
	
	void addMeeting(const Meeting_t<T>* meeting); //exceptoin-throwing "invalid timing"
	bool removeMeeting(const T& startingTime);
	Meeting_t<T>* findMeeting(const T& startingTime) const;
	bool is_empty() const;
	void destroy_all();
	// == default
	// destroy all

protected:
	bool check_new_day_validity(const Meeting_t<T>* meeting) const;
	int find_insert_location(const Meeting_t<T>* meeting) const;
	vector<Meeting_t<T>*> meetings;     /* dynamic array of meetings */

};

//Destructor.this function clear the object allocated area and the vector
//It does not destroy the meetings themselfs.
template <class T> DayCalendar_t<T>::~DayCalendar_t() {
	delete (&meetings);
} 

template <class T>
DayCalendar_t<T>& DayCalendar_t<T>::operator=(const DayCalendar_t<T>& other) {
	if (&this != &other){
		this->meetings = other.meetings;
	}
	return *this;
}

template <class T>
void DayCalendar_t<T>::addMeeting(const Meeting_t<T>* meeting) {
	if (check_new_day_validity()) {
		throw exception("invalid timing");
	}
	else {
		std::vector<Meeting_t<T>*>::iterator it_on_insert_loc = meetings.begin()+find_insert_location(meeting); //calculate the insertion location and move the vector iterator to the wanted index.
		meetings.insert(it_on_insert_loc,meeting); //insert at index "insert_location(meeting)"
	}
}

/*
	Find the index where we can insert the new elemnt and keep all the list sorted by starting time of the meetings
*/
template <class T>
int DayCalendar_t<T>::find_insert_location(const Meeting_t<T>* meeting) const{
	int insertion_index = 0;

	for (insertion_index = 0 ; insertion_index < meetings.size() ; insertion_index++) {
		if (insertion_index->startingTime < meetings[insertion_index]->startingTime){
			break; //found where we can put the new meetig and still keep them sorted
		}
	}

	return insertion_index;
}

/*
	This function check if there is a meeting which intersects with the time of *meeting;
	If there is return true, else false.
*/
template <class T>
bool DayCalendar_t<T>::check_new_day_validity(const Meeting_t<T>* meeting) const{
	bool is_intersecting = false;

	for (int i=0; i<meetings.size();i++){
		if( (*meetings[i]) == (*meeting)) {
			is_intersecting = true;
			break;
		}
		else if (meetings[i]->finishTime < meeting->startingTime){
			break;//this means that there won't be any more intersection. we can leave the loop
		}
	}

	return is_intersecting;
}

/*
	iterate over all elemnts, and return pointer to the one with the same startingTime. 
	If there is no such elemnt, return NULL.
*/
template <class T>
Meeting_t<T>* DayCalendar_t<T>::findMeeting(const T& startingTime) const {
	for (int i=0; i<meetings.size();i++){ 
		if(meetings[i]->startingTime == startingTime) {
			return meetings[i];
		}
	}
	return NULL;
}

/*
	This function finds the first meeting with the given startingTime and erase it. 
	If there is such one, return true. Else return false.
	In order to remove in only one loop, we won't use find
*/
template <class T>
bool DayCalendar_t<T>::removeMeeting(const T& startingTime) {
	std::vector<Meeting_t<T>*>::iterator it_index_to_remove = meetings.begin();
	for (int i=0; i<meetings.size();i++){ 
		if(meetings[i]->startingTime == startingTime) {
			meetings.erase(it_index_to_remove+i);
			return true;
		}
	}
	return false;
}

template <class T>
bool DayCalendar_t<T>::is_empty() const {
	return meetings.empty();
}

/*
	This function clears all the meetings from the calendar and call the destructor on them all.
*/
template <class T>
void DayCalendar_t<T>::destroy_all() {
	for (int i=0; i<meetings.size();i++){ 
		delete meetings[i];
	}
	meetings.clear();
}