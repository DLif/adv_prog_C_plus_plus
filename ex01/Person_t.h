#include <cstdlib>
#include <string>

using namespace std;

class Person_t
{
public:

	// ~Person_t();							 default destructor will suffice
	Person_t();								 // empty constructor, only inits unique id
	Person_t(const string& name, int age);   // create a new person from given name and age

	string getName() const;
	int getAge()     const;
	size_t getID()   const;

	void setName(string& name);
	void setAge(int age);

	bool operator== (const Person_t& other) const; // compare two persons
	// two persons are equal if they have the same id 
	// the alternative: comparing by age and name, is not sufficient in our opinion
	// since two different people may have the same name and age

private:

	const size_t	m_id;      // Unique ID for each Person_t
	string			m_name;
	int				m_age;
	static size_t	m_globID;  // current global id 

	Person_t(const Person_t& other);             // private copy constructor, no copying
	Person_t& operator= (const Person_t& other); // no copying via assignments as well

};

extern istream& operator>>(istream& is, Person_t& person);
extern ostream& operator<<(ostream& os, const Person_t& person);