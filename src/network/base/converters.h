/*
 * converters.h
 *
 *  Created on: 28.03.2011
 *      Author: gerd
 */

#ifndef CONVERTERS_H_
#define CONVERTERS_H_

#include "Graph.h"

namespace largenet {
namespace converters {

/**
 * Replaces each directed edge by an undirected one. Depending on the graph's element
 * factory, double edges are created or silently ignored.
 * @param g
 */
void toUndirected(Graph& g);

/**
 * Replaces each undirected edge by a pair of directed edges.
 * @param g Graph to modify
 */
void toDirected(Graph& g);

}
}

#endif /* CONVERTERS_H_ */
