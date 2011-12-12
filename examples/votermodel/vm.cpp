/**
 * @example vm.cpp
 * @section vm_example Voter model example
 *
 * This is a simulation of the directed adaptive voter model as in <a href="http://arxiv.org/abs/1110.1336">Zschaler et al. (2011)</a>.
 * A network of @p N nodes, representing agents, and @p L directed links, representing social connections, is
 * created. Each agent holds one of two possible opinions, @p UP or @p DOWN. The system evolves as
 * follows: In each update step, a random node and a random one of its outgoing neighbors are selected. If
 * they share the same opinion, nothing happens. If they have different opinions, the first node
 * adopts the opinion of its neighbor with probability <tt>(1-p)</tt>. Otherwise, with probability
 * @p p, it cuts its link to the neighbor and rewires it to a random node holding the same opinion.
 *
 * Depending on the parameter @p p, either global consensus is reached, in which every node holds the
 * same opinion, or the network splits into two disconnected clusters of nodes holding opposing opinions.
 * For low @p p, consensus is always achieved, while for large @p p, fragmentation is observed.
 * Fragmentation sets in at a critical value of @p p, which only depends on the average degree of
 * the network, i.e., the ratio of @p L an @p N.
 * If the network contains a substantial fraction of nodes with low out-degree, self-stabilizing structures
 * can form and lead to "early fragmentation".
 *
 * @author Gerd Zschaler <gzschaler@googlemail.com>
 */

#include "VoterModel.h"
#include "RandomVariates.h"
#include "WELLEngine.h"
#include <largenet2.h>
#include <largenet2/StateConsistencyListener.h>
#include <largenet2/generators/generators.h>
#include <iostream>
#include <memory>

using namespace std;
using namespace largenet;

int main(int argc, char **argv)
{
	unsigned int N = 2000; // number of nodes
	unsigned int L = 16000; // number of links

	double initial_up = 0.5; // initial fraction of UP-nodes

	double p = 0.3; // rewiring rate

	double tmax = 1000; // maximum simulation time

	// a random number generator (WELL1024a)
	myrng::RandomVariates<myrng::WELLEngine> rng;

	// Create a Graph object with VoterModel::node_states possible node
	// states and VoterModel::link_states possible link states
	Graph net(VoterModel::node_states, VoterModel::link_states);

	// Create new StateConsistencyListener object and add it to the graph.
	// This object ensures that edge states will be properly updated upon
	// node state changes, so that edge states are always consistent with
	// node states. To that end, the listener object uses the provided
	// EdgeStateCalculator
	StateConsistencyListener<VoterModel::EdgeStateCalculator> scl(
			auto_ptr<VoterModel::EdgeStateCalculator>(
					new VoterModel::EdgeStateCalculator));
	net.addGraphListener(&scl);

	// Connect the nodes randomly to form a random, Erdős-Rényi type network.
	generators::randomGnm(net, N, L, rng, true);

	// Iterate over all nodes in the network
	Graph::NodeIteratorRange nodes = net.nodes();
	for (Graph::NodeIterator n = nodes.first; n != nodes.second; ++n)
		// Set node state to VoterModel::UP for each node
		net.setNodeState(n->id(), VoterModel::UP);

	const node_size_t initialDownNodes = static_cast<node_size_t>(round(
			net.numberOfNodes() * (1.0 - initial_up)));

	// Set the first initialDownNodes' node states to VoterModel::DOWN.
	// Note that this is fine, since the links among the nodes have been placed
	// randomly, i.e., disregarding the node order.
	Graph::NodeIterator n = nodes.first;
	while (net.numberOfNodes(VoterModel::DOWN) < initialDownNodes)
	{
		net.setNodeState(n->id(), VoterModel::DOWN);
		++n;
	}

	// Now, all the edges in the network have been assigned appropriate states
	// by the StateConsistencyListener we supplied. Thus, an edge from an UP-node
	// to a DOWN-node will be in state UD, etc.

	// Create a VoterModel object that uses the Graph object and works with
	// the rewiring rate p
	VoterModel model(net, p);

	// Write output header line
	// (time - up nodes - down nodes - up-up links - up-down links - down-up links - down-down links)
	std::cout << "# t\tup\tdown\tuu\tud\tdu\tdd\n";

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
			std::cout << t << "\t" << net.numberOfNodes(VoterModel::UP) << "\t"
					<< net.numberOfNodes(VoterModel::DOWN) << "\t"
					<< net.numberOfEdges(VoterModel::UU) << "\t"
					<< net.numberOfEdges(VoterModel::UD) << "\t"
					<< net.numberOfEdges(VoterModel::DU) << "\t"
					<< net.numberOfEdges(VoterModel::DD) << "\n";
			next += interval;
		}
		// One simulation step
		t += model.step(rng);
	}

	return 0;
}
