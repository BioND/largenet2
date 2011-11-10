/**
 * @file IntervalOutput.cpp
 * @date 30.07.2009
 * @author gerd
 */

#include "IntervalOutput.h"

namespace sim
{
namespace output
{

IntervalOutput::IntervalOutput(std::ostream& out, const double interval,
		const std::string commentChar) :
	interval_(interval), nextOutputTime_(0), out_(out), commentChar_(
			commentChar)
{
}

IntervalOutput::~IntervalOutput()
{
}

void IntervalOutput::output(const double t, const bool force)
{
	if (force || t >= nextOutputTime_)
	{
		doOutput(t);
		nextOutputTime_ += interval_;
	}
}

}
}
