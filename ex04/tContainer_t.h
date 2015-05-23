#ifndef _T_CONTAINER_H
#define _T_CONTAINER_H

#include <iostream>
#include <algorithm>
#include "Comparator.h"
#include <typeinfo>
#include <iterator>
#include <iostream>

using namespace std;

// 
// NOTE: _TEMPLATE_TEMPLATE_ 
// when defined the template-template version is active
// otherwise, the non-template version is active.
//

#define _TEMPLATE_TEMPLATE_


#ifdef _TEMPLATE_TEMPLATE_
#define _TEMPLATE_CLASS_DEFINITION_ template <class T, template <typename, typename> class Container>
#define _CONTAINER_TYPE_ Container<T*, allocator<T*>>

#else
#define _TEMPLATE_CLASS_DEFINITION_ template <class T, class Container>
#define _CONTAINER_TYPE_ Container
#endif

_TEMPLATE_CLASS_DEFINITION_
class tContainer_t
{
	friend ostream& operator<< <T, Container>(ostream&, const tContainer_t&);
	
public:


	tContainer_t(){};   // default implementation will suffice
	//~tContainer_t();  // default implementation will suffice 

	inline bool isEmpty() const;		    // true iff container contains no elements

	inline size_t size() const;				// number of elements in container

	inline void push_back(const T* val);    // push to the end of the container
											// same semantics as the wrapped container's push_back method

	inline T* front() const;				// return the first element
											// same semnatics as the wrapped container's front method

	inline T* back() const;					// same as above, but returns the last element

	inline T* find(const T& val) const;	   // find element by given value
										   // returns the first element found
										   // if no such element exists, returns 0

	inline T* remove(const T& val);		   // remove element by given value
										   // removes only the first element found
										   // if no such element exists, returns 0

	inline T* removeDelete(const T& val);  // like method above, but also deletes the element
										   // if no such element was found, returns 0, otherwise returns the deleted element

	inline void removeAll();               // remove all elements without deleting them
	inline void removeDeleteAll();         // remove and delete all elements

	inline T* operator[](size_t index) const; // retrieve subscript operator
	inline T*& operator[](size_t index);      // assign subscript operator
									          // both versions thrown an exception if index is out of bounds


private:
	typedef typename _CONTAINER_TYPE_::iterator iter_t;
	typedef typename _CONTAINER_TYPE_::const_iterator const_iter_t;

	T* const& at(size_t index) const;     // get a constant reference to element at given index
										  // if index if out of bounds an exception will be thrown

	_CONTAINER_TYPE_ container;

	// non copyable 
	tContainer_t(const tContainer_t& other);
	tContainer_t& operator=(const tContainer_t& other);

};

_TEMPLATE_CLASS_DEFINITION_
inline T* tContainer_t<T, Container>::back() const
{
	return container.back();
}

_TEMPLATE_CLASS_DEFINITION_
inline T* tContainer_t<T, Container>::front() const
{
	return container.front();
}

_TEMPLATE_CLASS_DEFINITION_
inline bool tContainer_t<T, Container>::isEmpty() const
{
	return container.empty();
}

_TEMPLATE_CLASS_DEFINITION_
inline size_t tContainer_t<T, Container>::size() const
{
	return container.size();
}

_TEMPLATE_CLASS_DEFINITION_
inline void tContainer_t<T, Container>::push_back(const T* val)
{
	container.push_back((T*)val);
}


_TEMPLATE_CLASS_DEFINITION_
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

_TEMPLATE_CLASS_DEFINITION_
inline T* tContainer_t<T, Container>::remove(const T& val)
{
	tContainer_t<T, Container>::const_iter_t iter = find_if(container.begin(), container.end(), Comparator<T>(val));
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

_TEMPLATE_CLASS_DEFINITION_
inline T* tContainer_t<T, Container>::removeDelete(const T& val)
{
	T* result = remove(val);
	// Note that if no such element was found, result == 0 and delete won't do anything
	delete result;
	return result;
	
}

_TEMPLATE_CLASS_DEFINITION_
inline void tContainer_t<T, Container>::removeAll()
{
	// simply remove all elements
	container.clear(); 
}

_TEMPLATE_CLASS_DEFINITION_
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


_TEMPLATE_CLASS_DEFINITION_
inline T* const& tContainer_t<T, Container>::at(size_t index) const
{
	if (index >= size())
	{
		throw out_of_range("Error: index is out of bounds");
	}

	if (typeid(container) == typeid(vector<T*>))
	{
		// use the subscript operator only on a const vector<T*> type
		const vector<T*>& vec = *((const vector<T*>*)&container);

		// const subscript operator also returns a (const) reference
		return vec[index];
	}

	// list<T*>
	
	// move the iterator to the right poistion
	tContainer_t<T, Container>::const_iter_t iter = container.begin();
	advance(iter, index);
	return *iter;
}

_TEMPLATE_CLASS_DEFINITION_
inline T* tContainer_t<T, Container>::operator[](size_t index) const
{
	// pointer is copied
	return at(index);
}

_TEMPLATE_CLASS_DEFINITION_
inline T*& tContainer_t<T, Container>::operator[](size_t index)
{
	// allow modifications
	return (T*&)at(index);
}


_TEMPLATE_CLASS_DEFINITION_
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