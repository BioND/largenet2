#ifndef TEST_TYPES_H_
#define TEST_TYPES_H_

#include <iostream>
#include <boost/test/unit_test_log.hpp>

class MyInt
{
public:
	MyInt() : m_(0) {}
	explicit MyInt(int i) : m_(i) { BOOST_TEST_MESSAGE( "New MyInt(" << m_ << ")." ); }
	MyInt(const MyInt& o) : m_(o.m_) { BOOST_TEST_MESSAGE( "Copy-constructed MyInt(" << m_ << ")" ); }
	~MyInt() { BOOST_TEST_MESSAGE( "Destroyed MyInt(" << m_ << ")." ); }
	operator int() const { return m_; }
	MyInt& operator=(const MyInt& o) { if (this != &o) { m_ = o.m_; BOOST_TEST_MESSAGE( "Assignment from MyInt(" << m_ << ")." ); } return *this; }
	MyInt& operator=(const int i) { m_ = i; return *this; }
	friend bool operator==(const MyInt& a, const int i) { return a.m_ == i; }
	friend bool operator==(const int i, const MyInt& a) { return a.m_ == i; }
	bool operator==(const MyInt& o) const { return m_ == o.m_; }
	void sayHello() const { BOOST_TEST_MESSAGE( "Hello from MyInt(" << m_ << ")." ); }
private:
	int m_;
};

inline std::ostream& operator<<(std::ostream& o, const MyInt& i)
{
	o << "MyInt(" << static_cast<const int> (i) << ")";
	return o;
}

#endif /* TEST_TYPES_H_ */
