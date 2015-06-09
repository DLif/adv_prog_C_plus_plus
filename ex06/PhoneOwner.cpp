#include "PhoneOwner.h"
#include <iostream>

size_t PhoneOwner::globID = 0;

PhoneOwner::PhoneOwner(TC* company, PhoneClient* impl, const std::string& ownerName)
	: impl(impl), name(ownerName), id(globID++)
{
	subject = company;
	company->attach(this);
}

PhoneOwner::~PhoneOwner()
{
	delete impl;
	impl = 0;
}

void PhoneOwner::update(Subject* subject, NotificationArgument& notificationArgument)
{
	if (subject == this->subject)
	{


		printOwner();
		std::cout << "Received notification of type "
			<< notificationArgument.getNotificationType()
			<< "\nnotification content: "
			<< notificationArgument.getMessage()
			<< std::endl << std::endl;

	}
}

void PhoneOwner::printOwner() const{
	std::cout << (getClientType() == PhoneClient::PhoneClientType::Mobile ? "Mobile phone owner " : "Stationary phone owner ")
		<< getName()
		<< "\nwith phone number "
		<< getNumber()
		<< std::endl;
}