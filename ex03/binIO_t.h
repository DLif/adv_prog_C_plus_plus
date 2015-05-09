#include "virtIO_t.h"

class binIO_t {

public:

	
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

};