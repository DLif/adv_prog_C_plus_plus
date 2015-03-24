#include <cstdlib>
#include <string>

using namespace std;


class Person_t
{
public:

	~Person_t();           // destructor
	Person_t();            // empty constructor, only inits unique id
	Person_t(const string &name, int age);   
	
	string getName() const;
	int getAge() const ;
	size_t getID() const ;


private:

	const size_t	m_id;      // Unique ID for each Person_t
	string			m_name;
	int				m_age;
	static size_t	m_globID;  // current global id 

	Person_t(const Person_t& other); // private copy constructor, no copy passing to methods
	Person_t& operator= (const Person_t& other); // no copying via assignments

};
	