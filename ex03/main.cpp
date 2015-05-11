#include "binIO_t.h"
#include "asciiIO_t.h"
#include <iostream>

int main()
{
	
	string file_name = "file.txt";

	binIO_t bin(file_name, virtIO_t::read_m);
	if (!bin)
	{
		cout << "error";
	}

	


	return 0;
}