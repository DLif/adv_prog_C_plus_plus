#include "binIO_t.h"

// simply call base empty constructor
binIO_t::binIO_t()
{}

// default implementation suffices, simply calls base class destructor that does all the work
binIO_t::~binIO_t()
{}


// construct a binary stream with given path and accessMode
binIO_t::binIO_t(const string& path, const virtIO_t::access_mode& accessMode) : virtIO_t(path, accessMode)
{} 

