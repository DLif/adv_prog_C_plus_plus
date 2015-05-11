#ifndef _ASCII_IO_H
#define _ASCII_IO_H

#include "virtIO_t.h"

class asciiIO_t : public virtIO_t {

public:

	// do not hide operators >> << for the void buffers
	using virtIO_t::operator<<;
	using virtIO_t::operator>>;

	// constructs an ascii file stream
	// same logic as base class 
	asciiIO_t(const string& path, const virtIO_t::access_mode& accessMode);

	// if the file is currently open, closes it (implemented in base constructor)
	virtual ~asciiIO_t();


	// implementation for the various operators
	// note that for ascii IO, all operators are implemented with readByParseString and writeByParseString
	// exceptions and flag handling is already provided by these methods (defined below)
	// also note that in case of an error, the stream will rewind its position to the position it were
	// before calling the operator [ same behaviour as in standard C++ IO ]

	virtual asciiIO_t& operator>>(char& c);
	virtual asciiIO_t& operator<<(char c);
	virtual asciiIO_t& operator>>(unsigned char& c);
	virtual asciiIO_t& operator<<(unsigned char c);
	virtual asciiIO_t& operator>>(short& s);
	virtual asciiIO_t& operator<<(short s);
	virtual asciiIO_t& operator>>(unsigned short& s);
	virtual asciiIO_t& operator<<(unsigned short s);
	virtual asciiIO_t& operator>>(int& i);
	virtual asciiIO_t& operator<<(int i);
	virtual asciiIO_t& operator>>(unsigned int& i);
	virtual asciiIO_t& operator<<(unsigned int i);
	virtual asciiIO_t& operator>>(long& i);
	virtual asciiIO_t& operator<<(long i);
	virtual asciiIO_t& operator>>(unsigned long& i);
	virtual asciiIO_t& operator<<(unsigned long i);
	virtual asciiIO_t& operator>>(float& f);
	virtual asciiIO_t& operator<<(float f);
	virtual asciiIO_t& operator>>(double& d);
	virtual asciiIO_t& operator<<(double d);


private:

	// a generic method to read into the given container, one element, according to the given parse string
	// this method already sets the io_status_flag to readErr_e in case of an error and throws exceptions
	// its also important to note that in case of a read error, the seek position will remain the same as before the read
	// templating is not needed here, because we pass the address of the container
	void readByParseString(void* container, const string& parse_string) ;


	// a generic method to write into the file from given container, one element, according to the given parse string
	// this method already sets the io_status_flag to writeErr_e in case of an error and throws exceptions
	// its also important to note that in case of a write error, the seek position will remain the same as before the write
	// templating is needed here, because we're passing the value itself and we need to declare its type (can't deref void pointer)
	template <typename T> void writeByParseString(const T& container, const string& parse_string) ;

};

template <typename T> void asciiIO_t::writeByParseString(const T& container, const string& parse_string) 
{

	this->checkWriteAccessiblity();

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
};



inline asciiIO_t& asciiIO_t::operator>>(char& c){

	readByParseString(&c, "%c");
	return *this;
}
inline asciiIO_t& asciiIO_t::operator<<(char c)
{
	writeByParseString(c, "%c");
	return *this;
}
inline asciiIO_t& asciiIO_t::operator>>(unsigned char& c)
{
	// same as signed, read a character
	readByParseString(&c, "%c");
	return *this;
}
inline asciiIO_t& asciiIO_t::operator<<(unsigned char c)
{
	// same as signed, write a character
	writeByParseString(c, "%c");
	return *this;

}
inline asciiIO_t& asciiIO_t::operator>>(short& s)
{
	readByParseString(&s, "%hd");
	return *this;
}
inline asciiIO_t& asciiIO_t::operator<<(short s)
{
	writeByParseString(s, "%hd");
	return *this;
}
inline asciiIO_t& asciiIO_t::operator>>(unsigned short& s)
{
	readByParseString(&s, "%hu");
	return *this;
}
inline asciiIO_t& asciiIO_t::operator<<(unsigned short s)
{
	writeByParseString(s, "%hu");
	return *this;
}
inline asciiIO_t& asciiIO_t::operator>>(int& i)
{
	readByParseString(&i, "%d");
	return *this;
}
inline asciiIO_t& asciiIO_t::operator<<(int i)
{
	writeByParseString(i, "%d");
	return *this;
}
inline asciiIO_t& asciiIO_t::operator>>(unsigned int& i)
{
	readByParseString(&i, "%u");
	return *this;
}
inline asciiIO_t& asciiIO_t::operator<<(unsigned int i)
{
	writeByParseString(i, "%u");
	return *this;
}
inline asciiIO_t& asciiIO_t::operator>>(long& i)
{
	readByParseString(&i, "%l");
	return *this;
}
inline asciiIO_t& asciiIO_t::operator<<(long i)
{
	writeByParseString(i, "%l");
	return *this;
}
inline asciiIO_t& asciiIO_t::operator>>(unsigned long& i)
{
	readByParseString(&i, "%lu");
	return *this;
}
inline asciiIO_t& asciiIO_t::operator<<(unsigned long i)
{
	writeByParseString(i, "%lu");
	return *this;
}
inline asciiIO_t& asciiIO_t::operator>>(float& f)
{
	readByParseString(&f, "%f");
	return *this;
}
inline asciiIO_t& asciiIO_t::operator<<(float f)
{
	writeByParseString(f, "%f");
	return *this;
}
inline asciiIO_t& asciiIO_t::operator>>(double& d)
{
	readByParseString(&d, "%lf");
	return *this;
}
inline asciiIO_t& asciiIO_t::operator<<(double d)
{
	writeByParseString(d, "%lf");
	return *this;
}

#endif