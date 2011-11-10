/*
 * motif_construction.cpp
 *
 *  Created on: 04.02.2009
 *      Author: gerd
 */

#include "motif_construction.h"
#include "../NodeMotif.h"
#include "../LinkMotif.h"
#include "../TripleMotif.h"
#include "../QuadLineMotif.h"
#include "../QuadStarMotif.h"

namespace largenet
{
namespace motifs
{
namespace detail
{

template<>
void constructAllMotifs(std::set<NodeMotif>& m, node_state_size_t states,
		bool directed)
{
	for (node_state_t n = 0; n < states; ++n)
		m.insert(NodeMotif(n));
}

template<>
void constructAllMotifs(std::set<LinkMotif>& m, node_state_size_t states,
		bool directed)
{
	for (node_state_t a = 0; a < states; ++a)
		for (node_state_t b = 0; b < states; ++b)
			m.insert(LinkMotif(a, b, directed));
}

template<>
void constructAllMotifs(std::set<TripleMotif>& m, node_state_size_t states,
		bool directed)
{
	if (!directed)
	{
		for (node_state_t a = 0; a < states; ++a)
			for (node_state_t b = 0; b < states; ++b)
				for (node_state_t c = 0; c < states; ++c)
					m.insert(TripleMotif(a, b, c, TripleMotif::NO_DIR));
	}
	else
	{
		for (node_state_t a = 0; a < states; ++a)
			for (node_state_t b = 0; b < states; ++b)
				for (node_state_t c = 0; c < states; ++c)
				{
					m.insert(TripleMotif(a, b, c, TripleMotif::LCR));
					m.insert(TripleMotif(a, b, c, TripleMotif::LRC));
					m.insert(TripleMotif(a, b, c, TripleMotif::RCL));
					m.insert(TripleMotif(a, b, c, TripleMotif::CLR));
				}

	}
}

template<>
void constructAllMotifs(std::set<QuadLineMotif>& m, node_state_size_t states,
		bool directed)
{
	if (!directed)
	{
		for (node_state_t a = 0; a < states; ++a)
			for (node_state_t b = 0; b < states; ++b)
				for (node_state_t c = 0; c < states; ++c)
					for (node_state_t d = 0; d < states; ++d)
						m.insert(QuadLineMotif(a, b, c, d,
								QuadLineMotif::NO_DIR));
	}
	else
	{
		for (node_state_t a = 0; a < states; ++a)
			for (node_state_t b = 0; b < states; ++b)
				for (node_state_t c = 0; c < states; ++c)
					for (node_state_t d = 0; d < states; ++d)
					{
						m.insert(
								QuadLineMotif(a, b, c, d, QuadLineMotif::RLINE));
						m.insert(QuadLineMotif(a, b, c, d, QuadLineMotif::C_IN));
						m.insert(
								QuadLineMotif(a, b, c, d, QuadLineMotif::C_OUT));
						m.insert(QuadLineMotif(a, b, c, d, QuadLineMotif::B_IN));
						m.insert(
								QuadLineMotif(a, b, c, d, QuadLineMotif::B_OUT));
						m.insert(QuadLineMotif(a, b, c, d,
								QuadLineMotif::B_IN_C_OUT));
						m.insert(QuadLineMotif(a, b, c, d,
								QuadLineMotif::B_OUT_C_IN));
						m.insert(
								QuadLineMotif(a, b, c, d, QuadLineMotif::LLINE));
					}
	}
}

template<>
void constructAllMotifs(std::set<QuadStarMotif>& m, node_state_size_t states,
		bool directed)
{
	if (!directed)
	{
		for (node_state_t a = 0; a < states; ++a)
			for (node_state_t b = 0; b < states; ++b)
				for (node_state_t c = 0; c < states; ++c)
					for (node_state_t d = 0; d < states; ++d)
						m.insert(QuadStarMotif(a, b, c, d,
								QuadStarMotif::NO_DIR));
	}
	else
	{
		for (node_state_t a = 0; a < states; ++a)
			for (node_state_t b = 0; b < states; ++b)
				for (node_state_t c = 0; c < states; ++c)
					for (node_state_t d = 0; d < states; ++d)
					{
						m.insert(QuadStarMotif(a, b, c, d,
								QuadStarMotif::ALL_IN));
						m.insert(QuadStarMotif(a, b, c, d,
								QuadStarMotif::ALL_OUT));
						m.insert(
								QuadStarMotif(a, b, c, d, QuadStarMotif::A_OUT));
						m.insert(
								QuadStarMotif(a, b, c, d, QuadStarMotif::B_OUT));
						m.insert(
								QuadStarMotif(a, b, c, d, QuadStarMotif::C_OUT));
						m.insert(QuadStarMotif(a, b, c, d,
								QuadStarMotif::AB_OUT));
						m.insert(QuadStarMotif(a, b, c, d,
								QuadStarMotif::AC_OUT));
						m.insert(QuadStarMotif(a, b, c, d,
								QuadStarMotif::BC_OUT));
					}
	}
}

}
}
}
