#ifndef __PHONE_CLIENT_H
#define __PHONE_CLIENT_H

#include <string>

class PhoneClient
{

public:

	enum PhoneClientType { Mobile, Stationary };

	PhoneClient(const std::string& phoneNumber);
	virtual ~PhoneClient();

	virtual PhoneClientType getClientType() const = 0;

	// get phone number
	std::string getNumber() const;

	// factory method - create phone clients (Mobile, Stationary)
	static PhoneClient* createPhoneClient(const PhoneClientType& clientType, const std::string& phoneNumber);
	
protected:

	std::string phoneNumber; 

private:

	// clients are non copyable

	PhoneClient(const PhoneClient& other);
	PhoneClient& operator=(const PhoneClient&);


};

#endif