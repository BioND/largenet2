/*
 * motif_construction.cpp
 *
 *  Created on: 04.02.2009
 *      Author: gerd
 */

#include "motif_construction.h"
#include "../NodeMotif.h"
#include "../LinkMotif.h"

namespace largenet
{
namespace motifs
{
namespace detail
{

template<>
void constructAllMotifs(std::set<NodeMotif>& m, node_state_size_t states, bool directed)
{
	for (node_state_t n = 0; n < states; ++n)
		m.insert(NodeMotif(n));
}

template<>
void constructAllMotifs(std::set<LinkMotif>& m, node_state_size_t states, bool directed)
{
	for (node_state_t a = 0; a < states; ++a)
		for (node_state_t b = 0; b < states; ++b)
			m.insert(LinkMotif(a, b, directed));
}

/*
template<>
void constructAllMotifs(std::set<TripleMotif>& m, node_state_size_t states)
{
	for (node_state_t a = 0; a < states; ++a)
		for (node_state_t b = 0; b < states; ++b)
			for (node_state_t c = 0; c < states; ++c)
				m.insert(TripleMotif(a, b, c));
}

template<>
void constructAllMotifs(std::set<QuadLineMotif>& m, node_state_size_t states)
{
	for (node_state_t a = 0; a < states; ++a)
		for (node_state_t b = 0; b < states; ++b)
			for (node_state_t c = 0; c < states; ++c)
				for (node_state_t d = 0; d < states; ++d)
					m.insert(QuadLineMotif(a, b, c, d));
}

template<>
void constructAllMotifs(std::set<QuadStarMotif>& m, node_state_size_t states)
{
	for (node_state_t a = 0; a < states; ++a)
		for (node_state_t b = 0; b < states; ++b)
			for (node_state_t c = 0; c < states; ++c)
				for (node_state_t d = 0; d < states; ++d)
					m.insert(QuadStarMotif(a, b, c, d));
}

*/
}
}
}
