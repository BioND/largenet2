/**
 * @file BinReader.h
 * @date 16.12.2011
 * @author gerd
 */

#ifndef BINREADER_H_
#define BINREADER_H_

#include <largenet2/io/GraphReader.h>

namespace largenet
{
namespace io
{

/**
 * Read binary graph data
 * 
 * Reads binary data according to the following format:
 * @image html bin-format.png
 * where @p N and @p L denote the numbers of nodes and edges, respectively,
 * and <tt>n<sub>N</sub></tt> and <tt>n<sub>E</sub></tt> denote the numbers
 * of node and edge states. These are then followed by @p N pairs of node IDs
 * and corresponding node states. Finally, @p L triplets of source and target
 * node IDs and corresponding edge states are interpreted as the network edges.
 */
class BinReader: public largenet::io::GraphReader
{
public:
	BinReader() {}
	virtual ~BinReader() {}
	/**
	 * Create a new Graph object from stream
	 * @param strm Stream to read graph data from
	 * @return pointer to new graph object
	 */
	Graph* createFromStream(std::istream& strm);
};

} /* namespace io */
} /* namespace largenet */
#endif /* BINREADER_H_ */
