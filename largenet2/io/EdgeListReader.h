/**
 * @file EdgeListReader.h
 * @date 06.10.2010
 * @author gerd
 */

#ifndef EDGELISTREADER_H_
#define EDGELISTREADER_H_

#include <largenet2/io/GraphReader.h>

namespace largenet
{

namespace io
{
/**
 * Read graphs from edge list data.
 *
 * Appropriate input data is in edge list format including node states, that
 * is one edge per line as
 * @verbatim source target source_state target_state @endverbatim
 *
 * For instance,
 * @verbatim
0 1 0 0
1 2 0 1
1 3 0 0 @endverbatim
 * represents the graph
 * @dot
	strict digraph mygraph {
	 layout=neato
	 size="2,2"
	 node[label="\N",shape=circle]
	 0 [color=green];
	 1 [color=green];
	 2 [color=red];
	 3 [color=green];
	 0 -> 1;
	 1 -> 2;
	 1 -> 3;
	}
 * @enddot
 * where the @p 0 state is marked in green and the @p 1 state is marked in red.
 */
class EdgeListReader: public GraphReader
{
public:
	EdgeListReader() {}
	virtual ~EdgeListReader() {}
	/**
	 * @copybrief GraphReader::createFromStream(std::istream&)
	 * @param strm Stream providing edge list data
	 */
	Graph* createFromStream(std::istream& strm);
	/**
	 * @copybrief GraphReader::createFromStream(std::istream&,Graph&)
	 * @param strm Stream providing edge list data
	 * @param[out] graphToFill Graph object to hold the new graph, will be cleared before filling
	 * @return pointer to @p graphToFill
	 */
	Graph* createFromStream(std::istream& strm, Graph& graphToFill);
};

}

}

#endif /* EDGELISTREADER_H_ */
