#ifndef __OBSERVER_H
#define __OBSERVER_H
#include "NotificationArgument.h"

class Subject;

// observer abstract class
// observes at most a single subject at the same time

class Observer {

public:

	// default CTOR
	Observer();

	virtual ~Observer();

	// update also recieves update parameters (i.e. notification arguments)
	virtual void update(Subject* changedSubject, NotificationArgument& notificationArg) = 0;


protected:


	// Observed subject
	Subject* subject;

private:

	// prevent copying the subject through CCTOR or assignment
	// Observer must explicitliy attach to subject
	Observer(const Observer&);
	Observer& operator=(const Observer&);

};


#endif