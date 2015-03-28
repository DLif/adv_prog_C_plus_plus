#include "Person_t.h"

size_t Person_t::m_globID = 1;    // init global id to 1

Person_t::Person_t() : m_id(Person_t::m_globID){

	m_globID ++ ;    // advance global person id
	m_age = 0;       // set age to 0
}

Person_t::Person_t(const string& name, int age) :  m_id(Person_t::m_globID), m_name(name), m_age(age)
{
	m_globID ++;     // advance global person id
}


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

bool Person_t::operator==(const Person_t& other) const
{
	return this->m_id == other.m_id;
}
