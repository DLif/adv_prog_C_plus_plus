#include "virtIO_t.h"
#include <stdio.h>
#include <sys\types.h> 
#include <sys\stat.h> 


virtIO_t::~virtIO_t()
{
	// simply close the file
	if (isOpen()){
		fclose(filePtr);
	}
}

// construct an abstract file stream
// basic initialization, does not set a fileName
// to actually open a file, call virtIO_t::open(fileName, accessMode) member function

virtIO_t::virtIO_t() : 
	currentBufferUsage(buffer_not_set),    /* current IO buffer not set by user */
	inputBuffer(NULL),                     /* no input buffer set */
	outputBuffer(NULL),                    /* no output buffer set */
	filePtr(NULL),                         /* no file is opened */
	io_status_flag(not_open_e),            /* status is not open */
	isFileSet(false)                       /* file path and access mode were not set*/
{
	
}


// construct an abstract stream with given filePath and accessMode
// this method only initailizes the stream state and 
// IMPORTANT: does not open the file, instead, call virtIO_t::open() member function

// NOTE: after the construction the file is not open, so, reading or writing from the stream will result in an exception
virtIO_t::virtIO_t(const string& filePath, const virtIO_t::access_mode& accessMode) : virtIO_t()
{
	// provide access mode and file path
	this->accessMode = accessMode;
	this->filePath = filePath;
	// file name and access mode provided, may use open()
	this->isFileSet = true;
}



// method opens file at current filePath, with accessMode
// in case of an error (cannot open file for some reason), io_status_flag will be set to cant_open_file_e
// and an exception will be thrown
// otherwise, if everything is ok, status flag will be set to ok_e
// note that this method may only be called if file name and access mode were previously set, otherwise an exception will be thrown

void virtIO_t::open()
{
	if (!isFileSet)
	{
		// file was not provided, cannot call open()
		throw logic_error("Error: file name and access mode were not provided, use overloaded open(..)");
	}
	// fetch the open mode for the C function fread (note that this is a virtual call)
	// binary IO for example, will want to append a 'b' to the access mode
	string cOpenMode = translateAccessMode();

	// try to open the given file at filePath with given mode
	filePtr = fopen(filePath.c_str(), cOpenMode.c_str());

	// open the file 
	if (filePtr)
	{
		// opened the file successfully
		this->io_status_flag = virtIO_t::ok_e;
	}
	else
	{
		// some error occured
		this->io_status_flag = virtIO_t::cant_open_file_e;
		throw runtime_error("Error: failed to open file: " + filePath);
	}

}

void virtIO_t::open(const string& filePath, const virtIO_t::access_mode& accessMode)
{
	if (isOpen())
	{
		throw logic_error("Error: a file is currently open! You must close() it first");
	}
	// set file information
	this->accessMode = accessMode;
	this->filePath = filePath;
	this->isFileSet = true;
	// open the file
	open();
}

void virtIO_t::close()
{
	if (!isOpen())
	{
		throw logic_error("Error: no file is open!");
	}

	fclose(filePtr);
	// mark that stream is closed
	set_io_status(not_open_e);
	// disable user IO buffer if such was provided
	currentBufferUsage = buffer_not_set;
}

// this method translates accessMode into the C equivalent string representation to be used by fopen(..) C method
// note that this is a virtual function, and deriving classes may alter the access mode according to their needs (example: binary)
string virtIO_t::translateAccessMode() const {

	switch (accessMode)
	{
	case virtIO_t::read_m:
		// read only more
		return "r";
	case virtIO_t::read_update_m:
		// read + update mode
		// file must exist
		return "r+";
	case virtIO_t::write_m:
		// write only 
		// If a file with the same name already exists, its contents are discarded and the file is treated as a new empty file
		return "w";
	case virtIO_t::write_update_m:
		// write + update mode
		// create an empty file and open it for update (both for input and output).
		// If a file with the same name already exists its contents are discarded and the file is treated as a new empty file.
		return "w+";
	case virtIO_t::append_m:
		// append mode
		// opens file for output at the end of a file. Output operations always write data at the end of the file, expanding it.
		// Repositioning operations are ignored. The file is created if it does not exist.
		return "a";
	case virtIO_t::append_update_m:
		// append + update mode
		// Open a file for update(both for input and output) with all output operations writing data at the end of the file
		// Repositioning operations(fseek, fsetpos, rewind) affects the next input operations, but output operations move the position back to the end of file.
		// The file is created if it does not exist.
		return "a+";
	default:
		return "";
	}


}

// method returns the file size/length in bytes
size_t virtIO_t::getFileLen() const
{
	if (this->io_status_flag == not_open_e)
	{
		throw logic_error("Error: no file is currently open");
	}
	// use C function to fetch file size
	struct stat fileStats;
	if (stat(this->filePath.c_str(), &fileStats))
	{
		// some error occured
		throw runtime_error("Error: failed to compute file length");
	}
	
	return fileStats.st_size;
}




void virtIO_t::write(const void *buff, size_t size, size_t count)
{

	// see if we can perform this action
	this->checkWriteAccessiblity();

	// try to get current position
	long  current_pos = findCurrentPosition();
	if (current_pos == -1L)
	{
		this->io_status_flag = writeErr_e;
		throw runtime_error("Write error (seek)");
	}

	// actually write
	size_t num_elems = fwrite(buff, size, count, this->filePtr);
	if (num_elems < count)
	{
		this->io_status_flag = writeErr_e;
		// reposition file position to where it was BEFORE error
		setFilePosition(current_pos);
		throw runtime_error("Write error");
	}

}



void virtIO_t::read(void *buff, size_t size, size_t count)
{

	// see if we can perform this action
	this->checkReadAccessiblity();


	// try to get current position
	long  current_pos = findCurrentPosition();
	if (current_pos == -1L)
	{
		this->io_status_flag = readErr_e;
		throw runtime_error("Read error (seek)");
	}

	// actually read
	size_t num_elems = fread((void*)buff, size, count, this->filePtr);
	if (num_elems < count)
	{
		this->io_status_flag = readErr_e;
		// reposition file position to where it was BEFORE error
		setFilePosition(current_pos);
		throw runtime_error("Read error");
	}

}







// valid for both ASCII and binary representations (since an ascii char fit exactly in one byte, thus writing them is the same)
void virtIO_t::operator,(size_t len)
{
	if (this->currentBufferUsage == virtIO_t::buffer_not_set)
	{
		throw logic_error("You must set the IO buffer first with << or >> operator !");
	}

	try{


		if (this->currentBufferUsage == virtIO_t::input_buffer)
		{
			// write len bytes from the input buffer into the file
			this->write(this->inputBuffer, 1, len);
		}
		else
		{
			// read len bytes from the file into outputBuffer 
			this->read(this->outputBuffer, 1, len);
		}

		// reset the IO buffer, must be set before each usage
		this->currentBufferUsage = virtIO_t::buffer_not_set;
	}
	catch (...)
	{
		// reset the IO buffer, must be set before each usage, even in case of an error
		this->currentBufferUsage = virtIO_t::buffer_not_set;

		// re-throw exception
		throw;
	}

	


}


