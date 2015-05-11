#ifndef _BINIO_H
#define _BINIO_H

#include "virtIO_t.h"

class binIO_t : public virtIO_t{

public:

	// do not hide operators >> << for the void buffers
	using virtIO_t::operator<<;
	using virtIO_t::operator>>;
	  
	// constructs a binary file stream with given file path and accessMode
	// simply calls the base constructor
	binIO_t(const string& path, const virtIO_t::access_mode& accessMode);
	
	// if the file is currently open, closes it (implemented in base constructor)
	virtual ~binIO_t(); 

	// implementation for the various operators
	// note that for binary IO, all operators are implemented with write/read methods
	// and thus exceptions and flag handling is already provided by the base class
	// also note that in case of an error, the stream will rewind its position to the position it were
	// before calling the operator [ same behaviour as in standard C++ IO ]

	virtual binIO_t& operator>>(char& c);
	virtual binIO_t& operator<<(char c);
	virtual binIO_t& operator>>(unsigned char& c);
	virtual binIO_t& operator<<(unsigned char c);
	virtual binIO_t& operator>>(short& s);
	virtual binIO_t& operator<<(short s);
	virtual binIO_t& operator>>(unsigned short& s);
	virtual binIO_t& operator<<(unsigned short s);
	virtual binIO_t& operator>>(int& i);
	virtual binIO_t& operator<<(int i);
	virtual binIO_t& operator>>(unsigned int& i);
	virtual binIO_t& operator<<(unsigned int i);
	virtual binIO_t& operator>>(long& i);
	virtual binIO_t& operator<<(long i);
	virtual binIO_t& operator>>(unsigned long& i);
	virtual binIO_t& operator<<(unsigned long i);
	virtual binIO_t& operator>>(float& f);
	virtual binIO_t& operator<<(float f);
	virtual binIO_t& operator>>(double& d);
	virtual binIO_t& operator<<(double d);

protected: 

	// this method translates our access mode to a corresponding string representation
	// valid for usage with fopen C method
	// this overrides the base class implementation to add binary flag to each mode
	virtual string translateAccessMode() const;

};



// extend the translation method to fit our needs
// this will cause the files to be opened as binary files
// by adding the binary flag "b" after each possible access mode
inline string binIO_t::translateAccessMode() const
{
	// force the binary flag, causing the file to be opened in binary mode
	return  virtIO_t::translateAccessMode() + "b";
}



inline binIO_t& binIO_t::operator>>(char& c){

	// read one char, the read method already takes care of errors and flags
	read(&c, sizeof(char), 1);
	return *this;

}
inline binIO_t& binIO_t::operator<<(char c){

	// same binary representation as unsigned char
	return (*this) << (unsigned char)c;

}
inline binIO_t& binIO_t::operator>>(unsigned char& c)
{
	// read one char, the read method already takes care of errors and flags
	read(&c, sizeof(char), 1);
	return *this;
}
inline binIO_t& binIO_t::operator<<(unsigned char c)
{
	write(&c, sizeof(char), 1);
	return *this;
}
inline binIO_t& binIO_t::operator >> (short& s)
{
	read(&s, sizeof(short), 1);
	return *this;
}
inline binIO_t& binIO_t::operator << (short s)
{
	write(&s, sizeof(short), 1);
	return *this;
}
inline binIO_t& binIO_t::operator >> (unsigned short& s){
	read(&s, sizeof(short), 1);
	return *this;
}
inline binIO_t& binIO_t::operator << (unsigned short s){
	write(&s, sizeof(short), 1);
	return *this;
}
inline binIO_t& binIO_t::operator >> (int& i){

	read(&i, sizeof(int), 1);
	return *this;
}
inline binIO_t& binIO_t::operator << (int i){
	write(&i, sizeof(int), 1);
	return *this;
}
inline binIO_t& binIO_t::operator >> (unsigned int& i){
	read(&i, sizeof(int), 1);
	return *this;
}

inline binIO_t& binIO_t::operator << (unsigned int i){
	write(&i, sizeof(int), 1);
	return *this;

}
inline binIO_t& binIO_t::operator >> (long& l){
	read(&l, sizeof(long), 1);
	return *this;

}
inline binIO_t& binIO_t::operator << (long l){
	write(&l, sizeof(long), 1);
	return *this;
}
inline binIO_t& binIO_t::operator >> (unsigned long& l){
	read(&l, sizeof(long), 1);
	return *this;

}
inline binIO_t& binIO_t::operator << (unsigned long l){
	write(&l, sizeof(long), 1);
	return *this;
}
inline binIO_t& binIO_t::operator >> (float& f){
	read(&f, sizeof(float), 1);
	return *this;
}
inline binIO_t& binIO_t::operator << (float f){
	write(&f, sizeof(float), 1);
	return *this;
}
inline binIO_t& binIO_t::operator >> (double& d){
	read(&d, sizeof(double), 1);
	return *this;
}
inline binIO_t& binIO_t::operator << (double d){
	write(&d, sizeof(double), 1);
	return *this;
}

#endif