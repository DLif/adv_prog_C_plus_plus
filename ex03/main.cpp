#include "binIO_t.h"
#include "asciiIO_t.h"

#include <iostream>
#include <string>
using namespace std;

static string translateStatus(const virtIO_t::io_status ioStatus);
static string translateAccessMode(const virtIO_t::access_mode accessMode);
static virtIO_t* chooseFile(string printPorpose);
static int getAnInteger(string toPrintAddition);
static void processCommands();


binIO_t *binFile=NULL;
asciiIO_t *asciiFile=NULL;

int main()
{
	processCommands();
	return 0;
}

static string translateStatus(const virtIO_t::io_status ioStatus){
	switch (ioStatus)
	{
	case  virtIO_t::ok_e:
		return "ok_e";
	case virtIO_t::cant_open_file_e:
		return "cant_open_file_e";
	case virtIO_t::bad_access_e:
		return "bad_access_e";
	case virtIO_t::writeErr_e:
		return "writeErr_e";
	case virtIO_t::readErr_e:
		return "readErr_e";
	}
}

//In fact only these who inherite from virtIO_t should know this function, but here I use a similar function for prety printing
static string translateAccessMode(const virtIO_t::access_mode accessMode){

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

static virtIO_t* chooseFile(string printPorpose){
	char c;
	cout <<  printPorpose <<": binary (B) or ascii(A)" << endl;
	cin >> c;
	// clear rest of the line 
	cin.clear();
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	switch (c)
	{
	case 'A':
		return asciiFile;
	case 'B':
		return binFile;
	default:
		cout << "\nInvalid input" << endl;
		return NULL;
	}
}

static int getAnInteger(string toPrintAddition)
{
	int numToRead;
	cout << "\nChoose number "<< toPrintAddition <<": " << endl;
	if (!(cin >> numToRead)){
		cout << "\nInvalid input! \nWill be set as 0" << endl;
		numToRead = 0;
	}
	// clear rest of the line 
	cin.clear();
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	return numToRead;

}

static virtIO_t::access_mode acessModeFromUser()
{
	char c;

	cout << "\n\tchoose acess mode:" << endl;
	cout << "\nread(R) | write(W) | append(A) | read and update file(r) | write and update file(w) | read and update file(r) | append and update file(a) | clear(c)"<< endl;
	cin >> c;
	// clear rest of the line 
	cin.clear();
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	switch (c)
	{
	case 'R':
		return virtIO_t::read_m;
	case 'W':
		return virtIO_t::write_m;
	case 'A':
		return virtIO_t::append_m;
	case 'r':
		return virtIO_t::read_update_m;
	case 'w':
		return virtIO_t::write_update_m;
	case 'a':
		return virtIO_t::append_update_m;
	default:
		cout << "\nInvalid input" << endl;
		return acessModeFromUser();
	}
}

static void processCommands()
{
	char newFilePath[1025]={0};
	bool cont = true;
	char c;
	

	cout << "\nPlease write the first letter of the method you wish to call from the following list: " << endl;

	while (cont)
	{

		cout << "\nnew ascci file(A) (old ascii file will be closed) | new binary file(B) (old binary file will be closed) | read form file(R) | write to file (W) | get file path(p) | get file acess mode(m) | get file status(s) | write int(w) | read int(r) | quit" << endl;

		cin >> c;
		// clear rest of the line 
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		switch (c)
		{
		case 'A': {
			delete asciiFile;	//destroy old ascii file

			//Now make new one
			cout << "\nNew ascii file:\n\tchoose path:(max size 1024 chars)" << endl;
			cin >> newFilePath;
			newFilePath[1024]=0;//just in case, so it will still be a valid string even if the user wrote more than 1024 chars

			asciiFile = new asciiIO_t(string(newFilePath),acessModeFromUser());
			asciiFile->open();
			break; }
		case 'B': {
			delete binFile;	//destroy old bin file

			//Now make new one
			cout << "\nNew bin file:\n\tchoose path:(max size 1024 chars)" << endl;
			cin >> newFilePath;
			newFilePath[1024]=0;//just in case, so it will still be a valid string even if the user wrote more than 1024 chars

			binFile = new binIO_t(string(newFilePath),acessModeFromUser());
			binFile->open();
			break; }
		
		case 'R': {
			int numToRead=0;
			char *tempBuff=NULL;

			virtIO_t *steramToRead=chooseFile("\nChoose file to read");
			if (steramToRead==NULL){
				cout << "\nThe file isn't initialized" <<  endl;
				break;
			}
			if(!steramToRead->is_ok()){
				cout << "\nFile status isn't ok_e. please check the problem and use clesr before reading" << endl;
				break;
			}
			numToRead=getAnInteger("of bytes to read");

			tempBuff = new char[numToRead+1]; // alocate temp buffer
			tempBuff[numToRead]=0;// set string terminator

			try{
			*steramToRead >> tempBuff,numToRead; //read fro device
			}
			catch(exception& e){
				cerr << "Falid in reading: "<< e.what()<< endl;
				break;
			}

			cout << "\nForm file: \n" << string(tempBuff) << endl;

			delete tempBuff;
			break; }
		case 'W': {
			int numToRead=0;
			char tempBuff[1025]={0};

			virtIO_t *steramToRead=chooseFile("\nChoose file to write");
			if (steramToRead==NULL){
				cout << "\nThe file isn't initialized" <<  endl;
				break;
			}
			if(!steramToRead->is_ok()){
				cout << "\nFile status isn't ok_e. please check the problem and use clesr before writing" << endl;
				break;
			}
			numToRead=getAnInteger("of bytes to write(max 1024)");

			cout << "\nNow type your text" << endl;
			cin >> tempBuff; //get from user what to write
			tempBuff[1024]=0;// set string terminator, just in case

			try{
			*steramToRead << tempBuff,numToRead; //write to device
			}
			catch(exception& e){
				cerr << "Falid in writing: "<< e.what()<< endl;
				break;
			}

			cout << "\nTo file: \n" << string(tempBuff) << endl;

			break; }
		case 'p': {
			virtIO_t *steramToRead=chooseFile("\nChoose file to get path");
			if (steramToRead==NULL){
				cout << "\nThe file isn't initialized is: " <<  endl;
				break;
			}
			cout << "\nThe file path is: " << steramToRead->getFilePath() << endl;
			break; }
			
		case 'm': {
			virtIO_t *steramToRead=chooseFile("\nChoose file to get mode");
			if (steramToRead==NULL){
				cout << "\nThe file isn't initialized is: " <<  endl;
				break;
			}
			cout << "\nThe file acess mode is: " << translateAccessMode(steramToRead->getFileAccessMode()) << endl;
			break; }
		case 's': {
			virtIO_t *steramToRead=chooseFile("\nChoose file to get status");
			if (steramToRead==NULL){
				cout << "\nThe file isn't initialized is: " <<  endl;
				break;
			}
			cout << "\nThe file status is: " << translateStatus(steramToRead->getStatus()) << endl;
			break; }
		case 'q': {
			cont = false;
			break; }
		case 'r': {
			int i=-1;
			virtIO_t *steramToRead=chooseFile("\nChoose file to read an integer from");
			if (steramToRead==NULL){
				cout << "\nThe file isn't initialized" <<  endl;
				break;
			}
			if(!steramToRead->is_ok()){
				cout << "\nFile status isn't ok_e. please check the problem and use clesr before reading" << endl;
				break;
			}

			try{
			*steramToRead >> i; //danger
			}
			catch(exception& e){
				cerr << "Falid in reading int: "<< e.what()<< endl;
				break;
			}

			cout << i;
			break; }
		case 'w': {
			int i=-1;
			virtIO_t *steramToRead=chooseFile("\nChoose file to write an integer to");
			if (steramToRead==NULL){
				cout << "\nThe file isn't initialized" <<  endl;
				break;
			}
			if(!steramToRead->is_ok()){
				cout << "\nFile status isn't ok_e. please check the problem and use clesr before reading" << endl;
				break;
			}

			i=getAnInteger("to write to the file");

			try{
			*steramToRead << i; //danger
			}
			catch(exception& e){
				cerr << "Falid in writing int: "<< e.what()<< endl;
				break;
			}

			break; }

		case 'c': {
			virtIO_t *steramToRead=chooseFile("\nChoose file to clear");
			if (steramToRead==NULL){
				cout << "\nThe file isn't initialized" <<  endl;
				break;
			}
			steramToRead->clear();
			cout << "\nfile cleared" << endl;
			break;
				  }
		default:
			cout << "\nInvalid input" << endl;
			break;

		}

	}
	// delete all elements left in calendar
	delete asciiFile;
	delete binFile;
}