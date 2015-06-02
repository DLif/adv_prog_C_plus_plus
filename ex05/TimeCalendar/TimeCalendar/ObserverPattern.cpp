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
	}
}

void Subject::detach(Observer* observer)
{
	std::vector<Observer*>::iterator loc; 
	if ((loc = std::find(observers.begin(), observers.end(), observer)) != observers.end())
	{
		// contains observer, remove
		observers.erase(loc);
	}
}


void Subject::notify()
{
	std::vector<Observer*>::iterator iter = observers.begin();
	while (iter != observers.end())
	{
		// notify observer
		(*iter)->update(this);
	}
}