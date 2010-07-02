/**
 * @file StochasticSimulation.h
 * @date 13.07.2009
 * @author gerd
 */

#ifndef STOCHASTICSIMULATION_H_
#define STOCHASTICSIMULATION_H_

#include <vector>
#include <boost/function.hpp>

namespace sim {

class StochasticSimulation
{
public:
	typedef boost::function<double()> RateFunctor;
	typedef boost::function<void()> ProcFunctor;

	StochasticSimulation();
	void registerProcess(const RateFunctor& rateFunc,
			const ProcFunctor& procFunc);
	double step();
	unsigned int countReactions() const;

private:
	std::vector<unsigned int> pr_; ///< priority list
	std::vector<double> rates_;
	std::vector<RateFunctor> rateFuncs_;
	std::vector<ProcFunctor> procFuncs_;
};

inline void StochasticSimulation::registerProcess(const RateFunctor& rateFunc,
		const ProcFunctor& procFunc)
{
	pr_.push_back(pr_.size());
	rateFuncs_.push_back(rateFunc);
	procFuncs_.push_back(procFunc);
	rates_.push_back(rateFunc());
}

inline unsigned int StochasticSimulation::countReactions() const
{
	return rateFuncs_.size();
}
}
#endif /* STOCHASTICSIMULATION_H_ */
