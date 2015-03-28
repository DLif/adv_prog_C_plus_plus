#include "PersonArray_t.h"
#include <iostream>
#include <sstream>

using namespace std;


static Person_t* getPerson()
{
	Person_t* person = new Person_t;
	cout << "\nEnter a name, followed by an age" << endl;
	cin >> *person;
	return person;

}

static size_t getIndex()
{
	size_t index;
	cout << "\nEnter an index (will be interpreted as size_t)" << endl;
	cin >> index;
	return index;
}

int main()
{
	PersonArray_t arr;
	Person_t* ptr, *res;
	bool cont = true;
	size_t prevCount = 0;
	size_t index;

	while (cont)
	{

		cout << "\nnum elements | capacity | insert | first | last | Find | remove | Remove all |\n delete-remove | Delete-remove all | append | prepend" << endl;

		char c;
		cin >> c;
		switch (c)
		{
		case 'n': 
			cout << "\nNumber of elements in array: " << arr.getNumElements() << endl;
			break;
		case 'c':
			cout << "\nArray capacity: " << arr.getCapacity() << endl;
			break;
		case 'i':
			ptr = getPerson();
			arr.insert(ptr);
			break;
		case 'f':

			ptr = arr.firstElement();
			if (ptr == NULL)
			{
				cout << "\nArray is empty" << endl;
			}
			else
			{
				cout << endl << *ptr << endl;
			}
			break;
		case 'l':
			ptr = arr.lastElement();
			if (ptr == NULL)
			{
				cout << "\nArray is empty" << endl;
			}
			else
			{
				cout << endl << *ptr << endl;
			}
			break;
		case 'F':
			ptr = getPerson();
			res = arr.find(*ptr);
			
			if (res == NULL)
			{
				cout <<  "\nNot found" << endl;
			}
			else
			{
				stringstream ss;
				ss << (*res).getID();
				string id = ss.str();
				cout << "\nFound, ID: " << id << endl;
			}

			delete ptr;
			break;
		case 'r':
			ptr = getPerson();
			res = arr.remove(ptr);
			if (res == NULL)
			{
				cout << "\nNot found" << endl;
			}
			else
			{
				stringstream ss;
				ss << (*res).getID();
				string id = ss.str();
				cout << "\nFound and removed (first occurance), ID: " << id << endl;
			}
			delete ptr;

			break;
		case 'R':
			prevCount = arr.getNumElements();
			cout << "\nRemoving all ... " << endl;
			arr.removeAll();
			cout << prevCount - arr.getNumElements() << " elements removed" << endl;
			break;

		case 'd':
			prevCount = arr.getNumElements();
			ptr = getPerson();
			cout << "\n removing all occurances (with deleting) ..." << endl;
			arr.removeDelete(ptr);
			cout << prevCount - arr.getNumElements() << " elements removed" << endl;
			delete ptr;
			break;
		case 'D':
			prevCount = arr.getNumElements();
			cout << "\n Removing all (with deleting) ..." << endl;
			arr.removeDeleteAll();
			cout << prevCount - arr.getNumElements() << " elements removed" << endl;
			break;
		case 'a':
			index = getIndex();
			ptr = getPerson();
			if (!arr.append(index, ptr))
			{
				cout << "\n index is out of bounds!" << endl;
			}
			else
			{
				cout << "\n Inserting " << ptr->getName() << "at index " << index + 1 << endl;

			}
			delete ptr;
			break;
		case 'p':
			index = getIndex();
			ptr = getPerson();
			
			if (!arr.prepend(index, ptr))
			{
				cout << "\n index is out of bounds!" << endl;
			}
			else
			{
				cout << "\n Inserting " << ptr->getName() << "at index " << index << endl;
			}
			delete ptr;
			break;
		default:
			cout << "\n Invalid char" << endl;
			break;
		}
		


	}



}