#include "Person_t.h"

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

	return 0;
}