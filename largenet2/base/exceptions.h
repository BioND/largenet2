/**
 * @file exceptions.h
 * @date 31.08.2009
 * @author gerd
 */

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
	LNetException(const char* msg) throw() : msg_(msg) { }
	virtual ~LNetException() throw() {}
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
	NotAdjacentException(const char* msg) throw() : LNetException(msg) {}
};

/**
 * Thrown when trying to create parallel edges in simple graphs
 */
class SingletonException : public LNetException
{
public:
	SingletonException(const char* msg) throw() : LNetException(msg) {}
};

}

#endif /* EXCEPTIONS_H_ */
