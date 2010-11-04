/**
 * @file Outputter.cpp
 * @date 30.07.2009
 * @author gerd
 */

#include "Outputter.h"
#include "IntervalOutput.h"

namespace sim
{
namespace output
{

Outputter::Outputter()
{
}

Outputter::~Outputter()
{
}

void Outputter::addOutput(IntervalOutput* output)
{
	outputs_.push_back(output);
}

void Outputter::output(const double t, const bool force)
{
	for (OutputVector::iterator it = outputs_.begin(); it != outputs_.end(); ++it)
	{
		it->output(t, force);
	}
}

void Outputter::writeHeaders()
{
	for (OutputVector::iterator it = outputs_.begin(); it != outputs_.end(); ++it)
	{
		it->writeHeader();
	}
}

}
}
