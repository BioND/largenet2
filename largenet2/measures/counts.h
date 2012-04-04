/**
 * @file counts.h
 * @date 19.11.2010
 * @author gerd
 */

#ifndef COUNTS_H_
#define COUNTS_H_

#include <largenet2/base/Graph.h>
#include <largenet2/motifs/NodeMotif.h>
#include <largenet2/motifs/LinkMotif.h>
#include <largenet2/motifs/TripleMotif.h>
#include <largenet2/motifs/QuadStarMotif.h>
#include <cstddef>

namespace largenet {
namespace measures {

/**
 * Total number of nodes in graph.
 *
 * @param net Graph object
 * @return number of nodes in @p net
 */
inline size_t nodes(const Graph& net)
{
	return net.numberOfNodes();
}
/**
 * Total number of nodes of type @p n in graph.
 *
 * @param net Graph object
 * @param n NodeMotif to count
 * @return number of @p n nodes in @p net
 */
inline size_t nodes(const Graph& net, const motifs::NodeMotif& n)
{
	return net.numberOfNodes(n);
}

/**
 * Total number of edges in graph
 *
 * @param net Graph object
 * @return number of edges in @p net
 */
inline size_t edges(const Graph& net)
{
	return net.numberOfEdges();
}
/**
 * Total number of edges of type @p l in graph.
 *
 * @param net Graph object
 * @param l LinkMotif to count
 * @return number of @p l edges in @p net
 */
size_t edges(const Graph& net, const motifs::LinkMotif& l);

/**
 * Total number of triples in graph.
 *
 * A triple consists of three nodes connected in a row (either closed or open triangle).
 *
 * @param net Graph object
 * @return number of triples in @p net
 */
size_t triples(const Graph& net);
size_t inTriples(const Graph& net);
size_t outTriples(const Graph& net);
size_t inOutTriples(const Graph& net);
size_t triples(const Graph& net, const motifs::TripleMotif& t);

/**
 * Total number of closed triangles in graph.
 * @param net Graph object
 * @return number of triangles in @p net
 */
size_t triangles(const Graph& net);

size_t quadStars(const Graph& net);
size_t outQuadStars(const Graph& net);
size_t inQuadStars(const Graph& net);
size_t quadStars(const Graph& net, const motifs::QuadStarMotif& q);

}
}

#endif /* COUNTS_H_ */
