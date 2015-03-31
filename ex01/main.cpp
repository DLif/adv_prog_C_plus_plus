#include "PersonArray_t.h"
#include <iostream>
#include <sstream>

using namespace std;


static Person_t* getPerson()
{
	Person_t* person = new Person_t;
	cout << "\nEnter a name, followed by an age" << endl;
	cin >> *person;

	// clear rest of input line and errors
	cin.clear();
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	return person;

}

static size_t getIndex()
{
	size_t index;
	cout << "\nEnter an index (will be interpreted as size_t)" << endl;
	if (!(cin >> index))
	{
		cout << "\nInvalid input! \nWill be set as 0" << endl;
		index = 0;
	}
	// clear errors and the rest of the line
	cin.clear();
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	return index;
}

static size_t getSize()
{
	size_t size;
	cout << "\nEnter a size for the array (will be interpreted as size_t)" << endl;
	if (!(cin >> size))
	{
		cout << "\nInvalid input! \nWill be set as 0" << endl;
		size = 0;
	}
	// clear errors and the rest of the line
	cin.clear();
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	return size;
}


static PersonArray_t* getArray()
{

	char c;
	PersonArray_t* arr;
	cout << "enter D for default initial size capacity or C to insert custom initial size" << endl;
	cin >> c;
	// ignore the rest of the line
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	switch (c)
	{
	case 'D':
		arr = new PersonArray_t();
		break;
	case 'C':
		arr = new PersonArray_t(getSize());
		break;
	default:
		cout << "Invalid input, program will exit" << endl;
		arr = NULL;

	}

	// clear errors and the rest of the line
	
	return arr;
}

int main()
{
	PersonArray_t* arr;
	Person_t* ptr, *res;
	bool cont = true;
	size_t prevCount = 0;
	size_t index;
	char c;

	arr = getArray();
	if (arr == NULL)
	{
		return 0;
	}

	cout << "\nPlease write the first letter of the method you wish to call from the following list: " << endl;
	
	while (cont)
	{

		cout << "\nnum elements | capacity | IsEmpty |insert | first | last | Find | remove |\nRemove all | delete-remove | Delete-remove all | append | prepend | Print | quit" << endl;

		cin >> c;
		// clear rest of the line 
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		switch (c)
		{
		case 'n':
			cout << "\nNumber of elements in array: " << arr->getNumElements() << endl;
			break;
		case 'c':
			cout << "\nArray capacity: " << arr->getCapacity() << endl;
			break;
		case 'i':
			ptr = getPerson();
			arr->insert(ptr);
			break;
		case 'f':
			cout << "\nFirst element:" << endl;
			ptr = arr->firstElement();
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
			cout << "\nLast element:" << endl;
			ptr = arr->lastElement();
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

			cout << "\nFind method" << endl;
			ptr = getPerson();
			res = arr->find(*ptr);

			if (res == NULL)
			{
				cout << "\nNot found" << endl;
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
			cout << "\nRemove by value (no delete) \n";
			ptr = getPerson();
			res = arr->remove(*ptr);
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
				delete res;
			}
			delete ptr;

			break;
		case 'R':
			prevCount = arr->getNumElements();
			cout << "\nRemoving all ... " << endl;
			arr->removeAll();
			cout << prevCount - arr->getNumElements() << " elements removed" << endl;
			break;

		case 'd':

			cout << "\nRemove + delete by value \n";
			prevCount = arr->getNumElements();
			ptr = getPerson();
			cout << "\nremoving all occurances (with deleting) ..." << endl;
			arr->removeDelete(*ptr);
			cout << prevCount - arr->getNumElements() << " elements removed" << endl;
			delete ptr;
			break;
		case 'D':

			prevCount = arr->getNumElements();
			cout << "\nRemoving all (with deleting) ..." << endl;
			arr->removeDeleteAll();
			cout << prevCount - arr->getNumElements() << " elements removed" << endl;
			break;
		case 'a':
			cout << "\nAppend \n";
			index = getIndex();
			ptr = getPerson();
			if (!arr->append(index, ptr))
			{
				cout << "\nindex is out of bounds!" << endl;
			}
			else
			{
				cout << "\nInserting " << ptr->getName() << " at index " << index + 1 << endl;

			}

			break;
		case 'p':

			cout << "\nPrepend \n";
			index = getIndex();
			ptr = getPerson();

			if (!arr->prepend(index, ptr))
			{
				cout << "\nindex is out of bounds!" << endl;
			}
			else
			{
				cout << "\nInserting " << ptr->getName() << " at index " << index << endl;
			}

			break;
		case 'P':
			cout << "\n" << *arr;
			break;
		case 'q':
			cont = false;
			break;
		case 'I':
			cout << "\nisEmpty method" << endl;
			cout << (arr->isEmpty() ? "Array is empty" : "Array is not empty!") << endl;
			break;
		default:
			cout << "\nInvalid input" << endl;
			break;


		}

	}
	// delete all elements left in array
	arr->removeDeleteAll();
	delete arr;

}