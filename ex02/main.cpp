#include "DayCalendar_t.h"
#include "MeetingLocation_t.h"
#include <iostream>
#include <sstream>

using namespace std;


template <class T>
static Meeting_t<T>* getMeeting(bool withLocation)
{
	bool error = false;

	Meeting_t<T>* meeting;
	
	if (withLocation)
	{
		meeting = new MeetingLocation_t < T >;
		cout << "\nEnter a Meeting information (including location), in the following order: start time, finish time, topic, location" << endl;
	}
	else
	{
		meeting = new Meeting_t < T > ;
		cout << "\nEnter a Meeting information, in the following order: start time, finish time, topic" << endl;
	}
	
	try {
		cin >> *meeting;
	}
	catch (invalid_argument& invalid_arg_exception)
	{
		cout << "\nException thrown: " << invalid_arg_exception.what() << endl;
		error = true;
	}

	// clear rest of the line
	cin.clear();
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	if (error)
	{	
		delete meeting;
		return NULL;
	}

	return meeting;
}


template <class T>
static T getStartingTime()
{
	T startingTime;
	cout << "\nEnter starting time" << endl;
	if (!(cin >> startingTime))
	{
		cout << "\nInvalid input! \nWill be set as 0" << endl;
		startingTime = 0;
	}
	// clear errors and the rest of the line
	cin.clear();
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	return startingTime;
}



// main loop of the program
// processes commands from the input

template <class T>
static void processCommands()
{


	DayCalendar_t<T>* calendar = new DayCalendar_t<T>;
	T startingTime;
	bool cont = true;
	Meeting_t<T>* meeting;
	char c;
	

	cout << "\nPlease write the first letter of the method you wish to call from the following list: " << endl;

	while (cont)
	{

		cout << "\nadd meeting | Add meeting with address | count (num of meetings) | find meeting | remove meeting | print calendar | Remove all | delete all | isEmpty | quit" << endl;

		cin >> c;
		// clear rest of the line 
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		switch (c)
		{
		case 'a':
			cout << "\nNew meeting addition (without address)" << endl;
			meeting = getMeeting<T>(false);
			if (meeting == NULL)
				break;
			try {
				calendar->addMeeting(meeting);
			}
			catch (invalid_argument& invalid_arg_exception)
			{
				cout << "\nException thrown: " << invalid_arg_exception.what() << endl;
		
			}

			break;
		case 'A':
			cout << "\nNew meeting addition (WITH address)" << endl;
			meeting = getMeeting<T>(true);
			if (meeting == NULL)
				break; 

			try
			{
				calendar->addMeeting(meeting);
			}
			catch (invalid_argument& invalid_arg_exception)
			{
				cout << "\nException thrown: " << invalid_arg_exception.what() << endl;
			}
			break; 
		
		case 'f':
			cout << "\nFind meeting by start hour method" << endl;
			startingTime = getStartingTime<T>();
			meeting = calendar->findMeeting(startingTime);
			if (meeting == NULL)
			{
				cout << "\nNo such meeting exists" << endl;
			}
			else
			{
				cout << "Found: " << *meeting << endl;
			}

			break;
		case 'r':
			cout << "\nRemove meeting by start hour method" << endl;
			startingTime = getStartingTime<T>();
			meeting = calendar->removeMeeting(startingTime);
			if (meeting == NULL)
			{
				cout << "\nNo such meeting exists" << endl;
			}
			else
			{
				cout << "Removed: " << *meeting << endl;
				delete meeting;
			}

			break;
		case 'p':
			cout << "\nCalendar << operator" << endl;
			cout << *calendar << endl;
			break;
			
		case 'R':

			calendar->removeAll();
			cout << "\nRemoved all meetings from calendar (without delete)" << endl;
	
			break;
		case 'd':
			
			calendar->deleteAll();
			cout << "\nRemoved all meetings from calendar (WITH delete)" << endl;
			break;

		case 'q':
			cont = false;
			break;
		case 'i':
			cout << "\nisEmpty method" << endl;
			cout << (calendar->isEmpty() ? "Calendar is empty" : "Calendar is not empty!") << endl;
			break;
		case 'c':
			cout << "\ngetMeetingsCount method" << endl;
			cout << calendar->getMeetingsCount() << " meetings for today" << endl;
			break;
		default:
			cout << "\nInvalid input" << endl;
			break;

		}

	}
	// delete all elements left in calendar
	calendar->deleteAll();
	delete calendar;




}

int main()
{
	

	char c;
	cout << "Select the type of the calendar and meetings: f (float) or i (integer) " << endl;
	if (!(cin >> c) || (c!='f') && (c!= 'i')){
		cout << "\nInvalid input!, program will close" << endl;
		return 0;
	}
	// clear rest of the line 
	cin.clear();
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	if (c == 'f')
	{
		cout << "Valid time values are all float values in 0-24, for example: 24, 0.00, 13.5 (13 and a half), 13.75\n" << endl;
		processCommands<float>();
	}
	else
	{
		cout << "Valid time values are all int values in 0-24, for example: 24, 0, 8, 13\n" << endl;
		processCommands<int>();
	}
		

}