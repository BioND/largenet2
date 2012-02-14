/**
 * @file DegDistOutput.h
 * @date 30.07.2009
 * @author gerd
 */

#ifndef DEGDISTOUTPUT_H_
#define DEGDISTOUTPUT_H_

#include <largenet2/sim/output/IntervalOutput.h>
#include <largenet2/motifs/motifs.h>
#include <largenet2/measures/DegreeDistribution.h>
#include <boost/ptr_container/ptr_map.hpp>
#include <iomanip>
#include <algorithm>

namespace lmo = largenet::motifs;
namespace lmeas = largenet::measures;

namespace sim
{

namespace output
{

/**
 * Calculates and outputs the *directed* degree distribution for each node state in the network.
 */
template<class _Graph>
class DegDistOutput: public IntervalOutput
{
public:
	DegDistOutput(std::ostream& out, const _Graph& net, double interval) :
		IntervalOutput(out, interval), net_(net), nodeMotifs_(
				net_.numberOfNodeStates())
	{
	}
	virtual ~DegDistOutput()
	{
	}

private:
	void doOutput(double t)
	{
		typedef boost::ptr_map<lmo::NodeMotif, lmeas::InDegreeDistribution>
				in_dist_map;
		typedef boost::ptr_map<lmo::NodeMotif, lmeas::OutDegreeDistribution>
				out_dist_map;

		in_dist_map in_dists;
		out_dist_map out_dists;
		largenet::degree_t maxDegree = 0;
		for (lmo::NodeMotifSet::const_iterator motif = nodeMotifs_.begin(); motif
				!= nodeMotifs_.end(); ++motif)
		{
			lmeas::InDegreeDistribution* d1 = new lmeas::InDegreeDistribution(
					net_, *motif);
			in_dists.insert(*motif, std::auto_ptr<lmeas::InDegreeDistribution>(
					d1));
			lmeas::OutDegreeDistribution* d2 =
					new lmeas::OutDegreeDistribution(net_, *motif);
			out_dists.insert(*motif,
					std::auto_ptr<lmeas::OutDegreeDistribution>(d2));

			if (maxDegree < d1->maxDegree())
				maxDegree = d1->maxDegree();
			if (maxDegree < d2->maxDegree())
				maxDegree = d2->maxDegree();
		}

		const char tab = '\t';
		for (largenet::degree_t k = 0; k <= maxDegree; ++k)
		{
			stream() << t << tab << k;
			for (in_dist_map::const_iterator i = in_dists.begin(); i
					!= in_dists.end(); ++i)
				stream() << tab << (*i->second)[k];
			for (out_dist_map::const_iterator i = out_dists.begin(); i
					!= out_dists.end(); ++i)
				stream() << tab << (*i->second)[k];
			stream() << "\n";
		}
		stream() << "\n\n";
	}

	void doWriteHeader()
	{
		const char tab = '\t';
		stream() << commentChar() << " t" << tab << "k";
		for (lmo::NodeMotifSet::const_iterator motif = nodeMotifs_.begin(); motif
				!= nodeMotifs_.end(); ++motif)
			stream() << tab << "i" << *motif;
		for (lmo::NodeMotifSet::const_iterator motif = nodeMotifs_.begin(); motif
				!= nodeMotifs_.end(); ++motif)
			stream() << tab << "o" << *motif;
		stream() << "\n";

	}

	const _Graph& net_;
	lmo::NodeMotifSet nodeMotifs_;
};

template<class _Graph>
class StatelessDegDistOutput: public IntervalOutput
{
public:
	StatelessDegDistOutput(std::ostream& out, const _Graph& net,
			double interval) :
		IntervalOutput(out, interval), net_(net)
	{
	}
	virtual ~StatelessDegDistOutput()
	{
	}

private:
	void doOutput(double t)
	{
		lmeas::InDegreeDistribution in_dist(net_);
		lmeas::OutDegreeDistribution out_dist(net_);
		largenet::degree_t maxDegree = std::max(in_dist.maxDegree(),
				out_dist.maxDegree());

		const char tab = '\t';
		for (largenet::degree_t k = 0; k <= maxDegree; ++k)
		{
			stream() << t << tab << k << tab << in_dist[k] << tab
					<< out_dist[k] << "\n";
		}
		stream() << "\n\n";
	}

	void doWriteHeader()
	{
		const char tab = '\t';
		stream() << commentChar() << " t" << tab << "k" << tab << "in" << tab
				<< "out\n";
	}

	const _Graph& net_;
};

template<class _Graph>
class UndirectedDegDistOutput: public IntervalOutput
{
public:
	UndirectedDegDistOutput(std::ostream& out, const _Graph& net, double interval) :
		IntervalOutput(out, interval), net_(net), nodeMotifs_(
				net_.numberOfNodeStates())
	{
	}
	virtual ~UndirectedDegDistOutput()
	{
	}

private:
	void doOutput(double t)
	{
		typedef boost::ptr_map<lmo::NodeMotif, lmeas::UndirectedDegreeDistribution>
				un_dist_map;

		un_dist_map un_dists;
		largenet::degree_t maxDegree = 0;
		for (lmo::NodeMotifSet::const_iterator motif = nodeMotifs_.begin(); motif
				!= nodeMotifs_.end(); ++motif)
		{
			lmeas::UndirectedDegreeDistribution* d1 = new lmeas::UndirectedDegreeDistribution(
					net_, *motif);
			un_dists.insert(*motif, std::auto_ptr<lmeas::UndirectedDegreeDistribution>(
					d1));
			if (maxDegree < d1->maxDegree())
				maxDegree = d1->maxDegree();
		}

		const char tab = '\t';
		for (largenet::degree_t k = 0; k <= maxDegree; ++k)
		{
			stream() << t << tab << k;
			for (un_dist_map::const_iterator i = un_dists.begin(); i
					!= un_dists.end(); ++i)
				stream() << tab << (*i->second)[k];
			stream() << "\n";
		}
		stream() << "\n\n";
	}

	void doWriteHeader()
	{
		const char tab = '\t';
		stream() << commentChar() << " t" << tab << "k";
		for (lmo::NodeMotifSet::const_iterator motif = nodeMotifs_.begin(); motif
				!= nodeMotifs_.end(); ++motif)
			stream() << tab << *motif;
		stream() << "\n";
	}

	const _Graph& net_;
	lmo::NodeMotifSet nodeMotifs_;
};

}
}

#endif /* DEGDISTOUTPUT_H_ */
