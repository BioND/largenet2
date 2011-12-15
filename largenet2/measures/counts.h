/**
 * @file counts.h
 * @date 19.11.2010
 * @author gerd
 */

#ifndef COUNTS_H_
#define COUNTS_H_

#include <largenet2/base/Graph.h>
#include <largenet2/motifs/TripleMotif.h>
#include <largenet2/motifs/QuadStarMotif.h>
#include <cstddef>

namespace largenet {
namespace measures {

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
