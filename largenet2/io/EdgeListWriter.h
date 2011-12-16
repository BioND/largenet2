/**
 * @file EdgeListWriter.h
 * @date 06.10.2010
 * @author gerd
 */

#ifndef EDGELISTWRITER_H_
#define EDGELISTWRITER_H_

#include <largenet2/io/GraphWriter.h>

namespace largenet
{

namespace io
{
/**
 * Write graphs in edge list format including node states.
 *
 * See EdgeListReader for the edge list format.
 */
class EdgeListWriter: public GraphWriter
{
public:
	EdgeListWriter() : writeNodeStates_(false) {}
	virtual ~EdgeListWriter() {}
	/**
	 * @copybrief GraphWriter::write()
	 * @param g graph to write to stream
	 * @param strm stream to write graph in edge list format to
	 */
	void write(const Graph& g, std::ostream& strm);
	/**
	 * Check whether this writer writes node states
	 */
    bool writesNodeStates() const
    {
        return writeNodeStates_;
    }
    /**
     * Also write node states
     * @param val
     */
    void writeNodeStates(bool val)
    {
        writeNodeStates_ = val;
    }
private:
	bool writeNodeStates_;
};

}

}

#endif /* EDGELISTWRITER_H_ */
