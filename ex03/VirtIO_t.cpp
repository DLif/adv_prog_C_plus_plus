#include "virtIO_t.h"
#include <stdio.h>
#include <sys\types.h> 
#include <sys\stat.h> 


virtIO_t::~virtIO_t()
{
	if (io_status_flag != closed_e)
	{
		// file is open, close it
		fclose(filePtr);
	}

}

// construct an abstract file stream, without actually openning a file
// the stream is closed, reading a writing from it will result in an exception
// no IO buffer is currently used

virtIO_t::virtIO_t() : io_status_flag(virtIO_t::closed_e), currentBufferUsage(buffer_not_set)
{
	// file name automatically constructed to be an emptry string
}


// construct an abstract stream and open the file with given access mode
// in case of an error, io_status will be set to cant_open_file_e, but an exception will not be thrown
virtIO_t::virtIO_t(const string& filePath, const virtIO_t::access_mode& accessMode) : virtIO_t()
{
	// provide access mode and file path
	this->accessMode = accessMode;
	this->filePath = filePath;

	// open the file 
	if (virtIO_t::open())
	{
		// opened the file successfully
		this->io_status_flag = virtIO_t::ok_e;
	}
	else
	{
		// some error occured
		this->io_status_flag = virtIO_t::cant_open_file_e;
	}
}



// method opens file at current filePath
// returns false if some error occured, filePtr will point to NULL on error
// returns true if succesfull, filePtr will point to the opended file resource
bool virtIO_t::open()
{
	// fetch the open mode for the C function fread (note that this is a virtual call)
	string cOpenMode = translateAccessMode();

	// try to open the given file at filePath with given mode
	filePtr = fopen(filePath.c_str(), cOpenMode.c_str());

	if (filePtr == NULL)
	{
		// error occured
		return false; 
	}
	return true;

}

// this method translates accessMode into the C equivalent string representation
// note that this is a virtual function, and deriving classes may alter the access mode according to their needs
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
	if (this->io_status_flag == closed_e)
	{
		throw logic_error("Stream is not connected to a file!");
	}
	// use C function to fetch file size
	struct stat fileStats;
	if (stat(this->filePath.c_str(), &fileStats))
	{
		// some error occured
		throw runtime_error("Failed to compute file length");
	}
	
	return fileStats.st_size;
}




void virtIO_t::checkStreamValidity() const
{
	if (this->io_status_flag == closed_e)
	{
		throw logic_error("The stream is not connected to a file!");
	}

	if (!this->is_ok())
	{
		throw logic_error("You must clear the error flag before writing again");
	}

}


void virtIO_t::write(void *buff, size_t size, size_t count)
{

	checkStreamValidity();

	if (this->accessMode == read_m)
	{
		// read only mode
		throw logic_error("Invalid access: cannot write to file opened with read only access");
	}


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



void virtIO_t::read(const void *buff, size_t size, size_t count)
{

	checkStreamValidity();

	if (this->accessMode == append_m || this->accessMode == write_m)
	{
		// write only mode
		throw logic_error("Invalid access: cannot read from file opened with write only access (including append only)");
	}

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

	if (this->currentBufferUsage == virtIO_t::input_buffer)
	{
		// read len bytes 
		this->read(this->inputBuffer, 1, len);
	}
	else
	{
		// write len bytes 
		this->write(this->outputBuffer, 1, len);
	}

	// reset the IO buffer, must be set before each usage
	this->currentBufferUsage = virtIO_t::buffer_not_set;



}


