/**
 * @file MaxMethod.h
 * @date 02.08.2010
 * @author gerd
 */

#ifndef MAXMETHOD_H_
#define MAXMETHOD_H_

#include <boost/ptr_container/ptr_vector.hpp>
#include <cstddef>
#include <stdexcept>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <numeric>
#include <boost/bind.hpp>

namespace sim
{
namespace gillespie
{

class Agent
{
public:
	Agent()
	{
	}
	virtual ~Agent()
	{
	}
};

class MaxMethod
{
public:
	class Process
	{
	public:
		Process()
		{
		}
		virtual ~Process()
		{
		}
		virtual double maxRate() = 0;
		virtual double agentRate(Agent* a) = 0;
		virtual Agent* randomAgent() = 0;
		virtual size_t populationSize() = 0;
		virtual void operator()(Agent* a) = 0;
		virtual size_t numCalls() const
		{
			return 0;
		} // for debugging
		virtual std::string name() const
		{
			return "";
		}
	};
public:
	MaxMethod()
	{
	}
	void registerProcess(Process* p)
	{
		processes_.push_back(p);
	}
	size_t numberOfProcesses() const
	{
		return processes_.size();
	}
	template<class RandomGen> double step(RandomGen& rng)
	{
		typedef vector<double> RateVector;
		RateVector max_rates(processes_.size(), 0.0), max_rates_times_sizes(
				processes_.size(), 0.0);

		// fill max_rates vector
		transform(processes_.begin(), processes_.end(), max_rates.begin(),
				bind(&Process::maxRate, _1));

		// fill max_rates_times_sizes vector
		transform(processes_.begin(), processes_.end(), max_rates.begin(),
				max_rates_times_sizes.begin(), bind(multiplies<double> (),
						bind(&Process::populationSize, _1), _2));

		// calculate 1 / sum(max_rate*pop_size)
		const double total_max_rate_times_size =
				accumulate(max_rates_times_sizes.begin(),
						max_rates_times_sizes.end(), 0.0);
		if (total_max_rate_times_size == 0.0)
			return 1000;

		const double inv_total_max_rate_times_size = 1.0
				/ total_max_rate_times_size;

		double tau = 0;
		while (true)
		{
			// draw length of this time step from exponential distribution
			tau += rng.Exponential(inv_total_max_rate_times_size);

			// pick process with probability max_rate_times_size / total_max_rate_times_size
			// we do not use rng.Choices() here, as we would have to supply all probabilities with proper
			// normalization, potentially leading to rounding/truncation errors
			const double u = rng.Uniform01() * total_max_rate_times_size;
			unsigned int k = 0;
			double s = max_rates_times_sizes[k];
			while (s < u && k < max_rates_times_sizes.size() - 1)
				s += max_rates_times_sizes[++k];

			// execute process with probability agent_rate / max_rate
			Agent* a = processes_[k].randomAgent();
			const double prob = processes_[k].agentRate(a) / max_rates[k];
			if (rng.Chance(prob))
			{
				processes_[k](a);
				break;
			}
		}
		return tau;
	}
	const Process* process(unsigned int index) const;

private:
	typedef boost::ptr_vector<Process> ProcessesVector;
	ProcessesVector processes_;
};

inline const MaxMethod::Process* MaxMethod::process(unsigned int index) const
{
	if (index < processes_.size())
		return &processes_[index];
	else
		throw(std::out_of_range("Process index out of range"));
}

}
}
#endif /* MAXMETHOD_H_ */
