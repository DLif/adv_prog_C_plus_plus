#ifndef __OBSERVER_H
#define __OBSERVER_H

class Subject;

// observer abstract class
// observes at most a single subject at the same time

class Observer {

public:

	// default CTOR
	Observer();

	virtual ~Observer();
	virtual void update(Subject* changedSubject) = 0;

	// set current subject
	// method will first detach from previous subject (if existed)
	// and then attach to new one
	// to detach from existing subject, call method with 0
	virtual void setSubject(Subject* newSubject);

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