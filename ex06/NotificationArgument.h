#ifndef __NOTIF_ARG_H
#define __NOTIF_ARG_H

#include <string>

// class that is passed as an argument to the observer update method

class NotificationArgument
{

public:
	
	NotificationArgument(const std::string& type, const std::string& message);
	
	// get type of notification:
	//    service price update - "price"
	//    may upgrade to new phone - "upgrade"
	std::string getNotificationType() const;


	// get notificaition message
	// e.g. "new service price is: 100 shekels"
	std::string getMessage()          const;

protected:
	std::string type;
	std::string message;
};

#endif