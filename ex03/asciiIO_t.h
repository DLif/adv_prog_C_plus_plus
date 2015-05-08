#include "VirtIO_t.h"

class asciiIO_t {

public:
	asciiIO_t(){/*only father fileds to set in the constructor*/};
	asciiIO_t(string path,size_t mode);
	virtual ~asciiIO_t(){/*file closed in farther*/};

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