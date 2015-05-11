#include "binIO_t.h"

// default implementation suffices, simply calls base class destructor that does all the work
binIO_t::~binIO_t()
{}

// initializes an empty binary stream without opening a file
binIO_t::binIO_t()
{
	// let the base class do all the work
}

// construct a binary stream and open the file with access mode
binIO_t::binIO_t(const string& path, const virtIO_t::access_mode& accessMode) : virtIO_t(path, accessMode)
{ } 

