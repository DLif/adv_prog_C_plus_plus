 #include <stdio.h>
#include <string>
using namespace std;

enum stream_e{ok_e=0,cant_open_file_e=1,bad_access_e=2,writeErr_e=4,readErr_e=8};
enum mode_flags{closed=0,input=1,output=2,binary=4,append=8};

class VirtIO_t {

public:
	VirtIO_t():file_descriptor(NULL),path(NULL),mode(closed){};
	VirtIO_t(string path,size_t mode);
	virtual ~VirtIO_t(){ fclose(file_descriptor);};

	VirtIO_t& operator>>(void* Buf); //this only set preperations for 
	VirtIO_t& operator<<(const void* Buf); 

	virtual VirtIO_t& operator>>(char c)=0; //- each child whrites in his own way. check if can put child as return type

	void  operator,(int len);        // for read / write blocks.
									 // first >> or << must come
									 //  two commas will be treaded ,(len1+len2)
									 // if the len is smaller than the number of bit remaining, exception will be thrown

	size_t getFileLen() const;
	string get_file_path() const;
	const char *get_file_access_mode() const;

	//status getters as requested in doc.
	bool is_ok_e() const;
	bool is_cant_open_file_e() const;
	bool is_bad_access_e() const;
	bool is_writeErr_e() const;
    bool is_readErr_e() const;
	bool operator!(); //== not is_ok_e()

	//on failure throw exception or just set status?
	void write(char *buff,size_t chunk_size,size_t chunk_num); //virtual for 
	void read(char *buff,size_t read_size);

	void clear(size_t set=ok_e);

private:
	size_t file_status;
	string path;
	size_t mode;
	FILE  *file_descriptor;
	VirtIO_t(const VirtIO_t &other){};
	VirtIO_t& operator=(const VirtIO_t &other){};
};

//binIO_t always in binary mode and assci always as non binary