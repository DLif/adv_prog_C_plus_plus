//#include "tContainer_t.h"
#include <iostream>
#include "tContainer_t_v2.h"

#include <vector>
using namespace std;

void main()
{
	
	//tContainer_t<int, vector<int*>> vec;
	tContainer_t<int, vector> vec, vec2;

	int a, b, c;

	a = 5;
	b = 6;
	c = 8;

	vec.push_back(&a);
	vec.push_back(&b);
	vec.push_back(&c);

	cout << *vec.back() << endl;
	cout << *vec.front() << endl;

	int* p = vec.find(6);
	if (&b == p)
	{
		cout << " True" << endl; 
		cout << *p << endl;
	}

	p = vec.remove(6);
	if (&b == p)
	{
		cout << " True" << endl;
		cout << *p << endl;
	}

	cout << vec.isEmpty() << endl;
	cout << vec.size() << endl;
	vec.push_back(&b);
	vec.push_back(&b);
	
	cout << *vec[1] << endl;
	
	vec[2] = &a;
	cout << *vec[2] << endl;
	try
	{
		cout << *vec[15] << endl;
	}
	catch (...)
	{
		cout << "hello";
	}

	cout << vec.size() << endl;

	

	while (1){}


}