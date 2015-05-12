#ifndef _VIRTIO_H
#define _VIRTIO_H

#include <string>
using namespace std;


class virtIO_t {

/*
	
GENERAL NOTES:

- Constructors do not perform file opening, use an open(..) method(s) after construction.

- Stream supports closing and openning new files, without constructing a new stream object.

- The streams are opened with the same formats as defined in stdio (for example 'r+' is represented by read_update_m)
  and the IO semantics are exactly the same. flush, seek, clear methods are also provided.
  [Note however that there is no 'b' or 't' flag equivalents, because access_mode enum does not represent a format, such as text or binary
   the format is enforced by the deriving classes, for example binIO_t will always open files with 'b' flag]

- Finally, just like in C++ streams, in case of a read/write error, the file position pointer will remain in the same position
  as it were before the read/write was performed.
	
*/



public:

	// io stream status flags
	enum io_status{ not_open_e, ok_e, cant_open_file_e, bad_access_e, writeErr_e, readErr_e };

	// access mode flags, same as those defined for fopen
	// note that the user may only choose the access mode in an abstract meaning, independat from formats (e.g. binary or text)
	// the format shall be determined by the deriving classes
	// for example, binIO_t always opens a file in binary mode, while asciiIO_t always opens a file in text mode
	enum access_mode { read_m, write_m, append_m, read_update_m, write_update_m, append_update_m };


	// construct an abstract file stream
	// basic initialization, does not set a fileName and access mode
	// to actually open a file, call virtIO_t::open(fileName, accessMode) member function

	virtIO_t();

	// construct an abstract stream with given filePath and accessMode
	// this method only initailizes the stream state
	// IMPORTANT: the CTOR does not open the file, instead, to open the file, call virtIO_t::open() member function
	// (this enables us to throw exceptions properly from outside the CTOR, and translate access mode polymorphically)

	// NOTE: after construction the file is not open, and any attempt to read/write to the stream
	// will throw an exception
	virtIO_t(const string& filePath, const virtIO_t::access_mode& accessMode);

	// method opens file at current filePath, with accessMode
	// in case of an error (cannot open file for some reason), io_status_flag will be set to cant_open_file_e
	// and an exception will be thrown
	// otherwise, if everything is ok, status flag will be set to ok_e
	// NOTE: 1. if filePath and accessMode were not previously set (e.g. used empty constructor) then an exception will be thrown
	//       2. If a file is currently open, an exception will be thrown without changing the state of the stream
	void open();

	// same as open above, but opens the file at given filePath with given accessMode
	// use this method to open a file after calling the empty constructor, or to open a different file after closing the previous
	void open(const string& filePath, const virtIO_t::access_mode& accessMode);

	// close currently open file.
	// Does not reset filePath and accessMode, may open again same file with virtIO_t::open() mem function
	// if no file is currently open, throws an exception
	void close(); 

	// if a file is currently open, closes the file
	virtual ~virtIO_t();

	inline virtIO_t& operator>>(void* output_buff);       // sets output buffer (to output to)
	inline virtIO_t& operator<<(const void* input_buff);  // sets input buffer (to read from)

	// write or read to input/output buffers previously set by the user (<< or >> buffer operators)
	// although a common implementation exists for binary and ascii for writing/reading bytes/chars
	// each deriving class could potentially choose a different approach (thats why its virtual)

	// NOTES:
	// - one of the operators >> or << for IO buffers should be called before using this operator
	//   if not, an exception will be thrown
	// - this will only read or write (but not both) according to the last << or >> operator call
	// - exceptions and error flags will be handled in the same manner as in write/read methods (see below)
	// - the call resets the IO buffer in the end of it
	//   (meaning that the user must call << or >> buffer operator before using this operator again)
	//   regardless to whether or not an error has occured

	virtual void operator,(size_t num_bytes);

	// pure virtual read/write operators
	// pure virtual - because each deriving class may implement these operations differently
	// for example, the implementations for ASCII, Binary, Unicode should be different
	virtual virtIO_t& operator>>(char& c) = 0;
	virtual virtIO_t& operator<<(char c) = 0;
	virtual virtIO_t& operator>>(unsigned char& c) = 0;
	virtual virtIO_t& operator<<(unsigned char c) = 0;
	virtual virtIO_t& operator>>(short& s) = 0;
	virtual virtIO_t& operator<<(short s) = 0;
	virtual virtIO_t& operator>>(unsigned short& s) = 0;
	virtual virtIO_t& operator<<(unsigned short s) = 0;
	virtual virtIO_t& operator>>(int& i) = 0;
	virtual virtIO_t& operator<<(int i) = 0;
	virtual virtIO_t& operator>>(unsigned int& i) = 0;
	virtual virtIO_t& operator<<(unsigned int i) = 0;
	virtual virtIO_t& operator>>(long& i) = 0;
	virtual virtIO_t& operator<<(long i) = 0;
	virtual virtIO_t& operator>>(unsigned long& i) = 0;
	virtual virtIO_t& operator<<(unsigned long i) = 0;
	virtual virtIO_t& operator>>(float& f) = 0;
	virtual virtIO_t& operator<<(float f) = 0;
	virtual virtIO_t& operator>>(double& d) = 0;
	virtual virtIO_t& operator<<(double d) = 0;


	     
	
