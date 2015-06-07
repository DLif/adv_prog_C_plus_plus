#ifndef __TC__
#define __TC__

#include "Subject.h"
#include <string>

// represents a telephone company
// a phone company is a singleton

class TC : public Subject
{
public:

	virtual void notifyPriceChange(double newPrice);
	virtual void notifyUpgradeMobile(const std::string& newModel);

	// -- Singleton implementation ---
	static TC& getTelephoneCompany()
	{
		static TC company;
		return company;
	}


protected:
	// protected to allow inheritance
	TC();
	virtual ~TC(); 


private:

	// company non-copyable
	TC(const TC& other);
	TC& operator=(const TC&);


};



#endif