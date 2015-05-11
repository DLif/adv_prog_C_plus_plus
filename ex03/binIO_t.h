#ifndef _BINIO_H
#define _BINIO_H

#include "virtIO_t.h"

class binIO_t : public virtIO_t{

public:

	// constructs an empty stream
	// empty implmentation will suffice, simply calls the base empty constructor
	binIO_t();     

	// constructs stream + opens the file
	// same logic as base class (accessMode will be expanded to binary equivelant mode)
	binIO_t(const string& path, const virtIO_t::access_mode& accessMode);
	
	// if the file is currently open, closes it (implemented in base constructor)
	virtual ~binIO_t(); 

	// implementation for the various operators
	virtual binIO_t& operator>>(char c);
	virtual binIO_t& operator<<(char c);
	virtual binIO_t& operator>>(unsigned char c);
	virtual binIO_t& operator<<(unsigned char c);
	virtual binIO_t& operator>>(short s);
	virtual binIO_t& operator<<(short s);
	virtual binIO_t& operator>>(unsigned short s);
	virtual binIO_t& operator<<(unsigned short s);
	virtual binIO_t& operator>>(int i);
	virtual binIO_t& operator<<(int i);
	virtual binIO_t& operator>>(unsigned int i);
	virtual binIO_t& operator<<(unsigned int i);
	virtual binIO_t& operator>>(long i);
	virtual binIO_t& operator<<(long i);
	virtual binIO_t& operator>>(unsigned long i);
	virtual binIO_t& operator<<(unsigned long i);
	virtual binIO_t& operator>>(float f);
	virtual binIO_t& operator<<(float f);
	virtual binIO_t& operator>>(double d);
	virtual binIO_t& operator<<(double d);

protected: 

	// this method translates our access mode to a corresponding string representation
	// valid for usage with fopen C method
	// this derives the base class implementation to add binary flag to each mode
	virtual string translateAccessMode() const;

};





// extend the translation method to fit our needs
// this will cause the files to be opened as binary files
// by adding the binary flag "b" before each possible access mode
inline string binIO_t::translateAccessMode() const
{
	// force the binary flag, causing the file to be opened in binary mode
	return "b" + virtIO_t::translateAccessMode();
}



// general notes: all these methods use read,write already implemented in the base class
// these methods already take of exceptions throwing and error flag handling

inline binIO_t& binIO_t::operator>>(char c){

	// read one char, the read method already takes care of errors and flags
	read(&c, sizeof(char), 1);
	return *this;

}
inline binIO_t& binIO_t::operator<<(char c){

	// same binary representation as unsigned char
	return (*this) << (unsigned char)c;

}
inline binIO_t& binIO_t::operator >>(unsigned char c)
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
inline binIO_t& binIO_t::operator >> (short s)
{
	read(&s, sizeof(short), 1);
	return *this;
}
inline binIO_t& binIO_t::operator << (short s)
{
	write(&s, sizeof(short), 1);
	return *this;
}
inline binIO_t& binIO_t::operator >> (unsigned short s){
	return (*this) >> (short)s;
}
inline binIO_t& binIO_t::operator << (unsigned short s){
	return (*this) << (short)s;
}
inline binIO_t& binIO_t::operator >> (int i){

	read(&i, sizeof(int), 1);
	return *this;
}
inline binIO_t& binIO_t::operator << (int i){
	write(&i, sizeof(int), 1);
	return *this;
}
inline binIO_t& binIO_t::operator >> (unsigned int i){
	return (*this) >> (int)i;
}

inline binIO_t& binIO_t::operator << (unsigned int i){
	return (*this) << (int)i;

}
inline binIO_t& binIO_t::operator >> (long l){
	read(&l, sizeof(long), 1);
	return *this;

}
inline binIO_t& binIO_t::operator << (long l){
	write(&l, sizeof(long), 1);
	return *this;
}
inline binIO_t& binIO_t::operator >> (unsigned long l){
	return (*this) >> (long)l;

}
inline binIO_t& binIO_t::operator << (unsigned long l){
	return (*this) << (long)l;
}
inline binIO_t& binIO_t::operator >> (float f){
	read(&f, sizeof(float), 1);
	return *this;
}
inline binIO_t& binIO_t::operator << (float f){
	write(&f, sizeof(float), 1);
	return *this;
}
inline binIO_t& binIO_t::operator >> (double d){
	read(&d, sizeof(double), 1);
	return *this;
}
inline binIO_t& binIO_t::operator << (double d){
	write(&d, sizeof(double), 1);
	return *this;
}

#endif