	// getters for file length, file path and file access mode
	// 

	size_t getFileLen() const;                     // returns the file size in bytes 
												   // [throws exception if file is not open]

	inline string getFilePath() const;             // returns the file path
												   // [throws expcetion if was not previously set]
	                                              
	inline access_mode getFileAccessMode() const;  // returns the access mode
												   // [throws expcetion if was not previously set]

	// various IO status queries
	inline bool is_ok() const;
	inline bool is_cant_open_file() const;
	inline bool is_bad_access() const;
	inline bool is_writeErr() const;
	inline bool is_readErr() const;
	inline virtIO_t::io_status getStatus() const;

	// returns true iff a file is currently open
	inline bool isOpen() const;

	// returns true iff !is_ok(), meaning some error has occured
	// similar to ! operator implemented in std::ios class
	inline bool operator!() const; 

	// read and write bytes to file, similar to fread/fread C methods
	// size - sizeof a single element, count - number of elements to read/write
	// NOTES:
	// - in case of a write error or a read error, the appropriate io error flag will be set and an exception will be thrown
	//   note that when the stream encounters a read/write error, the file seek pointer will remain in its initial position
	//   the same behaviour as implemented for standard C++ IO
	// - in case access is not valid, io error flag will be set to bad_access_e and an exception will be thrown
	// - in case the file was not opened previously by calling open(..), or the stream is not ok_e, an exception will be thrown

	void write(const void *buff, size_t size, size_t count);  // write from buff into the file
	void read(void *buff, size_t size, size_t count);         // read from the file into buff

	// if the file is open, resets the status flag to ok_e
	// otherwise, throws an exception
	inline void clear();


	// locates correct position in the file 
	// in case of an error, -1L is returned
	// if file is not open, an exception is thrown

	inline long findCurrentPosition() const;

	// sets the current file position (from start)
	// returns true on success, false on failure
	// if file is not open, an exception is thrown
	inline bool setFilePosition(long int position) const;

	// flushes the file
	// returns true on success, returns false otherwise
	// if file is not open, an exception is thrown
	inline bool flush() const;

protected:


	// this method translates accessMode into the C equivalent string representation
	// to be used by fopen(..). Note that this is a virtual function, and
	// deriving classes may alter the access mode according to their needs (example: binary)
	// used by open() member function when openning the file
	virtual string translateAccessMode() const;

	// method sets the stream io status
	void set_io_status(io_status newStatus);

	
	// returns the current open file pointer
	// if no file is currently open, returns NULL
	inline FILE* getFilePtr() const;

	// method checks if the stream is ready to accept reads
	// specifically, it checks the following:
	// 1. the file is open and the stream is not broken (status is ok_e)
	// 2. the stream is open for read access
    // if one of the above does not hold, an appropriate exception is thrown
	// in case of an invalid access, the status flag will be set to bad_access_e
	inline void checkReadAccessiblity();

	// method checks if the stream is ready to accept writes
	// specifically, it checks the following:
	// 1. the file is open and the stream the stream is not broken (status is ok_e)
	// 2. the stream is open for write access
	// if one of the above does not hold, an appropriate exception is thrown
	// in case of an invalid access, the status flag will be set to bad_access_e
	inline void checkWriteAccessiblity();

	

private:

	// which IO buffer is currently used (input/output/none)
	enum IOBufferUsage { buffer_not_set, input_buffer, output_buffer };

	

	io_status io_status_flag;		   // io status as defined in the corresponding enum above
	string filePath;                   // path to the file
	access_mode accessMode;			   // access mode as defined in the corresponding enum above
	bool isFileSet;                    // holds whether or not filePath and accessMode were set

	FILE* filePtr;                     // actual file pointer
	const void* inputBuffer;           // input buffer (we will read from this buffer when , operator is used)
	void*       outputBuffer;          // output buffer (we will write to this buffer when , operator is used)
	IOBufferUsage currentBufferUsage;  // which buffer is currently used, inputBuffer, or outputBuffer, or neither of them
	

