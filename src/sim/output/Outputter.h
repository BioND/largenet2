/**
 * @file Outputter.h
 * @date 30.07.2009
 * @author gerd
 */

#ifndef OUTPUTTER_H_
#define OUTPUTTER_H_

#include <boost/ptr_container/ptr_vector.hpp>

namespace sim {

class IntervalOutput;

class Outputter
{
public:
	Outputter();
	virtual ~Outputter();
	void writeHeaders();
	void output(double t);
	void addOutput(IntervalOutput* output);
private:
	typedef boost::ptr_vector<IntervalOutput> OutputVector;
	OutputVector outputs_;
};
}
#endif /* OUTPUTTER_H_ */
