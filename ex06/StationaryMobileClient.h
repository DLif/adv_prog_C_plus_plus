#ifndef __STATIONARY_
#define __STATIONARY_

#include "PhoneClient.h"

class StationaryPhoneClient : public PhoneClient
{
	friend PhoneClient;

public:

	virtual PhoneClient::PhoneClientType getClientType() const
	{
		return PhoneClient::PhoneClientType::Stationary;
	}

protected:

	explicit StationaryPhoneClient(const std::string& number) : PhoneClient(number){}

private:
	StationaryPhoneClient(const StationaryPhoneClient& );
	StationaryPhoneClient& operator=(const StationaryPhoneClient&);


};


#endif