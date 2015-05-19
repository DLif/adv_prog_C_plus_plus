#include "tContainer_t.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <list>

using namespace std;


static size_t getIndex()
{
	size_t index;
	cout << "\nEnter an index, as size_t" << endl;
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

static int* getInt()
{
	int* val = new int();
	cout << "Enter an int" << endl;
	if (!(cin >> *val))
	{
		cout << "\nInvalid input! \nWill be set as 0" << endl;
		*val = 0;
	}
	// clear errors and the rest of the line
	cin.clear();
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	return val;
}

// returns true if user selected a vector data structure, false if list
static bool isVector()
{
	cout << "Enter container type: V(ector) or L(ist)" << endl;
	char c;
	cin >> c;
	// ignore the rest of the line
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	switch (c)
	{
	case 'v':
	case 'V':
		return true;
	case 'L':
	case 'l':
		return false;
		break;
	default:
		cout << "Invalid input, program will exit" << endl;
		exit(0);

	}
}

template <template <typename, typename> class Container>
static void process()
{

	tContainer_t<int, Container<int*, allocator<int*>>> container;
	bool cont = true;
	size_t prevCount = 0;
	size_t index;
	int* val = 0, *res = 0;
	char c;

	cout << "\nPlease write the first letter of the method you wish to call from the following list: " << endl;

	while (cont)
	{

		cout << "\nnum elements | IsEmpty | insert at end | first | last | operator[] fetch | Operator[] assign | Find | remove |\nRemove all | delete-remove | Delete-remove all | Print | quit" << endl;

		cin >> c;
		// clear rest of the line 
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		switch (c)
		{
		case 'n':
			cout << "\nNumber of elements in array: " << container.size() << endl;
			break;

		case 'i':
			val = getInt();
			container.push_back(val);
			break;
		case 'f':
			cout << "\nFirst element:" << endl;
			if (container.isEmpty())
			{
				cout << "\nContainer is empty" << endl;
			}
			else
			{
				cout << endl << *container.front() << endl;
			}
			break;
		case 'l':
			cout << "\nLast element:" << endl;
			if (container.isEmpty())
			{
				cout << "\nContainer is empty" << endl;
			}
			else
			{
				cout << endl << *container.back() << endl;
			}
			break;
		case 'F':

			cout << "\nFind method" << endl;
			val = getInt();
			res = container.find(*val);
			delete val;

			if (res == 0)
			{
				cout << "\nNot found" << endl;
			}
			else
			{
				cout << "\nFound " << *res << endl;
			}

			break;
		case 'r':
			cout << "\nRemove by value (no delete)  \n";
			val = getInt();
			cout << "\nremoving first occurance of value ..." << endl;
			res = container.remove(*val);
			delete val;

			if (res == 0)
			{
				cout << "\nNot found" << endl;
			}
			else
			{
				cout << "\nRemoved " << *res << endl;
			}
			delete res;


			break;
		case 'R':
			prevCount = container.size();
			cout << "\nRemoving all ... " << endl;
			container.removeAll();
			cout << prevCount - container.size() << " elements removed" << endl;
			break;

		case 'd':

			cout << "\nRemove + delete by value \n";
			prevCount = container.size();
			val = getInt();
			cout << "\nremoving first occurance of value (with delete) ..." << endl;
			container.removeDelete(*val);
			delete val;
			cout << prevCount - container.size() << " elements removed" << endl;

			break;
		case 'D':

			prevCount = container.size();
			cout << "\nRemoving all (with deleting) ..." << endl;
			container.removeDeleteAll();
			cout << prevCount - container.size() << " elements removed" << endl;
			break;

		case 'P':
			cout << "\n" << container;
			break;
		case 'q':
			cont = false;
			break;
		case 'I':
			cout << "\nisEmpty method" << endl;
			cout << (container.isEmpty() ? "Container is empty" : "Container is not empty!") << endl;
			break;
		case 'o':
			cout << "\nsubscript operator [] fetch" << endl;

			try
			{
				index = getIndex();

				val = (*((const tContainer_t<int, vector<int*>>*)(&container)))[index];
				cout << "container[" << index << "] is a ptr to " << *val << endl;

			}
			catch (exception& ex)
			{
				cout << ex.what() << endl;
			}
			break;

		case 'O':
			cout << "\nsubscript operator [] assign" << endl;

			try
			{
				index = getIndex();
				val = getInt();
				container[index] = val;

			}
			catch (exception& ex)
			{
				cout << ex.what() << endl;
				delete val;
			}
			break;


		default:
			cout << "\nInvalid input" << endl;
			break;


		}

	}
	// delete all elements left in container
	container.removeDeleteAll();
}

int main()
{
	if (isVector())
	{
		cout << "Selected data structure: vector, element type: int*" << endl;
		process<vector>();
	}
	//else
	//{
	//	cout << "Selected data structure: list, element type: int*" << endl; 
	//	process<list>();
	//}

}