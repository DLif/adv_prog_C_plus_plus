#include "TC.h"
#include "PhoneOwner.h"
#include <vector>
#include <iostream>
#include <string>

using namespace std;

static string getAString(const string& toPrintAddition)
{
	string input;
	cout << "\nEnter a " << toPrintAddition << ": " << endl;
	cin >> input;
	// clear rest of the line 
	cin.clear();
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	return input;
}

static double getADouble(const string& toPrintAddition)
{
	double numToRead;
	cout << "\nEnter a number to " << toPrintAddition << ": " << endl;
	if (!(cin >> numToRead) || numToRead < 0){
		cout << "\nInvalid input! \nWill be set as " << 100.0 << endl;
		numToRead = 100.0;
	}
	// clear rest of the line 
	cin.clear();
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	return numToRead;
}

static PhoneClient::PhoneClientType getMobileKind()
{
	char c;
	cout << "\nEnter a M for Mobile or S for Stationary phone client: " << endl;
	if (!(cin >> c) || (c!='M' && c!='S')){
		cout << "\nInvalid input! \nWill be set as Stationary" << endl;
		c = 'S';
	}
	// clear rest of the line 
	cin.clear();
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	if (c = 'M'){
		return PhoneClient::PhoneClientType::Mobile;
	}
	else {
		return PhoneClient::PhoneClientType::Stationary;
	}
}

int main()
{
	bool cont = true;
	vector<PhoneOwner*> phoneOwnersVector;
	char c;

	TC& company = TC::getTelephoneCompany();
	cout << "\nTelephone company initialized" << endl;

	cout << "\nPlease write the first letter of the method you wish to call from the following list: " << endl;

	while (cont){
		cout << "\nPhoneOwner (make new PoneOwner) | upgrade mobilies (send notifications) | change price |  quit" << endl;
	
		cin >> c;
		// clear rest of the line 
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		switch (c)
		{
		case 'P': {
			PhoneOwner* new_owner = new PhoneOwner(&company,
				PhoneClient::createPhoneClient(getMobileKind(), getAString("Phone number")),
				getAString("Phone owner name"));

			phoneOwnersVector.push_back(new_owner);
			cout << "\nnew PhoneOwner object made: ";
			new_owner->printOwner();

			break;
		}
		case 'u': {
			company.notifyUpgradeMobile(getAString("phones newest version"));
			break;
		}
		case 'c': {
			company.notifyPriceChange(getADouble("set the new price"));
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

	for (PhoneOwner* owner : phoneOwnersVector){
		delete owner;
	}

	return 0;
}