/**
 * @file VoterModel.h
 * The VoterModel class in the voter model example.
 * @author Gerd Zschaler <gzschaler@googlemail.com>
 */

#ifndef VOTERMODEL_H_
#define VOTERMODEL_H_

#include "util.h"
#include <largenet2.h>

/**
 * The voter model class in the @ref vm.cpp "voter model example".
 */
class VoterModel
{
public:
	static const largenet::node_state_size_t node_states = 2; ///< number of node states
	static const largenet::edge_state_size_t link_states = 4; ///< number of edge states

	/// Names for node states
	enum NodeState
	{
		UP, DOWN
	};
	/**
	 * Names for edge states
	 *
	 * Note that the edge states will be computed automatically by the library from the
	 * states of the two nodes an edge connects by the largenet::StateConsistencyListener,
	 * which makes use of the supplied VoterModel::EdgeStateCalculator.
	 *
	 * @see largenet2/StateConsistencyListener.h
	 */
	enum LinkState
	{
		UU, UD, DU, DD
	};

	/**
	 * An edge state calculator
	 *
	 * This computes appropriate edge states from source and target node states.
	 */
	class EdgeStateCalculator
	{
	public:
		EdgeStateCalculator()
		{
		}
		/**
		 * Compute edge state from given node states
		 * @param s source node state
		 * @param t target node state
		 * @return
		 */
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

	/**
	 * Constructor
	 * @param net Graph instance to use for the simulation
	 * @param p rewiring rate
	 */
	VoterModel(largenet::Graph& net, double p) :
			net_(net), p_(p)
	{
	}

	/**
	 * Check whether the simulation has stopped
	 *
	 * Returns true when no further updates are possible (i.e. an absorbing
	 * state of zero active links and/or all nodes in the same state has
	 * been reached)
	 */
	bool stopped() const
	{
		return (net_.numberOfNodes(UP) == 0) || (net_.numberOfNodes(DOWN) == 0)
				|| ((net_.numberOfEdges(UD) == 0)
						&& (net_.numberOfEdges(DU) == 0));
	}

	/**
	 * Perform one simulation step
	 * @param rng Random number generator, providing a method IntFromTo(int, int)
	 * that returns a random integer between the specified boundaries.
	 * @return time increment
	 */
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
	/**
	 * Rewire an edge to a new target with the same state as the source node
	 * @param e edge to rewire
	 * @param rng random number generator providing an IntFromTo(int, int) member
	 */
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
