#include "VirtIO_t.h"

class binIO_t {

public:
	binIO_t(){/*only father fileds to set in the constructor*/};
	binIO_t(string path,size_t mode);
	virtual ~binIO_t(){/*file closed in farther*/};

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