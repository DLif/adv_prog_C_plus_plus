#include "asciiIO_t.h"

// initializes an empty ascii stream without opening a file
asciiIO_t::asciiIO_t(){
	// let the base class do all the work
}

// intialize a stream and open a file in ascii (text) mode
// again, let the base class do all the work (base class opens the file in text mode by default)
asciiIO_t::asciiIO_t(const string& path, const virtIO_t::access_mode& accessMode) : virtIO_t(path, accessMode)
{}


asciiIO_t::~asciiIO_t(){
	// base implmentation suffices
}

void asciiIO_t::readByParseString(void* container, const string& parse_string)
{
	// get current position, true indicates this is a read
	// this may thrown an exception and set an error flag
	long currentPos = this->findCurrentPosition(true);

	// read one object from the file and store in the container
	if (fscanf(this->getFilePtr(), parse_string.c_str(), container) < 1)
	{
		// restore the position
		this->setFilePosition(currentPos);
		this->set_io_status(virtIO_t::readErr_e);

		throw runtime_error("Read error");
	}
}


void asciiIO_t::writeByParseString(void* container, const string& parse_string)
{
	// get current position, false indicates this is a write
	// this may thrown an exception and set an error flag
	long currentPos = this->findCurrentPosition(false);

	// write one object from from the container into the file
	if (fprintf(this->getFilePtr(), parse_string.c_str(), container) < 1)
	{
		// restore the position
		this->setFilePosition(currentPos);
		this->set_io_status(virtIO_t::writeErr_e);

		throw runtime_error("Write error");
	}
}


asciiIO_t& asciiIO_t::operator>>(char c){
	
	readByParseString(&c, "%c");
	return *this;
}
asciiIO_t& asciiIO_t::operator<<(char c)
{
	writeByParseString(&c, "%c");
	return *this;
}
asciiIO_t& asciiIO_t::operator>>(unsigned char c)
{
	readByParseString(&c, "%c");
	return *this;
}
asciiIO_t& asciiIO_t::operator<<(unsigned char c);
asciiIO_t& asciiIO_t::operator>>(short s);
asciiIO_t& asciiIO_t::operator<<(short s);
asciiIO_t& asciiIO_t::operator>>(unsigned short s);
asciiIO_t& asciiIO_t::operator<<(unsigned short s);
asciiIO_t& asciiIO_t::operator>>(int i);
asciiIO_t& asciiIO_t::operator<<(int i);
asciiIO_t& asciiIO_t::operator>>(unsigned int i);
asciiIO_t& asciiIO_t::operator<<(unsigned int i);
asciiIO_t& asciiIO_t::operator>>(long i);
asciiIO_t& asciiIO_t::operator<<(long i);
asciiIO_t& asciiIO_t::operator>>(unsigned long i);
asciiIO_t& asciiIO_t::operator<<(unsigned long i);
asciiIO_t& asciiIO_t::operator>>(float f);
asciiIO_t& asciiIO_t::operator<<(float f);
asciiIO_t& asciiIO_t::operator>>(double d);
asciiIO_t& asciiIO_t::operator<<(double d);