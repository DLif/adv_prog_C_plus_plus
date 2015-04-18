#include <string>
using namespace std;

template <class T> class Meeting_t {

	friend ostream& operator<<(ostream& os, const Meeting_t<T>& meeting);
	friend istream& operator>>(istream& is, Meeting_t<T>& meeting);

public:

	virtual ~Meeting_t();
	Meeting_t(const string& meetingTopic, const T& startingTime, const T& finishTime);
	Meeting_t(const Meeting_t& other);
	Meeting();

	virtual Meeting_t& operator=(const Meeting_t& other) const;
	inline bool operator==(const Meeting_t& other) const;

	inline T getMeetingDuration() const;
	inline T getStartingTime() const;
	inline T getFinishTime() const;
	inline string getMeetingTopic() const;


private:
	T startingTime;
	T finishTime;
	string meetingTopic;

};

template <class T>
inline T Meeting_t<T>::getMeetingDuration() const
{
	return finishTime - startingTime;
}

template <class T>
inline T Meeting_t<T>::getStartingTime() const
{
	return startingTime;
}

template <class T>
inline T Meeting_t<T>::getFinishTime() const
{
	return finishTime;
}

template <class T>
inline string Meeting_t<T>::getMeetingTopic() const
{
	return meetingTopic;
}

template <class T>
inline bool Meeting_t<T>::operator==(const Meeting_t& other) const
{
	return (startingTime > other.startingTime && startingTime < other.finishTime)
		|| (other.startingTime > startingTime && other.startingTime < finishTime);
}
