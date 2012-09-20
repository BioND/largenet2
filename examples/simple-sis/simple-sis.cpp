#include <iostream>
#include <largenet2.h>
#include <largenet2/StateConsistencyListener.h>
#include <largenet2/generators/generators.h>
#include "../lib/RandomVariates.h"
#include "../lib/WELLEngine.h"
#include "../lib/util.h"

using namespace std;
using namespace largenet;

enum NodeState
{
	S, I
};
enum EdgeState
{
	SS, SI, II
};

// a random number generator (WELL1024a)
typedef myrng::RandomVariates<myrng::WELLEngine> RandomNumberGenerator;

class EdgeStateCalc
{
public:
	edge_state_t operator()(node_state_t source, node_state_t target) const
	{
		if (source == target)
		{
			if (source == S)
				return SS;
			else
				return II;
		}
		else
			return SI;
	}
};

void printOutputLine(double t, const Graph& graph)
{
	cout << t << "\t" << graph.numberOfNodes(S) << "\t"
			<< graph.numberOfNodes(I) << "\t" << graph.numberOfEdges(SS) << "\t"
			<< graph.numberOfEdges(SI) << "\t" << graph.numberOfEdges(II)
			<< "\n";
}

void initializeNodeStates(const double initiallyInfectedFraction, Graph& graph)
{
	node_size_t numberOfInitiallyInfectedNodes = initiallyInfectedFraction
			* graph.numberOfNodes();
	for (Graph::NodeIterator n = graph.nodes().first; n != graph.nodes().second;
			++n)
		graph.setNodeState(n.id(), I);
}

void infectOnRandomSIEdge(Graph& graph,
		RandomNumberGenerator& randomNumberGenerator)
{
	Graph::EdgeStateIterator edge = myrng::util::random_from(graph.edges(SI),
			randomNumberGenerator);
	node_id_t susceptibleNode =
			graph.nodeState(edge->source()->id()) == S ?
					edge->source()->id() : edge->target()->id();
	graph.setNodeState(susceptibleNode, I);
}

void recoverRandomINode(Graph& graph,
		RandomNumberGenerator& randomNumberGenerator)
{
	Graph::NodeStateIterator node = myrng::util::random_from(graph.nodes(I),
			randomNumberGenerator);
	graph.setNodeState(node->id(), S);
}

int main(int argc, char **argv)
{
	const node_size_t numberOfNodes = 1000;
	const double averageDegree = 4.0;
	const edge_size_t numberOfEdges = averageDegree * numberOfNodes / 2.0;

	const double infectionRate = 0.03;
	const double recoveryRate = 0.02;

	const double initiallyInfectedFraction = 0.1;
	const double maximumSimulationTime = 1000;

	Graph graph(2, 3);
	StateConsistencyListener<EdgeStateCalc> consistencyListener(
			auto_ptr<EdgeStateCalc>(new EdgeStateCalc));
	graph.addGraphListener(&consistencyListener);

	RandomNumberGenerator randomNumberGenerator;
	generators::randomGnm(graph, numberOfNodes, numberOfEdges,
			randomNumberGenerator, false);

	initializeNodeStates(initiallyInfectedFraction, graph);

	double t = 0;
	printOutputLine(t, graph);
	while (t < maximumSimulationTime)
	{
		if (graph.numberOfNodes(I) == 0)
			break;
		double instantaneousInfectionRate = infectionRate
				* graph.numberOfEdges(SI);
		double instantaneousRecoveryRate = recoveryRate
				* graph.numberOfNodes(I);
		double totalRate = instantaneousInfectionRate
				+ instantaneousRecoveryRate;
		if (totalRate == 0.0)
			break;
		t += randomNumberGenerator.Exponential(1.0 / totalRate);
		if (randomNumberGenerator.Chance(
				instantaneousInfectionRate / totalRate))
			infectOnRandomSIEdge(graph, randomNumberGenerator);
		else
			recoverRandomINode(graph, randomNumberGenerator);
		printOutputLine(t, graph);
	}
	return 0;
}
