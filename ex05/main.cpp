#include "cDate_t.h"
#include "cTime_t.h"
#include <limits.h>
#include <vector>
#include <iostream>
#include <string>
#include <exception>
#include <algorithm>

using namespace std;

static size_t getAnInteger(const string& toPrintAddition)
{
	size_t numToRead;
	cout << "\nEnter a " << toPrintAddition << ": " << endl;
	if (!(cin >> numToRead)){
		cout << "\nInvalid input! \nWill be set as " << 0 << endl;
		numToRead = 0;
	}
	// clear rest of the line 
	cin.clear();
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	return numToRead;
}

static cDate_t* find_date(vector<cDate_t*>& dateVector, size_t index){
	if (dateVector.size() <= index){
		cout << "\nIndex out of bounds" << endl;
		return NULL;
	}
	
	return dateVector[index];
}

static cTime_t* find_time(vector<cTime_t*> timeVector, size_t index){
	
	if (timeVector.size() <= index)
	{
		cout << "\nIndex out of bounds" << endl;
		return NULL;
	}
	
	return timeVector[index];
}


struct Comparator
{

	cTime_t* timeObj;
	cDate_t* dateObj;
	Comparator(cTime_t* timeObj, cDate_t* dateObj)
	{
		this->timeObj = timeObj;
		this->dateObj = dateObj;
	}

	bool operator()(pair<cTime_t*, cDate_t*>* val)
	{
		if (val->first == timeObj && val->second == dateObj) return true;
		return false;
	}

};


struct ComparatorFirstValue
{

	cTime_t* timeObj;
	
	ComparatorFirstValue(cTime_t* timeObj)
	{
		this->timeObj = timeObj;
		
	}

	bool operator()(pair<cTime_t*, cDate_t*>* val)
	{
		if (val->first == timeObj) return true;
		return false;
	}

};

int main()
{
	bool cont = true;
	vector<cDate_t*> dateVector;
	vector<cTime_t*> timeVector;
	vector<pair<cTime_t*, cDate_t*>*> subjectToObserver;
	typedef vector<pair<cTime_t*, cDate_t*>*>::iterator pair_iter;
	char c;

	//dateObj.addTimeSubject(&timeObj);

	cout << "\nPlease write the first letter of the method you wish to call from the following list: " << endl;

	while (cont)
	{

		cout << "\nTime (make new time) | Date (make new date) | set date to time | remove date from time | add times | Print date info |  quit" << endl;
		cout << "\nAny time or date objects that are used for operations (set,add,etc.) should be created by Time or Date, accordingly." << endl;
		cin >> c;
		// clear rest of the line 
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		switch (c)
		{
		case 'T': {
			size_t hour = getAnInteger("hour [0-23]");
			size_t minute = getAnInteger("minute [0-59]");
			size_t second = getAnInteger("seconds [0-59]");
			try{

				cTime_t* newTime = new cTime_t(hour, minute, second);
				timeVector.push_back(newTime);
				cout << "\nnew cTime_t object made: ";
				newTime->print(cout, cTime_t::PrintFormat::TwelveHours) << endl;
			}
			catch (exception& ex)
			{
				cout << ex.what() << endl << endl;
			}
		

			break;
		}
		case 'D': {
			size_t day = getAnInteger("day [1-31]");
			size_t month = getAnInteger("month [1-12]");
			size_t year = getAnInteger("year >= 1900");
			try
			{
				cDate_t* newDate = new cDate_t(day, month, year);
				dateVector.push_back(newDate);
				cout << "\nnew cDate_t object made: ";
				newDate->print(cout, "EU-TEXT") << endl;
			}
			catch (exception& ex)
			{
				cout << ex.what() << endl << endl;
			}
			break;
		}
		case 's':{
			try
			{
				
				cDate_t* observer = find_date(dateVector, getAnInteger("index of date"));
				if (observer == NULL){
					break;
				}

				cTime_t* subject = find_time(timeVector, getAnInteger("index of time"));
				if (subject == NULL){
					break;
				}
				observer->setSubject(subject);
				cout << "Date: ";
				observer->print(cout, "EU-TEXT");
				cout << " now observers time object: ";
				subject->print(cout, cTime_t::PrintFormat::TwelveHours) << endl;
				subjectToObserver.push_back(new pair<cTime_t*, cDate_t*>(subject, observer));
			}
			catch (exception& ex)
			{
				cout << ex.what() << endl << endl;
			}

			break;
		}
		case 'r':{
			try

			{
				cDate_t* observer = find_date(dateVector, getAnInteger("index of date"));
				if (observer == NULL){
					break;
				}

				cTime_t* subject = find_time(timeVector, getAnInteger("index of time"));
				if (subject == NULL){
					break;
				}

				pair_iter iter;
				if ((iter = find_if(subjectToObserver.begin(), subjectToObserver.end(), Comparator(subject, observer))) == subjectToObserver.end())
				{
					cout << "Given date is not observing given time" << endl;
					break;
				}
				// this will also detach from subject
				observer->setSubject(0);
				cout << "\nconnection removed" << endl;

				subjectToObserver.erase(iter);
			}
			catch (exception& ex)
			{
				cout << ex.what() << endl;
			}
			break;
		}
		case 'a':{
			try
			{
				cout << "\nA+=B" << endl;
				
				cTime_t* left = find_time(timeVector, getAnInteger("index of A time"));
				if (left == NULL){
					break;
				}
				
				cTime_t* right = find_time(timeVector, getAnInteger("index of B time"));
				if (right == NULL){
					break;
				}

				pair_iter iter;
				if ((iter = find_if(subjectToObserver.begin(), subjectToObserver.end(), ComparatorFirstValue(left))) == subjectToObserver.end())
				{
					cout << "A does not have observers, select a time that is observed" << endl;
					*left += *right;
				}
				else
				{

					cout << "\nThe subject before addition: ";
					((*iter)->second)->print(cout, "EU") << endl;
					*left += *right;
					cout << "\nThe subject after addition: ";
					((*iter)->second)->print(cout, "EU") << endl;
				}

				cout << "\nThe result time is : ";
				left->print(cout, cTime_t::PrintFormat::TwelveHours) << endl;
			}
			catch (exception& ex)
			{
				cout << ex.what() << endl;
			}
			
			break;
		}
		case 'P':{

			cDate_t* observer = find_date(dateVector, getAnInteger("index of date"));
			if (observer == NULL){
				break;
			}
			cout << "Date: ";
			observer->print(cout, "EU-TEXT") << endl;
			cout << "Day in week: " << observer->currentDay() << endl;
			cout << "Current month: " << observer->currentMonth() << endl;
			cout << "Current year: " << observer->currentYear() << endl;
			cout << "Day of year: " << observer->dayOfYear() << endl;
			cout << "Day of month: " << observer->dayOfMonth() << endl;
			cout << "Is leap year: " << observer->isLeapYear() << endl;
			cout << "Name of day: " << observer->nameOfDay() << endl;
			cout << "Name of month: " << observer->nameOfMonth() << endl << endl;;

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