#include "Person_t.h"
#include <iostream>

size_t Person_t::m_globID = 1;    // init global id to 1

Person_t::Person_t() : m_id(Person_t::m_globID), m_age(0){

	m_globID++;      // advance global person id, default age is 0
}

Person_t::Person_t(const string& name, int age) : m_id(Person_t::m_globID), m_name(name), m_age(age)
{
	m_globID++;     // advance global person id
}


bool Person_t::operator==(const Person_t& other) const
{
	return this->m_age == other.m_age && this->m_name == other.m_name;
}

Person_t& Person_t::operator=(const Person_t& other)
{
	if (this != &other)
	{
		// different person, copy name and age
		this->m_age = other.m_age;
		this->m_name = other.m_name;
	}
	return *this;
}

// copy constructor, copy name and age
Person_t::Person_t(const Person_t& other) : m_id(Person_t::m_globID), m_name(other.m_name), m_age(other.m_age)
{
	m_globID++;     // advance global person id
}

// read into a person object from an istream object
istream& operator>>(istream& is, Person_t& person)
{
	string name;
	int age;

	is >> name;
	person.setName(name);
	if (!(is >> age) || age < 0)
	{
		cout << "\nInvalid age! age will be set to 0" << endl;
		age = 0;
	}

	person.setAge(age);
	
	return is;

}

// output an inner representation of person into os
ostream& operator<<(ostream& os, const Person_t& person)
{
	os << "ID:        " << person.getID() << endl;
	os << "Name:      " << person.getName() << endl;
	os << "Age:       " << person.getAge() << endl;

	return os;
}