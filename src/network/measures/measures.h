/**
 * @file measures.h
 * @date 12.01.2011
 * @author gerd
 */

#ifndef MEASURES_H_
#define MEASURES_H_

#include "../base/Graph.h"
#include <utility>

namespace largenet
{

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

}
}

#endif /* MEASURES_H_ */
