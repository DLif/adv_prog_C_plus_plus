#include <cstdlib>
#include <string>

using namespace std;

class Person_t
{
public:

	// ~Person_t();							 default destructor will suffice
	Person_t();								 // inits unique id, sets age to 0
	Person_t(const string& name, int age);   // create a new person from given name and age
	Person_t(const Person_t& other);         // copy constructor, copies name and age

	inline string getName() const;
	inline int getAge()     const;
	inline size_t getID()   const;

	inline void setName(const string& name);
	inline void setAge(int age);

	bool operator== (const Person_t& other) const;      // compare two persons, two persons are equal iff they have same name and age
	Person_t& operator= (const Person_t& other)  ;		// assignment operator, copies name and age
	

private:

	const size_t	m_id;      // Unique ID for each Person_t
	string			m_name;
	int				m_age;
	static size_t	m_globID;  // current global id 

};

extern istream& operator>>(istream& is, Person_t& person);        // read into a person object
extern ostream& operator<<(ostream& os, const Person_t& person);  // read from a person object (representation of the object)

// inline methods implementations

inline int Person_t::getAge() const
{
	return m_age;
}

inline size_t Person_t::getID() const
{

	return m_id;
}

inline string Person_t::getName() const
{
	return m_name;
}

inline void Person_t::setAge(int age)
{
	this->m_age = age;
}

inline void Person_t::setName(const string& name)
{
	this->m_name = name;
}
