#ifndef _T_CONTAINER_H
#define _T_CONTAINER_H

#include <iostream>
#include <algorithm>
#include "Comparator.h"
#include <typeinfo>
#include <iterator>
#include <iostream>

// declarations
using namespace std;


template <class T, class Container>
class tContainer_t
{
	friend ostream& operator<< <T, Container>(ostream&, const tContainer_t&);
	
public:


	tContainer_t(){};   // default implementation will suffice
	//~tContainer_t();  // default implementation will suffice [virtual?]

	inline bool isEmpty() const;		    // true iff container contains no elements
	inline size_t size() const;				// number of elements in container
	inline void push_back(const T* val);    // push to the end of the container
											// same semantics as the wrapped container's push_back method
	inline T* front() const;				// return the first element
											// same semnatics as the wrapped container's front method
	inline T* back() const;					// same as above, but returns the last element

	inline T* find(const T& val) const;	   // find element by given value
										   // if no such element exists, returns 0

	inline T* remove(const T& val);		   // remove element by given value
										   // removes only the first element found
										   // if no such element exists, returns 0

	inline bool removeDelete(const T& val);// like method above, but also deletes the element
										   // if no such element was found, returns false, otherwise returns true

	inline void removeAll();               // remove all elements without deleting them
	inline void removeDeleteAll();         // remove and delete all elements

	inline T* operator[](size_t index) const; // retrieve subscript operator
	inline T*& operator[](size_t index);      // assign subscript operator
									          // both versions thrown an exception if index is out of bounds

protected:
	typedef typename Container::iterator iter_t;
	typedef typename Container::const_iterator const_iter_t;

	T* const& at(size_t index) const;     // get a constant reference to element at given index
										  // if index if out of bounds an exception will be thrown

private:
	Container container;

	// non copyable 
	tContainer_t(const tContainer_t& other);
	tContainer_t& operator=(const tContainer_t& other);

};

template <class T, class Container>
inline T* tContainer_t<T, Container>::back() const
{
	return container.back();
}

template <class T, class Container>
inline T* tContainer_t<T, Container>::front() const
{
	return container.front();
}

template <class T, class Container>
inline bool tContainer_t<T, Container>::isEmpty() const
{
	return container.empty();
}

template <class T, class Container>
inline size_t tContainer_t<T, Container>::size() const
{
	return container.size();
}

template <class T, class Container>
inline void tContainer_t<T, Container>::push_back(const T* val)
{
	container.push_back((T*)val);
}


template <class T, class Container>
inline T* tContainer_t<T, Container>::find(const T& val) const
{
	tContainer_t<T, Container>::const_iter_t iter = find_if(container.begin(), container.end(), Comparator<T>(val));
	if (iter == container.end())
	{
		// element with given value not found
		return 0;
	}
	
	return *iter;
}

template <class T, class Container>
inline T* tContainer_t<T, Container>::remove(const T& val)
{
	tContainer_t<T, Container>::iter_t iter = find_if(container.begin(), container.end(), Comparator<T>(val));
	if (iter == container.end())
	{
		// element with given value not found
		return 0;
	}
	// remove the element and return the element that was removed
	T* result = *iter;
	container.erase(iter);
	return result;
}

template <class T, class Container>
inline bool tContainer_t<T, Container>::removeDelete(const T& val)
{
	T* result = remove(val);
	if (result == 0)
		// element does not exist
		return false;

	delete result;
	return true;
}

template <class T, class Container>
inline void tContainer_t<T, Container>::removeAll()
{
	// simply remove all elements
	container.clear(); 
}

template <class T, class Container>
inline void tContainer_t<T, Container>::removeDeleteAll()
{
	tContainer_t::iter_t iter = container.begin();
	while (iter != container.end())
	{
		delete *iter;
		++iter;
	}

	removeAll();
}


template <class T, class Container>
inline T* const& tContainer_t<T, Container>::at(size_t index) const
{
	if (index >= size())
	{
		throw out_of_range("Error: index is out of bounds");
	}

	if (typeid(container) == typeid(vector<T>))
	{
		// use the subscript operator only on a vector<T*> type
		const vector<T*>& vec = *((const vector<T*>*)&container);

		// const subscript operator also returns a (const) reference
		return vec[index];
	}

	// list<T>
	
	// move the iterator to the right poistion
	tContainer_t<T, Container>::const_iter_t iter = container.begin();
	advance(iter, index);
	return *iter;
}

template <class T, class Container>
inline T* tContainer_t<T, Container>::operator[](size_t index) const
{
	// pointer is copied
	return at(index);
}

template <class T, class Container>
inline T*& tContainer_t<T, Container>::operator[](size_t index)
{
	// allow modifications
	return (T*&)at(index);
}


template <class T, class Container>
ostream& operator << (ostream& os, const tContainer_t<T, Container>& tContainer)
{

	tContainer_t<T, Container>::const_iter_t iter = tContainer.container.begin();
	if (tContainer.isEmpty())
	{
		os << "tContainer is empty" << endl;
		return os;
	}
	os << "tContainer size: " << tContainer.size() << endl << endl;
	while (iter != tContainer.container.end())
	{
		os << "[ "<< *(*iter) << " ]";
		++iter;
	}
	os << endl;
	return os;
}

#endif