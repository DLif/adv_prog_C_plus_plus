#include "PersonArray_t.h"

const size_t PersonArray_t::glob_reallocation_size = 16; // reallocation size is 16 elements


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

	return (Person_t*)this->m_array[0];//why casting needed?
}

Person_t* PersonArray_t::lastElement() const
{
	if(m_num_elements == 0)
	{
		// empty array
		return NULL;
	}
	return (Person_t*)(m_array[m_num_elements-1]);//why casting needed?

}
size_t PersonArray_t::getNumElements() const
{
	return m_num_elements;
}

void PersonArray_t::insert(const Person_t* personPtr)
{
	// append to end
	PersonArray_t::append(m_num_elements, personPtr);
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

	// delete previous array
	delete [] m_array;
	m_array = newArr;
}

// find returns NULL if no such person was found
Person_t* PersonArray_t::find(const Person_t& person) const
{

	for(size_t i = 0; i < this->m_num_elements; ++i)
	{
		if(&person == this->m_array[i])
		{
			return (Person_t*)this->m_array[i];
		}
	}
	return NULL;
}

void PersonArray_t::removeAll()
{
	m_num_elements = 0; //this means that any pointers left in the array would be treated as junk - we would never access them again and some of them will be overriden as we insert new pointers
}

void PersonArray_t::removeDeleteAll()
{
	//move on all objects in array and call their destructor
	for (unsigned int i=0 ; i < m_num_elements ; i++){
		delete m_array[i];//m_array[i] is a pointer to the i-th Person
	}
	
	removeAll(); //now that all the objects are destroyed, we can remove the array without "deleting" any objects.
}

int PersonArray_t::append(int index, const Person_t* person){

	if (index<0 || ((unsigned int)index)>m_num_elements) { //check index validity
		return 0;
	}

	else if(index == m_num_elements){//adding an element in the tail is a special case
		if (m_num_elements == m_capacity) {//if the array is completely full, increase capacity
			increaseCapacity();
		}
		m_array[m_num_elements]= person;//insert new element
		m_num_elements++;
		return 1;
	}

	//all cases with valid index that isn't the tail will execute this:

	make_space_at_index(index);
	//now insert the element. becuase we called the make_space_at_index function the insertion at the given index won't reomove any element other from the array.
	m_array[index]=person;
	return 1;
}

void PersonArray_t::make_space_at_index(int index){
	insert(m_array[m_num_elements-1]);//copy the last element in the array to the tail (one of the copies will be overriden in the next step)
	//we move each pinter with index j to index j+1, when index<=j<old_m_num_elemnts-1. (old_m_num_elemnts == m_num_elemnts-1 because we inserted the last element twice in the tail).
	for (int i=m_num_elements-2; i>=index ;i--){ 
		m_array[i+1] = m_array[i];
	}
}

int PersonArray_t::prepend(int index, const Person_t* person){

	//in all cases prepend(i,person) == append(i-1,person) , only allowed indexes are bit different
	if (index<1 || ((unsigned)index)>=m_num_elements) { //check index validity
		return 0;
	}
	else return append(index-1,person);
}