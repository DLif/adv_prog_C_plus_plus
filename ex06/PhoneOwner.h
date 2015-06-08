#ifndef __PHONE_OWNER
#define __PHONE_OWNER

#include "PhoneClient.h"
#include "Observer.h"
#include <string>
#include "NotificationArgument.h"
#include "TC.h"

class PhoneOwner : public Observer
{

public:

	PhoneOwner(TC* telephoneCompany, PhoneClient* impl, const std::string& name);
	virtual ~PhoneOwner();


	std::string getName() const;
	size_t getId() const;
	std::string getNumber() const;
	PhoneClient::PhoneClientType getClientType() const;

	// observer pattern update method
	void update(Subject* subject, NotificationArgument& notificationArgument);

	//print object to stdout
	void printOwner();

protected:

	// bridge (holds specific phone type implementation, e.g. mobile phone or stationary phone specific aspects)
	PhoneClient* impl;
	
private:

	// Phone owner name and id
	// client type independant and belongs to the abstraction itself
	std::string name;
	size_t id;

	// disallow "copying" owners
	PhoneOwner(const PhoneOwner& other);
	PhoneOwner& operator=(const PhoneOwner&);

	static size_t globID;

};

inline std::string PhoneOwner::getName() const
{
	return name;
}

inline size_t PhoneOwner::getId() const
{
	return id;
}

inline std::string PhoneOwner::getNumber() const
{
	// phone type specific
	return impl->getNumber();
}

inline PhoneClient::PhoneClientType PhoneOwner::getClientType() const
{
	// phone type specific
	return impl->getClientType();
}


#endif