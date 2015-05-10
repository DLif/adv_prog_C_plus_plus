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
	// closes the file if open
}

void asciiIO_t::readByParseString(void* container, const string& parse_string)
{
	// get current position
	long currentPos = this->findCurrentPosition();
	if (currentPos == -1L)
	{
		this->set_io_status(virtIO_t::readErr_e);
		throw runtime_error("Read error(seek)");
	}

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
	// get current position
	long currentPos = this->findCurrentPosition();
	if (currentPos == -1L)
	{
		this->set_io_status(virtIO_t::readErr_e);
		throw runtime_error("Write error(seek)");
	}

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
	// same as signed, read a character
	readByParseString(&c, "%c");
	return *this;
}
asciiIO_t& asciiIO_t::operator<<(unsigned char c)
{
	// same as signed, write a character
	writeByParseString(&c, "%c");
	return *this;

}
asciiIO_t& asciiIO_t::operator>>(short s)
{
	readByParseString(&s, "%hd");
	return *this;
}
asciiIO_t& asciiIO_t::operator<<(short s)
{
	writeByParseString(&s, "%hd");
	return *this;
}
asciiIO_t& asciiIO_t::operator>>(unsigned short s)
{
	readByParseString(&s, "%hu");
	return *this;
}
asciiIO_t& asciiIO_t::operator<<(unsigned short s)
{
	writeByParseString(&s, "%hu");
	return *this;
}
asciiIO_t& asciiIO_t::operator>>(int i)
{
	readByParseString(&i, "%d");
	return *this;
}
asciiIO_t& asciiIO_t::operator<<(int i)
{
	writeByParseString(&i, "%d");
	return *this;
}
asciiIO_t& asciiIO_t::operator>>(unsigned int i)
{
	readByParseString(&i, "%u");
	return *this;
}
asciiIO_t& asciiIO_t::operator<<(unsigned int i)
{
	writeByParseString(&i, "%u");
	return *this;
}
asciiIO_t& asciiIO_t::operator>>(long i)
{
	readByParseString(&i, "%l");
	return *this;
}
asciiIO_t& asciiIO_t::operator<<(long i)
{
	writeByParseString(&i, "%l");
	return *this;
}
asciiIO_t& asciiIO_t::operator>>(unsigned long i)
{
	readByParseString(&i, "%lu");
	return *this;
}
asciiIO_t& asciiIO_t::operator<<(unsigned long i)
{
	writeByParseString(&i, "%lu");
	return *this;
}
asciiIO_t& asciiIO_t::operator>>(float f)
{
	readByParseString(&f, "%f");
	return *this;
}
asciiIO_t& asciiIO_t::operator<<(float f)
{
	writeByParseString(&f, "%f");
	return *this;
}
asciiIO_t& asciiIO_t::operator>>(double d)
{
	readByParseString(&d, "%lf");
	return *this;
}
asciiIO_t& asciiIO_t::operator<<(double d)
{
	writeByParseString(&d, "%lf");
	return *this;
}