	// stream is non copyable  
	virtIO_t(const virtIO_t &);               
	virtIO_t& operator=(const virtIO_t &);

};


/* ------------------------------------- INLINE member functions implementation ----------------------------------------*/



// set output buffer
inline virtIO_t& virtIO_t::operator>>(void* buffer)
{
	this->currentBufferUsage = output_buffer;
	this->outputBuffer = buffer;

	return *this;
}

// set input buffer
inline virtIO_t& virtIO_t::operator<<(const void* buffer)
{
	this->currentBufferUsage = input_buffer;
	this->inputBuffer = buffer;

	return *this;
}


// method tries to find current position in the file
// returns the current position inside the file
// returns -1L in case of an error

inline long virtIO_t::findCurrentPosition() const
{
	if (!isOpen())
	{
		throw logic_error("Error: no file is currently open");
	}
	return ftell(this->filePtr);
}

// sets the file position to given position
// returns true on success, false otherwise
inline bool  virtIO_t::setFilePosition(long int position) const
{
	if (!isOpen())
	{
		throw logic_error("Error: no file is currently open");
	}
	return fseek(this->filePtr, position, SEEK_SET) == 0;
}

// flushes file to storage
// returns true on success, false otherwise
// if file is not open, exception is thrown 
inline bool virtIO_t::flush() const
{
	if (!isOpen())
	{
		throw logic_error("Error: no file is currently open");
	}
	return fflush(filePtr) == 0;
}


inline FILE* virtIO_t::getFilePtr() const{
	
	if (isOpen())
		return this->filePtr;
	return 0;
}

inline bool virtIO_t::is_ok() const
{
	return this->io_status_flag == ok_e;
}

inline bool virtIO_t::is_bad_access() const
{
	return this->io_status_flag == bad_access_e;
}


inline bool virtIO_t::is_cant_open_file() const
{
	return this->io_status_flag == cant_open_file_e;
}

inline bool virtIO_t::is_writeErr() const
{
	return this->io_status_flag == writeErr_e;
}

inline bool virtIO_t::is_readErr() const
{
	return this->io_status_flag == readErr_e;
}


// protected method, to be used by deriving classes
inline void virtIO_t::set_io_status(virtIO_t::io_status newStatus)
{
	this->io_status_flag = newStatus;

}

inline virtIO_t::io_status virtIO_t::getStatus() const
{
	return this->io_status_flag;
}

// returns true iff !is_ok(), meaning some error has occured
// similar to ! operator implemented in std::ios class
inline bool virtIO_t::operator!() const
{
	return !this->is_ok();
}


inline string virtIO_t::getFilePath() const
{
	if (!isFileSet)
	{
		throw logic_error("Error: file path is not set");
	}
	return this->filePath;
}

inline virtIO_t::access_mode virtIO_t::getFileAccessMode() const
{
	if (!isFileSet)
	{
		throw logic_error("Error: acess mode is not set");
	}
	return this->accessMode;
}

// clear error status
inline void virtIO_t::clear()
{
	if (isOpen()){
		this->io_status_flag = ok_e;
	}
	else
	{
		throw logic_error("Error: no file is currently open");
	}
}


inline void virtIO_t::checkWriteAccessiblity()
{
	
	if (!isOpen())
	{
		throw logic_error("Error: must open the file before writing to it");
	}

	if (!this->is_ok())
	{
		throw logic_error("Error: must clear error flags before writing to the stream again");
	}

	if (this->accessMode == read_m)
	{
		// read only mode
		this->io_status_flag = bad_access_e;
		throw logic_error("Invalid access: cannot write to file opened with read only access");
	}
}

inline void virtIO_t::checkReadAccessiblity()
{

	if (!isOpen())
	{
		throw logic_error("Error: must open the file before reading from it");
	}
	if (!this->is_ok())
	{
		throw logic_error("Error: must clear error flags before reading from the stream again");
	}

	if (this->accessMode == append_m || this->accessMode == write_m)
	{
		// write only mode
		this->io_status_flag = bad_access_e;
		throw logic_error("Invalid access: cannot read from file opened with write only access (including append only)");
	}

}

// returns true iff a file is currently open
inline bool virtIO_t::isOpen() const
{
	if (this->io_status_flag == not_open_e)
	{
		// no file is open and there was no attempt to open a file
		return false;
	}
	if (this->io_status_flag == cant_open_file_e)
	{
		// unsuccessful attempt to open a file
		return false;
	}
	return true;
}


#endif
