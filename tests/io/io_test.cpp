/**
 * @file io_test.cpp
 * @date 16.12.2011
 * @author gerd
 */

#include <largenet2.h>
#include <largenet2/io/BinWriter.h>
#include <largenet2/io/BinReader.h>
#include <largenet2/io/DotWriter.h>
#include <iostream>
#include <fstream>

using namespace std;
using namespace largenet;

int main(int argc, char **argv)
{
	Graph g(2, 4);
	g.addNode(0); // 0
	g.addNode(0); // 1
	g.addNode(1); // 2
	g.addNode(1); // 3
	edge_id_t e = g.addEdge(0, 1, true);
	g.setEdgeState(e, 0);
	e = g.addEdge(0, 2, true);
	g.setEdgeState(e, 1);
	e = g.addEdge(2, 3, true);
	g.setEdgeState(e, 3);

	cout << "Writing graph to binary file.\n";
	cout << "Graph with " << g.numberOfNodes() << " nodes in "
			<< g.numberOfNodeStates() << " states and " << g.numberOfEdges()
			<< " edges.\n";
	ofstream outfile("iotest.net", ios::binary);
	if (outfile)
	{
		io::BinWriter writer;
		writer.write(g, outfile);
		outfile.close();
	}

	cout << "Writing graph to DOT file.\n";
	outfile.open("iotest.dot");
	if (outfile)
	{
		io::DotWriter writer;
		writer.write(g, outfile);
		outfile.close();
	}

	cout << "Trying to read graph from binary file.\n";
	ifstream infile("iotest.net", ios::binary);
	Graph* g2 = 0;
	if (infile)
	{
		io::BinReader reader;
		g2 = reader.createFromStream(infile);
		infile.close();
		cout << "Graph with " << g2->numberOfNodes() << " nodes in "
				<< g2->numberOfNodeStates() << " states and "
				<< g2->numberOfEdges() << " edges.\n";
	}
	delete g2;
}
