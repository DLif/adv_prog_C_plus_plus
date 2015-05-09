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


// extend the translation method to fit our needs
// this will cause the files to be opened as binary files
// by adding the binary flag "b" before each possible access mode
string binIO_t::translateAccessMode() const
{
	// force the binary flag, causing the file to be opened in binary mode
	return "b" + virtIO_t::translateAccessMode();
}



// general notes: all these methods use read,write already implemented in the base class
// these methods already take of exceptions throwing and error flag handling

binIO_t& binIO_t::operator>>(char c){

	// read one char, the read method already takes care of errors and flags
	read(&c, sizeof(char), 1);
	return *this;

}
binIO_t& binIO_t::operator<<(char c){

	// same binary representation as unsigned char
	return (*this) << (unsigned char)c;

}
binIO_t& binIO_t::operator >>(unsigned char c)
{
	// read one char, the read method already takes care of errors and flags
	read(&c, sizeof(char), 1);
	return *this;
}
binIO_t& binIO_t::operator<<(unsigned char c)
{
	write(&c, sizeof(char), 1);
	return *this;
}
binIO_t& binIO_t::operator >> (short s)
{
	read(&s, sizeof(short), 1);
	return *this;
}
binIO_t& binIO_t::operator << (short s)
{
	write(&s, sizeof(short), 1);
	return *this;
}
binIO_t& binIO_t::operator >> (unsigned short s){
	return (*this) >> (short)s;
}
binIO_t& binIO_t::operator << (unsigned short s){
	return (*this) << (short)s;
}
binIO_t& binIO_t::operator >> (int i){

	read(&i, sizeof(int), 1);
	return *this;
}
binIO_t& binIO_t::operator << (int i){
	write(&i, sizeof(int), 1);
	return *this;
}
binIO_t& binIO_t::operator >> (unsigned int i){
	return (*this) >> (int)i;
}

binIO_t& binIO_t::operator << (unsigned int i){
	return (*this) << (int)i;

}
binIO_t& binIO_t::operator >> (long l){
	read(&l, sizeof(long), 1);
	return *this;

}
binIO_t& binIO_t::operator << (long l){
	write(&l, sizeof(long), 1);
	return *this;
}
binIO_t& binIO_t::operator >> (unsigned long l){
	return (*this) >> (long)l;

}
binIO_t& binIO_t::operator << (unsigned long l){
	return (*this) << (long)l;
}
binIO_t& binIO_t::operator >> (float f){
	read(&f, sizeof(float), 1);
	return *this;
}
binIO_t& binIO_t::operator << (float f){
	write(&f, sizeof(float), 1);
	return *this;
}
binIO_t& binIO_t::operator >> (double d){
	read(&d, sizeof(double), 1);
	return *this;
}
binIO_t& binIO_t::operator << (double d){
	write(&d, sizeof(double), 1);
	return *this;
}