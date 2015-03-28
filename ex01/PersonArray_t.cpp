#include "PersonArray_t.h"

const size_t PersonArray_t::glob_reallocation_size = 16; // reallocation size is 16 elements


// create a new array
// constructer with default initial size same as glob_reallocation_size (16)
PersonArray_t::PersonArray_t(size_t initial_size) : m_num_elements(0), m_capacity(initial_size)
{
	// init array with initial given size
	m_array = new const Person_t*[initial_size];
}

PersonArray_t::~PersonArray_t()
{
	// delete the array without deleting the elements themselves
	delete [] m_array;
}

size_t PersonArray_t::getCapacity() const 
{
	return m_capacity;
}

Person_t* PersonArray_t::firstElement() const
{
	if(m_num_elements == 0)
	{
		// empty array
		return NULL;
	}

	return (Person_t*)this->m_array[0];
}

Person_t* PersonArray_t::lastElement() const
{
	if(m_num_elements == 0)
	{
		// empty array
		return NULL;
	}
	return (Person_t*)(m_array[m_num_elements-1]);

}
size_t PersonArray_t::getNumElements() const
{
	return m_num_elements;
}

void PersonArray_t::insert(const Person_t* personPtr)
{
	// append to end (after last element)
	PersonArray_t::append(m_num_elements - 1, personPtr);
}

void PersonArray_t::increaseCapacity()
{
	
	m_capacity += glob_reallocation_size;

	// allocate a new array
	const Person_t ** newArr = new const Person_t*[m_capacity];

	// move all elements to new array
	for(size_t i = 0; i < m_num_elements; ++i)
	{
		newArr[i] = m_array[i];
	}

	// delete previous array and set new
	delete [] m_array;
	m_array = newArr;
}

// find returns NULL if no such person was found
Person_t* PersonArray_t::find(const Person_t& person) const
{

	for(size_t i = 0; i < this->m_num_elements; ++i)
	{
		if(person == *(this->m_array[i]))
		{
			return (Person_t*)this->m_array[i];
		}
	}
	return NULL;
}

void PersonArray_t::removeAll()
{
	m_num_elements = 0; //this means that any pointers left in the array would be treated as junk
						//we would never access them again and some of them will be overriden as we insert new pointers
}

void PersonArray_t::removeDeleteAll()
{
	//iterate over all objects in array and call their destructor
	for (size_t i = 0 ; i < m_num_elements ; i++){
		delete m_array[i]; //m_array[i] is a pointer to the i-th Person
	}
	
	removeAll(); //now that all the objects are destroyed, we can remove the array without "deleting" any objects.
}


// method appends given person AFTER given index
// returns 0 on failure (if given index is out of bounds)
// returns 1 on success
int PersonArray_t::append(size_t index, const Person_t* person){

	if ( index >= m_num_elements) { // check if index in bounds
		return 0;
	}

	if (m_num_elements == m_capacity) {
		// if the array is completely full, increase capacity
		increaseCapacity();
	}

	if(index == m_num_elements - 1){

		//adding an element after the tail is a special case, no elements need to be pushed
		m_array[m_num_elements] = person; 
	}
	else
	{
		// need to push all elements starting at index+1
		pushAllStartingAt(index + 1);
		//now insert the element. becuase we called the makeSpaceAtIndex function the insertion at the given index won't reomove any other element from the array.
		m_array[index + 1] = person;
	}
	m_num_elements++;
	return 1;
}

void PersonArray_t::pushAllStartingAt(size_t index){

	// simply push all elements by one slot
	for (size_t i = m_num_elements-1; i>= index ; i--){ 
		m_array[i+1] = m_array[i];
	}
}

// method appends a new element BEFORE given index
// returns 0 on failure (if given index is out of bounds)
// returns 1 on success
int PersonArray_t::prepend(size_t index, const Person_t* person){

	// check if index out of bounds
	if(index >= m_num_elements)
	{
		return 0;
	}

	if(index == 0)
	{
		// special case
		if (m_num_elements == m_capacity) {
			// if the array is completely full, increase capacity
			increaseCapacity();
		}
		// need to push all elements by one slot
		pushAllStartingAt(0);
		// insert in first place
		m_array[0] = person;
		// increase num elements
		m_num_elements ++ ;
	}

	else { 
		// same as appending AFTER index - 1
		append(index - 1, person);
	}

	return 1;
}


int main()
{
	PersonArray_t arr;
	Person_t person;
	arr.insert(&person);
	arr.insert(new Person_t());
	arr.prepend(0, new Person_t());
	Person_t* p1 = arr.find(person);
	return 0;
}