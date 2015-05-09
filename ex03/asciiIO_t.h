#include "virtIO_t.h"

class asciiIO_t {

public:

	
	asciiIO_t();

	// constructs stream + opens the file
	// same logic as base class (accessMode will be expanded to binary equivelant mode)
	asciiIO_t(const string& path, const virtIO_t::access_mode& accessMode);

	// if the file is currently open, closes it (implemented in base constructor)
	virtual ~asciiIO_t();

	virtual asciiIO_t& operator>>(char c);
	virtual asciiIO_t& operator<<(char c);
	virtual asciiIO_t& operator>>(unsigned char c);
	virtual asciiIO_t& operator<<(unsigned char c);
	virtual asciiIO_t& operator>>(short s);
	virtual asciiIO_t& operator<<(short s);
	virtual asciiIO_t& operator>>(unsigned short s);
	virtual asciiIO_t& operator<<(unsigned short s);
	virtual asciiIO_t& operator>>(int i);
	virtual asciiIO_t& operator<<(int i);
	virtual asciiIO_t& operator>>(unsigned int i);
	virtual asciiIO_t& operator<<(unsigned int i);
	virtual asciiIO_t& operator>>(long i);
	virtual asciiIO_t& operator<<(long i);
	virtual asciiIO_t& operator>>(unsigned long i);
	virtual asciiIO_t& operator<<(unsigned long i);
	virtual asciiIO_t& operator>>(float f);
	virtual asciiIO_t& operator<<(float f);
	virtual asciiIO_t& operator>>(double d);
	virtual asciiIO_t& operator<<(double d);

private:
	bool isAsciiChar(char s);

};