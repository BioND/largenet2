#ifndef EXCEPTIONS_H_
#define EXCEPTIONS_H_

#include <string>

namespace largenet
{

/**
 * Base class for largenet exceptions
 */
class LNetException
{
public:
	/**
	 * Constructor
	 * @param msg exception message
	 */
	LNetException(const char* msg) throw() : msg_(msg) { }
	/**
	 * Destructor
	 */
	virtual ~LNetException() throw() {}
	/**
	 * Get exception message
	 * @return exception message
	 */
	virtual const char* what() const throw() { return msg_.c_str(); }
private:
	std::string msg_;
};

/**
 * Thrown when two nodes are not connected
 */
class NotAdjacentException : public LNetException
{
public:
	/**
	 * Constructor
	 * @param msg exception message
	 */
	NotAdjacentException(const char* msg) throw() : LNetException(msg) {}
};

/**
 * Thrown when trying to create parallel edges in simple graphs
 */
class SingletonException : public LNetException
{
public:
	/**
	 * Constructor
	 * @param msg exception message
	 */
	SingletonException(const char* msg) throw() : LNetException(msg) {}
};

}

#endif /* EXCEPTIONS_H_ */
