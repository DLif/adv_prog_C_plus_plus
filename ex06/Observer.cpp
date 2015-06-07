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

