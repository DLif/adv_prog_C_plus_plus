#include "Observer.h"
#include "Subject.h"

Observer::Observer() : subject(0) { }

Observer::~Observer()
{
	if (subject)
	{
		subject->detach(this);
		subject = 0;
	}
}


void Observer::setSubject(Subject* newSubject)
{
	if (subject)
	{
		// detach from previous
		subject->detach(this);
	}
	subject = newSubject;
	if (subject)
		subject->attach(this);

}
