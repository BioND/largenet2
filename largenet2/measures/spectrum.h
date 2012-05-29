/**
 * @file spectrum.h
 * @date 29.05.2012
 */

#ifndef SPECTRUM_H_
#define SPECTRUM_H_

#include <largenet2/base/Graph.h>
#include <boost/numeric/ublas/matrix_sparse.hpp>

namespace bnu = boost::numeric::ublas;

namespace largenet
{
namespace measures
{

typedef bnu::mapped_matrix<double> sparse_dmatrix_t;

/**
 * Adjacency matrix of graph @p g.
 *
 * Compute the matrix \f$ A \f$ for the graph @p g, where \f$ A_{ij} = 1 \f$ if nodes
 * \f$ i \f$ and \f$ j \f$ are connected and \f$ A_{ij} = 0 \f$ otherwise.
 * @param g graph object
 * @return adjacency matrix of @p g
 */
sparse_dmatrix_t adjacency_matrix(const Graph& g);

/**
 * Diagonal matrix of node degrees
 * @param g graph object
 * @return diagonal matrix containing the node degrees (ascending node ID order)
 */
sparse_dmatrix_t degree_matrix(const Graph& g);
/**
 * Unnormalized Laplacian of the graph @p g.
 *
 * Compute the matrix \f$ L = D - A\f$, where \f$ D \f$ is the degree matrix of the
 * graph and \f$ A \f$ is its adjacency matrix.
 * @param g graph object
 * @return Laplacian matrix of @p g
 */
sparse_dmatrix_t laplacian(const Graph& g);
/**
 * Normalized Laplacian of the graph @p g.
 *
 * Compute the matrix \f$ D^{-1/2}LD^{-1/2} = I - D^{-1/2}AD^{-1/2} \f$, where \f$ D \f$ is the
 * degree matrix of the graph and \f$ A \f$ is its adjacency matrix.
 * @param g graph object
 * @return Normalized Laplacian matrix of @p g
 */
sparse_dmatrix_t normalized_laplacian(const Graph& g);

}
}

#endif /* SPECTRUM_H_ */
