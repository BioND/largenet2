/**
 * @file StochasticSimulation.cpp
 * @date 14.07.2009
 * @author gerd
 */

#include "StochasticSimulation.h"
#include "../myrng1.2/myrngWELL.h"
#include <algorithm>
#include <cassert>

namespace sim {

StochasticSimulation::StochasticSimulation()
{
}

double StochasticSimulation::step()
{
	assert(rates_.size() == pr_.size());
	assert(rateFuncs_.size() == pr_.size());
	assert(procFuncs_.size() == pr_.size());
	double atot = 0.0;
	for (unsigned int i = 0; i < rates_.size(); ++i)
	{
		rates_[i] = (rateFuncs_[i])();
		atot += rates_[i];
	}
	if (atot == 0.0)
		return 1000;

	const double tau = rng.Exponential(1.0 / atot);
	const double x = rng.Uniform01() * atot;
	unsigned int k = 0;
	double sum = rates_[pr_[k]];
	while (sum < x)
		sum += rates_[pr_[++k]];

	// call process k
	procFuncs_[pr_[k]]();

	if (k > 0) std::swap(pr_[k], pr_[k-1]);
	return tau;
}
}
