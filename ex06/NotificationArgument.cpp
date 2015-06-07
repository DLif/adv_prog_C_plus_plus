#include "NotificationArgument.h"

std::string NotificationArgument::getMessage() const
{
	return message;
}

std::string NotificationArgument::getNotificationType() const
{
	return type;
}

NotificationArgument::NotificationArgument(const std::string& type, const std::string& message)
	: type(type), message(message) {};

NotificationArgument::~NotificationArgument()
{};