/**
 * @file measures.h
 * @date 12.01.2011
 * @author gerd
 */

#ifndef MEASURES_H_
#define MEASURES_H_

#include <largenet2/base/Graph.h>
#include <utility>

namespace largenet
{
/**
 * Various graph-theoretic measures
 */
namespace measures
{

typedef std::pair<degree_t, degree_t> degree_range_t;

degree_t maxInDegree(const Graph& g);
degree_t minInDegree(const Graph& g);
degree_range_t inDegreeRange(const Graph& g);

degree_t maxOutDegree(const Graph& g);
degree_t minOutDegree(const Graph& g);
degree_range_t outDegreeRange(const Graph& g);

inline double meanDegree(const Graph& g)
{
	return static_cast<double> (g.numberOfEdges()) / g.numberOfNodes();
}

/**
 * One-point correlation function: Pearson's correlation coefficient for in- and out-degree.
 * @param g Graph to compute correlation coefficient for.
 * @return Correlation coefficient $r\in[-1,1]$ of linear dependence between the nodes' in- and out-degrees.
 */
double inOutDegreeCorrelation(const Graph& g);

struct NeighborDegreeCorrelations
{
	double r_ii, r_io, r_oi, r_oo;
};

NeighborDegreeCorrelations neighborDegreeCorrelations(const Graph& g);

/**
 * Two-point correlation function: Pearson's correlation coefficient for in-degrees of adjacent nodes
 * @param g Graph
 * @return correlation coefficient between in-degrees of adjacent nodes
 */
double neighborDegreeCorrelationInIn(const Graph& g);
/**
 * Two-point correlation function: Pearson's correlation coefficient for in- and out-degrees of adjacent nodes
 * @param g Graph
 * @return correlation coefficient between the nodes' in-degrees and out-degrees of outgoing neighbors.
 */
double neighborDegreeCorrelationInOut(const Graph& g);
/**
 * Two-point correlation function: Pearson's correlation coefficient for out-degrees of adjacent nodes
 * @param g Graph
 * @return correlation coefficient between out-degrees of adjacent nodes
 */
double neighborDegreeCorrelationOutOut(const Graph& g);
/**
 * Two-point correlation function: Pearson's correlation coefficient for in- and out-degrees of adjacent nodes
 * @param g Graph
 * @return correlation coefficient between the nodes' out-degrees and in-degrees of outgoing neighbors.
 */
double neighborDegreeCorrelationOutIn(const Graph& g);

}
}

#endif /* MEASURES_H_ */
