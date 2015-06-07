#include "TC.h"
#include "PhoneOwner.h"
#include <iostream>

int main()
{

	TC& company = TC::getTelephoneCompany();

	PhoneOwner a(&company,
		PhoneClient::createPhoneClient(PhoneClient::PhoneClientType::Mobile, "050-588-3335"),
		"yosi");

	PhoneOwner b(&company,
		PhoneClient::createPhoneClient(PhoneClient::PhoneClientType::Stationary, "03-1234567"),
		"Zero cool"
		);
	
	company.notifyPriceChange(150.44);
	company.notifyUpgradeMobile("Nokia lumia 950");

	while (1){}

	return 0;
}