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
/// degree range type (for (min, max) degree pair)
typedef std::pair<degree_t, degree_t> degree_range_t;

/**
 * Get maximum in-degree in graph @p g
 */
degree_t maxInDegree(const Graph& g);
/**
 * Get minimum in-degree in graph @p g
 */
degree_t minInDegree(const Graph& g);
/**
 * Get in-degree range (min, max) in graph @p g
 */
degree_range_t inDegreeRange(const Graph& g);
/**
 * Get maximum out-degree in graph @p g
 */
degree_t maxOutDegree(const Graph& g);
/**
 * Get minimum out-degree in graph @p g
 */
degree_t minOutDegree(const Graph& g);
/**
 * Get out-degree range (min, max) in graph @p g
 */
degree_range_t outDegreeRange(const Graph& g);
/**
 * Get mean degree in graph @p g
 */
inline double meanDegree(const Graph& g)
{
	return static_cast<double> (g.numberOfEdges()) / g.numberOfNodes();
}

/**
 * One-point correlation function: Pearson's correlation coefficient for in- and out-degree.
 * @param g Graph to compute correlation coefficient for.
 * @return Correlation coefficient \f$r\in[-1,1]\f$ of linear dependence between the nodes' in- and out-degrees.
 */
double inOutDegreeCorrelation(const Graph& g);

/**
 * Combined nearest-neighbor degree correlation coefficients.
 */
struct NeighborDegreeCorrelations
{
	double r_ii;	///< in-in-degree correlation along directed edges
	double r_io;	///< in-out-degree correlation along directed edges
	double r_oi;	///< out-in-degree correlations along directed edges
	double r_oo;	///< out-out-degree correlations along directed edges
};

/**
 * Two-point correlation functions for all four possible combinations.
 * @param g Graph object
 * @return correlation coefficients
 */
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
