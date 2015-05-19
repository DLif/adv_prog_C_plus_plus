#ifndef _COMPARATOR_H
#define _COMPARATOR_H

// defines a functor template
// the functor simply compares stored value with given value

template <class T>
struct Comparator
{
public:

	Comparator(const T& toCompareWith) :toCompareWith(toCompareWith) {};
	bool operator()(const T* other) const
	{
		return *other == toCompareWith;
	}

private:
	const T toCompareWith;

};



#endif