/**
 * @file DirectMethod.h
 * @date 13.07.2009
 * @author gerd
 */

#ifndef DIRECTMETHOD_H_
#define DIRECTMETHOD_H_

#include <boost/function.hpp>
#include <vector>
#include <algorithm>
#include <cassert>

namespace sim
{
namespace gillespie
{

class DirectMethod
{
public:
	typedef boost::function<double()> RateFunctor;
	typedef boost::function<void()> ProcFunctor;

	DirectMethod() {}
	void registerProcess(const RateFunctor& rateFunc,
			const ProcFunctor& procFunc)
	{
		pr_.push_back(pr_.size());
		rateFuncs_.push_back(rateFunc);
		procFuncs_.push_back(procFunc);
		rates_.push_back(rateFunc());
	}
	template<class RandomGen>
	double step(RandomGen& rng)
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

		if (k > 0)
			std::swap(pr_[k], pr_[k - 1]);
		return tau;
	}
	unsigned int countReactions() const
	{
		return rateFuncs_.size();
	}

private:
	std::vector<unsigned int> pr_; ///< priority list
	std::vector<double> rates_;
	std::vector<RateFunctor> rateFuncs_;
	std::vector<ProcFunctor> procFuncs_;
};

}
}

#endif /* DIRECTMETHOD_H_ */
