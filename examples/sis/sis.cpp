/**
 * @example sis.cpp
 * @section sis_example SIS model example
 *
 * This is a simulation of a simple epidemiological susceptible-infected-susceptible (SIS)
 * model on an adaptive network as in <a href="http://dx.doi.org/10.1103/PhysRevLett.96.208701">Gross et al. (2006)</a>.
 * A network of @p N nodes, representing agents, and @p L undirected links, representing social connections, is
 * created. Each agent is either susceptible to a communicable disease, @p S, or infected, @p I.
 * With probability @p p per link between susceptible and infected nodes and per unit time,
 * a susceptible node contracts the disease from an infectious neighbour. With probability @p r
 * an infected node recovers and becomes susceptible again. Additionally, susceptible nodes
 * seek to avoid their infectious neighbours by rewiring links between susceptible and infectious
 * nodes with probability @p w per link and unit time. Thus a link connecting a susceptible and
 * and infectious node is removed and a new one between the susceptible and another, randomly
 * selected susceptible node is established.
 *
 * Depending on the model parameters @p p, @p r, @p w, the disease-free state is stable or
 * unstable. Additionally, the rewiring activity (non-zero @p w) allows for a bistable regime
 * where both states coexist, and the final outcome depends on the initial conditions.
 *
 * @author Gerd Zschaler <gzschaler@googlemail.com>
 */

#include "SISModel.h"
#include "../lib/RandomVariates.h"
#include "../lib/WELLEngine.h"
#include <largenet2.h>
#include <largenet2/StateConsistencyListener.h>
#include <largenet2/generators/generators.h>
#include <iostream>
#include <memory>

using namespace std;
using namespace largenet;

int main(int argc, char **argv)
{
	const unsigned int N = 10000; // number of nodes
	const unsigned int L = 100000; // number of links

	// a random number generator (WELL1024a)
	typedef myrng::RandomVariates<myrng::WELLEngine> rng_t;
	rng_t rng;

	// define our own model type for SISModel using rng_t
	typedef SISModel<rng_t> model_t;

	// Model parameters; these are in the bistable regime, so the
	// final state depends on the initial conditions.
	model_t::Params params =
	{
			0.006,  // infection rate
			0.002,  // recovery rate
			0.2  	// rewiring rate
	};

	// initial conditions
	const double initial_infected = 0.2; // initial fraction of infected nodes

	const double tmax = 1000; // maximum simulation time

	// Create a Graph object with SISModel::node_states possible node
	// states and SISModel::link_states possible link states
	Graph net(model_t::node_states, model_t::link_states);

	// Create new StateConsistencyListener object and add it to the graph.
	// This object ensures that edge states will be properly updated upon
	// node state changes, so that edge states are always consistent with
	// node states. To that end, the listener object uses the provided
	// EdgeStateCalculator
	StateConsistencyListener<model_t::EdgeStateCalculator> scl(
			auto_ptr<model_t::EdgeStateCalculator>(
					new model_t::EdgeStateCalculator));
	net.addGraphListener(&scl);

	// Connect the nodes randomly to form a random, undirected Erdős-Rényi
	// type network.
	generators::randomGnm(net, N, L, rng, false);

	// Iterate over all nodes in the network
	Graph::NodeIteratorRange nodes = net.nodes();
	for (Graph::NodeIterator n = nodes.first; n != nodes.second; ++n)
		// Set node state to model_t::S for each node
		net.setNodeState(n->id(), model_t::S);

	const node_size_t initiallyInfectedNodes = static_cast<node_size_t>(round(
			net.numberOfNodes() * initial_infected));

	// Set the first initiallyInfectedNodes' node states to SISModel::I
	// Note that this is fine, since the links among the nodes have been placed
	// randomly, i.e., disregarding the node order.
	Graph::NodeIterator n = nodes.first;
	while (net.numberOfNodes(model_t::I) < initiallyInfectedNodes)
	{
		net.setNodeState(n->id(), model_t::I);
		++n;
	}

	// Now, all the edges in the network have been assigned appropriate states
	// by the StateConsistencyListener we supplied. Thus, an edge from an S-node
	// to an I-node will be in state SI, etc.

	// Create a SISModel object that uses the Graph object, works with
	// the specified model parameters, and uses the provided random number
	// generator
	model_t model(net, params, rng);

	// Write output header line
	// (time - S-nodes - I-nodes - S-S-links - S-I-links - I-I-links)
	std::cout << "# t\tS\tI\tSS\tSI\tII\n";

	// Simulation loop
	// Perform model steps until simulation time exceeds maximum or the model
	// has stopped (no further changes possible)
	double t = 0, next = 0;
	double interval = 1; // output interval
	while ((t <= tmax) && (!model.stopped()))
	{
		// only write output at specified intervals
		if (t >= next)
		{
			std::cout << t << "\t" << net.numberOfNodes(model_t::S) << "\t"
					<< net.numberOfNodes(model_t::I) << "\t"
					<< net.numberOfEdges(model_t::SS) << "\t"
					<< net.numberOfEdges(model_t::SI) << "\t"
					<< net.numberOfEdges(model_t::II) << "\n";
			next += interval;
		}
		// One simulation step
		t += model.step(rng);
	}

	// Make sure that final state is written
	std::cout << t << "\t" << net.numberOfNodes(model_t::S) << "\t"
			<< net.numberOfNodes(model_t::I) << "\t"
			<< net.numberOfEdges(model_t::SS) << "\t"
			<< net.numberOfEdges(model_t::SI) << "\t"
			<< net.numberOfEdges(model_t::II) << "\n";

	return 0;
}

