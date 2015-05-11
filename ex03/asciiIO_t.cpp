#include "asciiIO_t.h"


// intialize an ascii file stream
// again, let the base class do all the work
asciiIO_t::asciiIO_t(const string& path, const virtIO_t::access_mode& accessMode) : virtIO_t(path, accessMode)
{}


asciiIO_t::~asciiIO_t(){
	// base implmentation suffices
	// closes the file if open
}

void asciiIO_t::readByParseString(void* container, const string& parse_string)
{

	this->checkReadAccessiblity();

	// get current position
	long currentPos = this->findCurrentPosition();
	if (currentPos == -1L)
	{
		this->set_io_status(virtIO_t::readErr_e);
		throw runtime_error("Read error(seek)");
	}

	// read one object from the file and store in the container
	if (fscanf(this->getFilePtr(), parse_string.c_str(), container) < 1)
	{
		// restore the position
		this->setFilePosition(currentPos);
		this->set_io_status(virtIO_t::readErr_e);

		throw runtime_error("Read error");
	}

}
