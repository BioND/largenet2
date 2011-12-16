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
 * 
 *
 * @author gerd
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
	/**
	 * Create a graph from stream data, using an existing Graph object
	 * @param strm Stream to read data from
	 * @param[out] graphToFill Graph object to hold the new graph, will be cleared before filling
	 * @return pointer to @p graphToFill
	 */
	Graph* createFromStream(std::istream& strm, Graph& graphToFill);
};

} /* namespace io */
} /* namespace largenet */
#endif /* BINREADER_H_ */
