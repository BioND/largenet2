/**
 * @file DegDistOutput.h
 * @date 30.07.2009
 * @author gerd
 */

#ifndef DEGDISTOUTPUT_H_
#define DEGDISTOUTPUT_H_

#include "IntervalOutput.h"
#include "../../network/motifs/motifs.h"
#include <map>
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
		stream() << commentChar() << "t = " << std::setprecision(9) << t
				<< "\n";
		std::map<largenet::motifs::NodeMotif, largenet::measures::degree_dist_t> dists;
		largenet::id_size_t maxDegree = 0;
		for (largenet::motifs::NodeMotifSet::const_iterator motif =
				nodeMotifs_.begin(); motif != nodeMotifs_.end(); ++motif)
		{
			largenet::measures::degreeDistribution(net_, dists[*motif], *motif);
			if (maxDegree < dists[*motif].size())
				maxDegree = dists[*motif].size();
		}

		const char tab = '\t';
		for (largenet::id_size_t k = 0; k < maxDegree; ++k)
		{
			stream() << k;
			for (largenet::motifs::NodeMotifSet::const_iterator motif =
					nodeMotifs_.begin(); motif != nodeMotifs_.end(); ++motif)
			{
				if (k < dists[*motif].size())
					stream() << tab << dists[*motif][k];
				else
					stream() << tab << 0;
			}
			stream() << "\n";
		}
		stream() << "\n\n";
	}

	void doWriteHeader()
	{
		const char tab = '\t';
		stream() << commentChar();
		for (largenet::motifs::NodeMotifSet::const_iterator motif =
				nodeMotifs_.begin(); motif != nodeMotifs_.end(); ++motif)
		{
			stream() << tab << *motif;
		}
		stream() << "\n";

	}

	const _Graph& net_;
	lnet::motifs::NodeMotifSet nodeMotifs_;
};

}

#endif /* DEGDISTOUTPUT_H_ */
