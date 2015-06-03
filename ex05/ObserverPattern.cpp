#include "ObserverPattern.h"
#include <algorithm>

// common subject logic implemntation

Subject::~Subject() {};

void Subject::attach(Observer* observer)
{
	if (std::find(observers.begin(), observers.end(), observer) == observers.end())
	{
		// does not contain observer, add to vector
		observers.push_back(observer);
		observer->addSubject(this);
	}
}

void Subject::detach(Observer* observer)
{
	std::vector<Observer*>::iterator loc; 
	if ((loc = std::find(observers.begin(), observers.end(), observer)) != observers.end())
	{
		// contains observer, remove
		observers.erase(loc);
		observer->addSubject(NULL);
	}
}


void Subject::notify()
{
	std::vector<Observer*>::iterator iter = observers.begin();
	while (iter != observers.end())
	{
		// notify observer
		(*iter)->update(this);
		iter += 1;
	}
}

Observer* Subject::getTestSubject(){
	if (observers.size() <= 0){
		return NULL;
	}
	return *(observers.begin());
}

void Subject::free_observers_connection(){
	for (Observer* observer : observers){
		//observer->remove_subject_from_list();
	}
}

void Observer::addSubject(Subject* attachedTo){
	subjects.push_back(attachedTo);
}