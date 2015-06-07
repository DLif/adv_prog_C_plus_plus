#ifndef __MOBILE_
#define __MOBILE_

#include "PhoneClient.h"

class MobilePhoneClient : public PhoneClient
{
	friend PhoneClient;

public:

	virtual PhoneClient::PhoneClientType getClientType() const
	{
		return PhoneClient::PhoneClientType::Mobile;
	}

protected:

	explicit MobilePhoneClient(const std::string& number) : PhoneClient(number){}

private:
	MobilePhoneClient(const MobilePhoneClient& other);
	MobilePhoneClient& operator=(const MobilePhoneClient&);


};


#endif