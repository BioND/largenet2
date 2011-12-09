/**
 * @file VoterModel.h
 * @author Gerd Zschaler <gzschaler@googlemail.com>
 */

#ifndef VOTERMODEL_H_
#define VOTERMODEL_H_

#include "util.h"
#include <largenet2.h>

class VoterModel
{
public:
	static const largenet::node_state_size_t node_states = 2;
	static const largenet::edge_state_size_t link_states = 4;

	/// Names for node states
	enum NodeState
	{
		UP, DOWN
	};
	/**
	 * Names for link states
	 *
	 * Note that the link states will be computed automatically by the library from the
	 * states of the two nodes a link connects using a lnet::DefaultLinkStateCalculator.
	 * To use enum names for the automatically computed states, they have to be specified
	 * in canonical order in the enum.
	 *
	 * @see largenet/base/state_calculators.h
	 * @see largenet/motifs/LinkMotif.h
	 */
	enum LinkState
	{
		UU, UD, DU, DD
	};

	class EdgeStateCalculator
	{
	public:
		EdgeStateCalculator()
		{
		}
		largenet::edge_state_t operator()(const largenet::node_state_t s,
				const largenet::node_state_t t) const
		{
			if (s == UP)
			{
				if (t == UP)
					return UU;
				else
					return UD;
			}
			else if (t == UP)
				return DU;
			else
				return DD;
		}
	};

	VoterModel(largenet::Graph& net, double p) :
			net_(net), p_(p)
	{
	}

	bool stopped() const
	{
		return (net_.numberOfNodes(UP) == 0) || (net_.numberOfNodes(DOWN) == 0)
				|| ((net_.numberOfEdges(UD) == 0)
						&& (net_.numberOfEdges(DU) == 0));
	}

	template<class RandomGen> double step(RandomGen& rng)
	{
		// do nothing if there is only one node
		if (net_.numberOfNodes() < 2)
			return 1000;

		// here, we measure time in units of 1/L
		const double tau = 1.0 / net_.numberOfEdges();

		// Get a random node from the network. If the network contains zero
		// nodes, this throws an exception.
		largenet::Node* n1 = net_.randomNode(rng);

		// Get a random out-going edge of the node. For convenience,
		// we use the helper function random_from() defined in util.h,
		// which returns a Node::edge_iterator object.
		largenet::Node::edge_iterator ei = random_from(n1->outEdges(), rng);
		if (ei == n1->outEdges().second)
			return tau; // do nothing if the node has no neighbors

		// Get the actual edge
		largenet::Edge* e = *ei;

		// Do nothing if the nodes share the same state
		if (net_.nodeState(e->source()->id())
				== net_.nodeState(e->target()->id()))
			return tau;

		// Rewire with probability p (we use the random number generator rng)
		if (rng.Chance(p_))
			rewire(e, rng);
		// or copy the neighbor's state with probability (1-p)
		else
			net_.setNodeState(e->source()->id(),
					net_.nodeState(e->target()->id()));

		// return time increment
		return tau;
	}

private:
	template<class RandomGen> void rewire(largenet::Edge* e, RandomGen& rng)
	{
		// get source node state
		largenet::node_state_t s = net_.nodeState(e->source()->id());

		// do nothing if there are no nodes (in the same state) we can rewire to
		if (net_.numberOfNodes(s) == 1)
			return;

		largenet::edge_size_t old_edges = net_.numberOfEdges();

		// try only so often to rewire a link
		largenet::node_size_t tries = 0;
		const largenet::node_size_t max_tries = net_.numberOfNodes(s);
		while (tries < max_tries)
		{
			// get a random node in the same state as the source node
			largenet::Node* n = net_.randomNode(s, rng);

			if (n == e->source()) // disallow self-loops
			{
				++tries;
				continue;
			}

			net_.addEdge(e->source()->id(), n->id(), true);

			if (net_.numberOfEdges() == old_edges) // could not add edge (already in graph)
			{
				++tries;
				continue;
			}
			else
			{
				net_.removeEdge(e->id());
				return;
			}
		}
	}

	largenet::Graph& net_;
	double p_;
};

#endif /* VOTERMODEL_H_ */
