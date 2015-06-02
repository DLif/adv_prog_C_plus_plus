#include "cDateBasicImpl.h"

absDateImpl* cDateBasicImpl::clone() const
{
	return new cDateBasicImpl(*this);
}