/**
 * @file DegDistOutput.h
 * @date 30.07.2009
 * @author gerd
 */

#ifndef DEGDISTOUTPUT_H_
#define DEGDISTOUTPUT_H_

#include "IntervalOutput.h"
#include "../../network/motifs/motifs.h"
#include "../../network/measures/DegreeDistribution.h"
#include <boost/ptr_container/ptr_map.hpp>
#include <iomanip>

namespace sim {

/**
 * Calculates and outputs the degree distribution for each node state in the network.
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
		typedef boost::ptr_map<largenet::motifs::NodeMotif, largenet::measures::InDegreeDistribution> in_dist_map;
		typedef boost::ptr_map<largenet::motifs::NodeMotif, largenet::measures::OutDegreeDistribution> out_dist_map;

		in_dist_map in_dists;
		out_dist_map out_dists;
		largenet::degree_t maxDegree = 0;
		for (largenet::motifs::NodeMotifSet::const_iterator motif =
				nodeMotifs_.begin(); motif != nodeMotifs_.end(); ++motif)
		{
			largenet::measures::InDegreeDistribution* d1 = new largenet::measures::InDegreeDistribution(net_, *motif);
			in_dists.insert(*motif, std::auto_ptr<largenet::measures::InDegreeDistribution>(d1));
			largenet::measures::OutDegreeDistribution* d2 = new largenet::measures::OutDegreeDistribution(net_, *motif);
			out_dists.insert(*motif, std::auto_ptr<largenet::measures::OutDegreeDistribution>(d2));

			if (maxDegree < d1->maxDegree())
				maxDegree = d1->maxDegree();
			if (maxDegree < d2->maxDegree())
				maxDegree = d2->maxDegree();
		}

		const char tab = '\t';
		for (largenet::degree_t k = 0; k <= maxDegree; ++k)
		{
			stream() << t << tab << k;
			for (in_dist_map::const_iterator i = in_dists.begin(); i != in_dists.end(); ++i)
				stream() << tab << (*i->second)[k];
			for (out_dist_map::const_iterator i = out_dists.begin(); i != out_dists.end(); ++i)
				stream() << tab << (*i->second)[k];
			stream() << "\n";
		}
		stream() << "\n\n";
	}

	void doWriteHeader()
	{
		const char tab = '\t';
		stream() << commentChar() << " t" << tab << "k";
		for (largenet::motifs::NodeMotifSet::const_iterator motif =
				nodeMotifs_.begin(); motif != nodeMotifs_.end(); ++motif)
			stream() << tab << "i" << *motif;
		for (largenet::motifs::NodeMotifSet::const_iterator motif =
				nodeMotifs_.begin(); motif != nodeMotifs_.end(); ++motif)
			stream() << tab << "o" << *motif;
		stream() << "\n";

	}

	const _Graph& net_;
	largenet::motifs::NodeMotifSet nodeMotifs_;
};

}

#endif /* DEGDISTOUTPUT_H_ */
