#ifndef _VIRTIO_H
#define _VIRTIO_H

#include <string>
using namespace std;


class virtIO_t {

public:

	// io status flags
	enum io_status{ closed_e, ok_e, cant_open_file_e, bad_access_e, writeErr_e, readErr_e };

	// access mode flags, same (in their semantic meaning) as those defined for fopen
	enum access_mode { read_m, write_m, append_m, read_update_m, write_update_m, append_update_m };


	// initializes a stream object, without opening a file.
	virtIO_t();


	// constructs stream + opens the file at given path with given accessMode
	// if file cannot be opened, io_status will be set to cant_open_file_e
	// this is the only case where an error flag is set without throwing an exception
	// since, throwing exceptions from a constructor is considered bad practice.
	virtIO_t(const string& filePath, const virtIO_t::access_mode& accessMode);



	// if a file is currently open, closes the file
	virtual ~virtIO_t();

	virtIO_t& operator>>(void* output_buff);       // sets output buffer
	virtIO_t& operator<<(const void* input_buff);  // sets input buffer

	// pure virtual read/write operators
	// pure virtaul - because each deriving class may implement these operations differently
	// for example, the implementations for ASCII, Binary, Unicode should all be different
	virtual virtIO_t& operator>>(char c) = 0;
	virtual virtIO_t& operator<<(char c) = 0;
	virtual virtIO_t& operator>>(unsigned char c) = 0;
	virtual virtIO_t& operator<<(unsigned char c) = 0;
	virtual virtIO_t& operator>>(short s) = 0;
	virtual virtIO_t& operator<<(short s) = 0;
	virtual virtIO_t& operator>>(unsigned short s) = 0;
	virtual virtIO_t& operator<<(unsigned short s) = 0;
	virtual virtIO_t& operator>>(int i) = 0;
	virtual virtIO_t& operator<<(int i) = 0;
	virtual virtIO_t& operator>>(unsigned int i) = 0;
	virtual virtIO_t& operator<<(unsigned int i) = 0;
	virtual virtIO_t& operator>>(long i) = 0;
	virtual virtIO_t& operator<<(long i) = 0;
	virtual virtIO_t& operator>>(unsigned long i) = 0;
	virtual virtIO_t& operator<<(unsigned long i) = 0;
	virtual virtIO_t& operator>>(float f) = 0;
	virtual virtIO_t& operator<<(float f) = 0;
	virtual virtIO_t& operator>>(double d) = 0;
	virtual virtIO_t& operator<<(double d) = 0;


	// write or read to input/output buffers
	// although a common implementation exists for binary and ascii for writing bytes/chars
	// each deriving class could potentially choose a different approach 
	// (for example interpreting the bytes in a different manner), so this method should be virtual
	virtual void operator,(size_t num_bytes);        
	
	// getters for file length, file path and file access mode
	size_t getFileLen() const;                     // returns the file size in bytes 
												   // throws exception if file is not open

	inline string getFilePath() const;             // throws exception if file is not open
	inline access_mode getFileAccessMode() const;  // throws exception if file is not open

	// various IO status queries
	inline bool is_ok() const;
	inline bool is_cant_open_file() const;
	inline bool is_bad_access() const;
	inline bool is_writeErr() const;
	inline bool is_readErr() const;
	inline virtIO_t::io_status getStatus() const;

	// returns true iff !is_ok(), meaning some error has occured
	// similar to ! operator implemented in std::ios class
	inline bool operator!() const; 

	// read and write chunks of bytes, similar to fread/fread C methods
	// size - sizeof a single element, count - number of elements to read/write
	// in case of a write error or a read error, the appropriate io error flag will be set and an exception will be thrown
	void write(void *buff, size_t size, size_t count);
	void read(const void *buff, size_t size, size_t count);

	// reset the status flag to ok_e
	inline void clear();

protected:

	// which IO buffer is currently used (input/output/non)
	enum IOBufferUsage { buffer_not_set, input_buffer, output_buffer };

	// this method recieves our access mode to a corresponding string representation
	// valid for usage with fopen C method
	// may be overriden in deriving classes, if a different mode needs to be returned (example: binary mode)
	virtual string translateAccessMode() const;

	// method sets the stream io status
	void set_io_status(io_status newStatus);

	// method tries to find current position in the file
	// returns the current position inside the file
	// the parameter is only relevant for the error flag and exception (indications the context of the call)

	// locates correct position in the file 
	// in case of an error, -1L is returned
	// note that this method assumes that a file is open
	inline long findCurrentPosition() const;

	// sets the current position file position (from start)
	// returns true on success, false on failure
	inline bool setFilePosition(long int position) const;

	// sets the usage of the IOBuffer, either for input or output
	inline void setIOBufferPurpose(IOBufferUsage usage);

	// returns the current open file pointer
	// if no file is currently open, returns NULL
	inline FILE* getFilePtr() const;

	// checks the following
	// 1. the stream is not closed
	// 2. the stream is ok (no error flag is set)
	// if no one those does not hold, an appropriate exception is thrown
	inline void checkStreamValidity() const;

private:


	io_status io_status_flag;		   // io status as defined in the corresponding enum above
	string filePath;                   // path of the file that was opened
	access_mode accessMode;			   // access mode as defined in the corresponding enum above
	FILE* filePtr;                     // actual file pointer
	const void* inputBuffer;           // input buffer (we will read from this buffer when , operator is used)
	void*       outputBuffer;          // output buffer (we will write to this buffer when , operator is used)
	IOBufferUsage currentBufferUsage;  // which buffer is currently used, inputBuffer, or outputBuffer, or neither of them

	// stream is non copyable  
	virtIO_t(const virtIO_t &other);               
	virtIO_t& operator=(const virtIO_t &other);

	// method opens the file at filePath with access as returned by translateAccessMode()
	// in case of an error, method returns false, if opened successfully, returns true
	bool open();



};


#endif
