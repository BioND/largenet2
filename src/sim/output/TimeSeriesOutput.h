/**
 * @file TimeSeriesOutput.h
 * @date 29.07.2009
 * @author gerd
 */

#ifndef TIMESERIESOUTPUT_H_
#define TIMESERIESOUTPUT_H_

#include "IntervalOutput.h"
#include "../../network/motifs/motifs.h"
#include <iomanip>

namespace sim
{

/**
 * Outputs numbers of nodes, links, and possibly triples in all states in the network.
 */
template<class _Graph, class _LinkStateCalculator>
class TimeSeriesOutput: public IntervalOutput
{
public:
	TimeSeriesOutput(std::ostream& out, const _Graph& net,
			const _LinkStateCalculator& lsc, double interval, bool directedMotifs);
	virtual ~TimeSeriesOutput();

private:
	void doOutput(double t);
	void doWriteHeader();
	void addTripleOutput(const char sep) {}
	void addTripleHeader(const char sep) {}
	const _Graph& net_;
	const _LinkStateCalculator& lsc_;
	const largenet::motifs::NodeMotifSet nodeMotifs_;
	const largenet::motifs::LinkMotifSet linkMotifs_;
	//	const largenet::motifs::TripleMotifSet tripleMotifs_;
};

template<class _Graph, class _LinkStateCalculator>
TimeSeriesOutput<_Graph, _LinkStateCalculator>::TimeSeriesOutput(
		std::ostream& out, const _Graph& net, const _LinkStateCalculator& lsc,
		const double interval, const bool directedMotifs) :
	IntervalOutput(out, interval), net_(net), lsc_(lsc), nodeMotifs_(
			net.numberOfNodeStates(), directedMotifs), linkMotifs_(
			net.numberOfNodeStates(), directedMotifs)
//			, tripleMotifs_(net.numberOfNodeStates(), directedMotifs)
{
}

template<class _Graph, class _LinkStateCalculator>
TimeSeriesOutput<_Graph, _LinkStateCalculator>::~TimeSeriesOutput()
{
}

template<class _Graph, class _LinkStateCalculator>
void TimeSeriesOutput<_Graph, _LinkStateCalculator>::doOutput(const double t)
{
	const char sep = '\t';
	stream() << std::setprecision(9) << t;
	for (largenet::motifs::NodeMotifSet::const_iterator it =
			nodeMotifs_.begin(); it != nodeMotifs_.end(); ++it)
		stream() << sep << net_.numberOfNodes(*it);
	for (largenet::motifs::LinkMotifSet::const_iterator it =
			linkMotifs_.begin(); it != linkMotifs_.end(); ++it)
		stream() << sep << net_.numberOfEdges(lsc_(it->source(), it->target()));

	addTripleOutput(sep);
	stream() << "\n";
}

template<class _Graph, class _LinkStateCalculator>
void TimeSeriesOutput<_Graph, _LinkStateCalculator>::doWriteHeader()
{
	const char tab = '\t';
	stream() << commentChar() << "   t";
	for (largenet::motifs::NodeMotifSet::const_iterator it =
			nodeMotifs_.begin(); it != nodeMotifs_.end(); ++it)
		stream() << tab << *it;
	for (largenet::motifs::LinkMotifSet::const_iterator it =
			linkMotifs_.begin(); it != linkMotifs_.end(); ++it)
		stream() << tab << *it;

	addTripleHeader(tab);
	stream() << "\n";
}
//
//template<>
//void TimeSeriesOutput<lnet::TripleMultiNetwork>::addTripleHeader(const char sep)
//{
//	for (largenet::motifs::TripleMotifSet::const_iterator it =
//			tripleMotifs_.begin(); it != tripleMotifs_.end(); ++it)
//		stream() << sep << *it;
//}
//
//template<>
//void TimeSeriesOutput<lnet::TripleNetwork>::addTripleHeader(const char sep)
//{
//	for (largenet::motifs::TripleMotifSet::const_iterator it =
//			tripleMotifs_.begin(); it != tripleMotifs_.end(); ++it)
//		stream() << sep << *it;
//}
//
//template<>
//void TimeSeriesOutput<lnet::TripleMultiNetwork>::addTripleOutput(const char sep)
//{
//	for (largenet::motifs::TripleMotifSet::const_iterator it =
//			tripleMotifs_.begin(); it != tripleMotifs_.end(); ++it)
//		stream() << sep << net_.numberOfTriples(
//				net_.getTripleStateCalculator()(*it));
//}
//
//template<>
//void TimeSeriesOutput<lnet::TripleNetwork>::addTripleOutput(const char sep)
//{
//	for (largenet::motifs::TripleMotifSet::const_iterator it =
//			tripleMotifs_.begin(); it != tripleMotifs_.end(); ++it)
//		stream() << sep << net_.numberOfTriples(
//				net_.getTripleStateCalculator()(*it));
//}
}
#endif /* TIMESERIESOUTPUT_H_ */
