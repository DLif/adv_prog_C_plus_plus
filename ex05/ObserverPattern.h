#ifndef __OBSERVER_PATTERN__
#define __OBSERVER_PATTERN__
#include <vector>

/*
	observer pattern interfaces
*/

class Subject;

// observer abstract class
// holds multiple subject pointers at the same time

class Observer {

public:
	
	virtual ~Observer() {}
	virtual void update(Subject* changedSubject) = 0;

protected:
	// enable multiple subjects
	std::vector<Subject*> subjects;

};

// subject abstract class

class Subject {

public:
	virtual ~Subject() = 0;
	// attach a new observer
	// if observer already exists, nothing will be changed
	virtual void attach(Observer*);

	// detach an observer
	// if observer does not exist nothing will be changed
	virtual void detach(Observer*);

protected:
	// update() all observers
	virtual void notify();

private:
	std::vector<Observer*> observers;

};
#endif