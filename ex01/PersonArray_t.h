#include "Person_t.h"

class PersonArray_t
{
public:
	~PersonArray_t();

	explicit PersonArray_t(size_t initial_size = PersonArray_t::glob_reallocation_size);  // costructs dynamic array with given minimal number of elements
																						  // may be used as a "default" constructor, e.g. no arguments

	size_t getNumElements() const;   // returns the current number of persons in array
	size_t getCapacity()    const;   // returns the current dynamic array capacity

	void insert(const Person_t* personPtr); // inserts given person to the end of array
											// if array is full in time of method call, method will first expand the array 
											// capacity by glob_reallocation_size elements


	Person_t* firstElement() const;   // returns the first person pointer in the array
									  // returns NULL if empty
	Person_t* lastElement() const;    // returns the last person pointer in the array
									  // returns NULL if empty

	Person_t* find(const Person_t& person) const; // method tries to find given person in the array
												  // if such person is found, the element is returned
												  // otherwise, returns NULL 
	Person_t* remove(const Person_t* person);     // method removes the given element
												  // if more than one found, removes only the first
												  // on success, returns the element, otherwise returns NULL

	void removeDelete(const Person_t* person);    // removes and deletes all elements with given value 

	void removeAll();       // empty array without deleting the elements themselves
	void removeDeleteAll(); // empty array and delete all the elements 

	int append(const size_t index, const Person_t* person);  // appends given person after given index
													         // if index is out of bounds, returns 0
													         // on success returns 1

	int prepend(const size_t index, const Person_t* person); // prepends given element before given index
															 // if index is out of bounds, returns 0
													         // on success, returns 1

	Person_t* elementAt(const size_t index) const;           // returns the element at given index
															 // returns NULL if index is out of bounds


private:
	const Person_t**	m_array;    // array of pointers to persons 
									// const added for safety measures, we dont want to change data members of persons accidently
									// note: destructor is a const method

	size_t      m_capacity;         // number of elements the dynamic array can currently hold without reallocating
	size_t      m_num_elements;     // number of elements currently in the array

	PersonArray_t(const PersonArray_t&);                // private  copy constructor (objects cannot be copied)
	PersonArray_t& operator= (const PersonArray_t&);    // private assignment operator (objects cannot be copied)

	void increaseCapacity();				// increase array capacity by glob_reallocation_size
											// implemeneted by allocating a new array with bigger size
											// and then moving all elements to the new array

	void pushAllStartingAt(const size_t index);    // push all the elements, starting from given index, one slot further (e.g. increase indices of said elements by one)
											 // effectively "freeing" the slot at given index

	void contractStartingAt(const size_t index);   // push all the elements after given index, to the "left" (one index down), removing the element at index

	static const size_t glob_reallocation_size;  // the number of elements that are added to the capacity when an array is full
												 // and we wish to insert a new element

};


extern ostream& operator<<(ostream& os, const PersonArray_t& array); // "To string"