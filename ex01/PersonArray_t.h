#include "Person_t.h"

class PersonArray_t
{
public:
	~PersonArray_t();
	//PersonArray_t();                         // default constructor, initial capacity is glob_reallocation_size
	explicit PersonArray_t(size_t initial_size = glob_reallocation_size);  // costructs dynamic array with given minimal number of elements

	size_t getNumElements() const;   // returns the current number of persons in array
	size_t getCapacity() const;      // returns the current dynamic array capacity
	
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
	

	void removeAll();       // empty array without deleting the elements themselves
	void removeDeleteAll(); // empty array and delete all the elements 

	int append(int index, const Person_t* person);  // appends given person after given index
											  // if no such index exists, returns 0
											  // on success returns 1
	int prepend(int index, const Person_t* person); // prepends given element before given index
											  // if no such index exists, returns 0
											  // on success, returns 1


private:
	const Person_t**	m_array;       // array of persons (const for safety measures, we dont want to change members accidently)
	size_t      m_capacity;    // number of elements the dynamic array can currently hold
	size_t      m_num_elements; // number of elements currently in the array

	PersonArray_t(const PersonArray_t&);      // hidden copy constructor (objects cannot be copied)
	PersonArray_t& operator= (const PersonArray_t&);    // hidden assignment operator (objects cannot be copied)

	void increaseCapacity();  // increase array capacity by glob_reallocation_size
	void make_space_at_index(int index);//we move all the elements between the given index and the tail one index forward,"freeing the array at the given index.
									
	static const size_t glob_reallocation_size;  // the number of elements that are added to the capacity when an array is full

};