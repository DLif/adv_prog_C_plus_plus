//#include "Person_t.h"
#include "PersonArray_t.h"

size_t Person_t::m_globID = 1;    // init global id to 1

Person_t::Person_t() : m_id(Person_t::m_globID){

	m_globID ++ ;    // advance global person id
	m_age = 0;                 // what should we put here ?
}

Person_t::Person_t(const string& name, int age) :  m_id(Person_t::m_globID), m_name(name), m_age(age)
{
	m_globID ++;    // advance global person id
}

Person_t::~Person_t(){}

int Person_t::getAge() const 
{
	return m_age;
}

size_t Person_t::getID() const 
{

	return m_id;
}

string Person_t::getName() const
{
	return m_name;
}


int main()
{
	PersonArray_t *p =new PersonArray_t(1);
	Person_t &f = Person_t();
	(*p).insert(&f);
	(*p).insert(new Person_t());
	(*p).prepend(1,new Person_t());
	Person_t *p1 = (*p).find(f);
	return 0;
}