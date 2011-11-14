/**
 * @file types.h
 * @date 01.09.2009
 * @author gerd
 */

#ifndef LARGENET_TYPES_H_
#define LARGENET_TYPES_H_

/**
 * The largenet namespace
 */
namespace largenet {

/// Node ID type
typedef unsigned long int node_id_t;
/// Node count type
typedef node_id_t node_size_t;
/// Edge id type
typedef unsigned long int edge_id_t;
/// Edge count type
typedef edge_id_t edge_size_t;
/// Degree type (is a node count type)
typedef unsigned long int degree_t;
/// Degree size type (is degree type)
typedef degree_t degree_size_t;
/**
 * Node state type
 *
 * A node state is an integer value, which may represent different
 * node types or categories. Using the methods provided by the Graph
 * interface, one can efficiently traverse all nodes in a given
 * state, or randomly select a node in a given state, for instance.
 */
typedef unsigned int node_state_t;
/// Node state count type
typedef node_state_t node_state_size_t;
/**
 * Edge state type
 *
 * A edge state is an integer value, which may represent different
 * edge types or categories. Using the methods provided by the Graph
 * interface, one can efficiently traverse all edges in a given
 * state, or randomly select an edge in a given state, for instance.
 */
typedef unsigned int edge_state_t;
/// Edge state count type
typedef edge_state_t edge_state_size_t;

}

#endif /* LARGENET_TYPES_H_ */
