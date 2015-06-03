#include "cDate_t.h"
#include "cTime_t.h"
#include <limits.h>
#include <vector>
#include <iostream>
#include <string>

using namespace std;

static int getAnInteger(const string& toPrintAddition, const size_t limit_up, const size_t limit_down)
{
	int numToRead;
	cout << "\nChoose the number of " << toPrintAddition << ": " << endl;
	if (!(cin >> numToRead) || numToRead > limit_up || numToRead < limit_down){
		cout << "\nInvalid input! \nWill be set as " << limit_down << endl;
		numToRead = limit_down;
	}
	// clear rest of the line 
	cin.clear();
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	return numToRead;
}

cDate_t* find_date(vector<cDate_t*>& dateVector){
	int hour = getAnInteger("the day", 31,0);
	int minute = getAnInteger("the month", 12,1);
	int second = getAnInteger("the year", INT_MAX,1900);
	cDate_t newDate = cDate_t(hour, minute, second);

	for (cDate_t* date_b : dateVector){
		if (*(cDateBasicImpl*)(date_b->date) == *(cDateBasicImpl*)(newDate.date)){
			return date_b;
		}
	}
	cout << "\nNo such date" << endl;
	return NULL;
}

cTime_t* find_time(vector<cTime_t*> timeVector){
	int hour = getAnInteger("the hour", 23,0);
	int minute = getAnInteger("the minute", 60,0);
	int second = getAnInteger("the second", 60,0);
	cTime_t newTime = cTime_t(hour, minute, second);

	for (cTime_t* time : timeVector){
		if (*time == newTime){
			return time;
		}
	}
	cout << "\nNo such time" << endl;
	return NULL;
}



int main()
{
	bool cont = true;
	vector<cDate_t*> dateVector;
	vector<cTime_t*> timeVector;
	char c;

	//dateObj.addTimeSubject(&timeObj);

	cout << "\nPlease write the first letter of the method you wish to call from the following list: " << endl;

	while (cont)
	{

		cout << "\nTime (make new time) | Date (make new date) | set date to time | remove date from time | add times |  quit" << endl;
		cout << "\nAny time or date objects that are used for operations (set,add,etc.) should be made by Time or Date, accordingly." << endl;
		cin >> c;
		// clear rest of the line 
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		switch (c)
		{
		case 'T': {
			int hour = getAnInteger("the hour", 23,0);
			int minute = getAnInteger("the minute", 60,0);
			int second = getAnInteger("the second", 60,0);
			cTime_t* newTime = new cTime_t(hour, minute, second);
			timeVector.push_back(newTime);
			cout << "\nnew Time object made " << *newTime << endl;

			break;
			}
		case 'D': {
			int hour = getAnInteger("the day", 31,0);
			int minute = getAnInteger("the month", 12,1);
			int second = getAnInteger("the year", INT_MAX,1900); //TODO -fix limit issue later
			cDate_t* newDate = new cDate_t(hour, minute, second);
			dateVector.push_back(newDate);
			cout << "\nnew Date object made " << *newDate << endl;
			break;
		}
		case 's':{
			cout << "\nGive the parameters to get the observer(Date)" << endl;
			cDate_t* observer = find_date(dateVector);
			if (observer == NULL){
				break;
			}
			cout << "\nGive the parameters to get the subject(time)" << endl;
			cTime_t* subject = find_time(timeVector);
			if (subject == NULL){
				break;
			}
			subject->attach(observer);
			cout << "\nconnection made" << endl;
			break;
		}
		case 'r':{
			cout << "\nGive the parameters to get the observer(Date)" << endl;
			cDate_t* observer = find_date(dateVector);
			if (observer == NULL){
				break;
			}
			cout << "\nGive the parameters to get the subject(time)" << endl;
			cTime_t* subject = find_time(timeVector);
			if (subject == NULL){
				break;
			}
			subject->detach(observer);
			cout << "\nconnection removed" << endl;
			break;
		}
		case 'a':{
			cout << "\nA+=B" << endl;
			cout << "\ngive the parameters to get A" << endl;
			cTime_t* left = find_time(timeVector);
			if (left == NULL){
				break;
			}
			cout << "\ngive the parameters to get B" << endl;
			cTime_t* right = find_time(timeVector);
			if (right == NULL){
				break;
			}

			if (left->getTestSubject() != NULL){
				cout << "\nThe subject before addition: " << *(cDate_t*)(left->getTestSubject()) << endl;
				*left += *right;
				cout << "\nThe reasulted time is : " << *left << endl;
				cout << "\nThe subject after addition: " << *(cDate_t*)(left->getTestSubject()) << endl;
			}
			else{
				*left += *right;
			}
			
			break;
		}
		case 'q':{
			cont = false;
			break;
		}
		default:
			cout << "\nInvalid input" << endl;
			break;
		}
	}

	//clear vectors
	for (cDate_t* date : dateVector){
		delete date;
	}
	for (cTime_t* time : timeVector){
		delete time;
	}

	return 0;
}