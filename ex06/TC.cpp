#include "TC.h"
#include <sstream>
#include <string>
#include "PhoneOwner.h"

TC::TC()  {}
TC::~TC() {}

void TC::notifyPriceChange(double newPrice)
{
	// notify ALL clients about new price
	std::ostringstream strs;
	strs << newPrice;
	NotificationArgument arg("price", "new service price, " + strs.str() +" shekels");
	notify(arg);
}

void TC::notifyUpgradeMobile(const std::string& newModel)
{
	NotificationArgument arg("upgrade", "new model available, " + newModel);

	// notify only mobile phone carriers
	for (Observer* obs : observers)
	{
		PhoneOwner* client = static_cast<PhoneOwner*>(obs);
		if (client->getClientType() == PhoneClient::PhoneClientType::Mobile)
		{
			client->update(this, arg);
		}
	}
}