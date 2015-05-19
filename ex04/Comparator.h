#ifndef _COMPARATOR_H
#define _COMPARATOR_H


template <class T>
class Comparator
{

public:

	Comparator(const T& toCompareWith) :toCompareWith(toCompareWith) {};

	bool operator()(const T* other) const
	{
		return *other == toCompareWith;
	}

private:
	const T& toCompareWith;

};



#endif