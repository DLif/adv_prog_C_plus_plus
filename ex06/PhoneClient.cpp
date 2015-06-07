#ifndef __PHONE_CLIENT
#define __PHONE_CLIENT
#include "PhoneClient.h"
#include "MobilePhoneClient.h"
#include "StationaryMobileClient.h"

PhoneClient::PhoneClient(const std::string& phoneNumber) : phoneNumber(phoneNumber) {}
PhoneClient::~PhoneClient() {}

std::string PhoneClient::getNumber() const
{
	return phoneNumber;
}

PhoneClient* PhoneClient::createPhoneClient(const PhoneClient::PhoneClientType& type, const std::string& phoneNumber)
{
	switch (type)
	{
	case PhoneClient::PhoneClientType::Mobile:
		return new MobilePhoneClient(phoneNumber);

	case PhoneClient::PhoneClientType::Stationary:
		return new StationaryPhoneClient(phoneNumber);

	}

	return 0;
}

#endif