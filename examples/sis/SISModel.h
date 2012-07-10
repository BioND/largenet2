#ifndef SISMODEL_H_
#define SISMODEL_H_

#include <largenet2.h>
#include <largenet2/sim/gillespie/DirectMethod.h>
#include <boost/bind.hpp>
#include "../lib/util.h"

/**
 * The SISModel class in the @ref sis_example.
 *
 * @example sis.cpp
 */
template<class RandomGen>
class SISModel
{
private:
	typedef SISModel<RandomGen> self_type;
public:
	static const largenet::node_state_size_t node_states = 2; ///< number of node states
	static const largenet::edge_state_size_t link_states = 3; ///< number of edge states

	struct Params
	{
		double p; ///< infection probability per S-I-link
		double r; ///< recovery probability per I-node
		double w; ///< rewiring probability per S-I-link
	};

	/// Names for node states
	enum NodeState
	{
		S, I
	};
	/**
	 * Names for edge states
	 *
	 * Note that the edge states will be computed automatically by the library from the
	 * states of the two nodes an edge connects by the largenet::StateConsistencyListener,
	 * which makes use of the supplied SISModel::EdgeStateCalculator.
	 *
	 * @see largenet2/StateConsistencyListener.h
	 */
	enum LinkState
	{
		SS, SI, II
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
		 * @return edge state
		 */
		largenet::edge_state_t operator()(const largenet::node_state_t s,
				const largenet::node_state_t t) const
		{
			if (s != t)
				return SI;
			else if (s == S)
				return SS;
			else
				return II;
		}
	};


	/**
	 * Constructor
	 * @param net Graph instance to use for the simulation
	 * @param p SIS model parameters
	 * @param rng Random number generator to use for the simulation
	 */
	SISModel(largenet::Graph& net, Params p, RandomGen& rng) :
	net_(net), par_(p), rng_(rng)
	{
		// Register the different processes with the Gillespie stepper.
		// Each process is registered with a rate function which computes
		// the instantaneous reaction rate for the process and an "action"
		// function which performs the action of the process. Note how
		// the convenient use of boost::bind allows to use SISModel member
		// functions for this.
		stepper.registerProcess(
				boost::bind(&self_type::infectionRate, this),
				boost::bind(&self_type::infect, this)
				);
		stepper.registerProcess(
				boost::bind(&self_type::recoveryRate, this),
				boost::bind(&self_type::recover, this)
				);
		stepper.registerProcess(
				boost::bind(&self_type::rewiringRate, this),
				boost::bind(&self_type::rewire, this)
				);
	}

	/**
	 * Check whether the simulation has stopped
	 *
	 * Returns true when no further updates are possible (i.e. the absorbing
	 * state of zero infectious nodes has been reached).
	 */
	bool stopped()
	{
		return net_.numberOfNodes(I) == 0;
	}

	/**
	 * Perform one simulation step
	 * @param rng Random number generator, providing a method IntFromTo(int, int)
	 * that returns a random integer between the specified boundaries.
	 * @return time increment
	 */
	double step(RandomGen& rng)
	{
		return stepper.step(rng);
	}

private:
	double infectionRate() const
	{
		return net_.numberOfEdges(SI) * par_.p;
	}
	double recoveryRate() const
	{
		return net_.numberOfNodes(I) * par_.r;
	}
	double rewiringRate() const
	{
		return net_.numberOfEdges(SI) * par_.w;
	}

	void infect()
	{
		largenet::Graph::EdgeStateIterator edge = myrng::util::random_from(
				net_.edges(SI), rng_);
		if (net_.nodeState(edge->source()->id()) == S)
			net_.setNodeState(edge->source()->id(), I);
		else
			net_.setNodeState(edge->target()->id(), I);
	}

	void recover()
	{
		largenet::Graph::NodeStateIterator n = myrng::util::random_from(
				net_.nodes(I), rng_);
		net_.setNodeState(n.id(), S);
	}

	void rewire()
	{
		largenet::Graph::EdgeStateIterator e = myrng::util::random_from(
				net_.edges(SI), rng_);

		largenet::Node* n =
				(net_.nodeState(e->source()->id()) == S) ?
						e->source() : e->target();
		net_.removeEdge(e->id());
		largenet::edge_size_t old_edges = net_.numberOfEdges();
		unsigned int tries = 0;
		const unsigned int max_tries = net_.numberOfNodes(S);
		largenet::Graph::NodeStateIterator n2 = myrng::util::random_from(
				net_.nodes(S), rng_);
		while (tries < max_tries)
		{
			if (n->id() == n2.id()) // disallow self-loops
			{
				n2 = myrng::util::random_from(net_.nodes(S), rng_);
				++tries;
				continue;
			}

			net_.addEdge(n->id(), n2.id(), false);	// undirected edge

			if (net_.numberOfEdges() == old_edges) // could not add edge (already in graph)
			{
				n2 = myrng::util::random_from(net_.nodes(S), rng_);
				++tries;
				continue;
			}
			else
				break;
		}
	}

private:
	largenet::Graph& net_;
	Params par_;
	sim::gillespie::DirectMethod stepper;
	RandomGen& rng_;
};

#endif /* SISMODEL_H_ */
