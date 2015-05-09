#include "virtIO_t.h"

class asciiIO_t : public virtIO_t {

public:

	// default implementation will suffice, 
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


protected:

	// a generic method to read into the given container, one element, according to the given parse string
	// this method already sets the io_status_flag to readErr_e in case of an error and throws exceptions
	// its also important to note that in case of a read error, the seek position will remain the same as before the read
	void readByParseString(void* container, const string& parse_string);


	// a generic method to write into the file from given container, one element, according to the given parse string
	// this method already sets the io_status_flag to writeErr_e in case of an error and throws exceptions
	// its also important to note that in case of a write error, the seek position will remain the same as before the write
	void writeByParseString(void* container, const string& parse_string);

};