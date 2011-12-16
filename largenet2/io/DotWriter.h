/**
 * @file DotWriter.h
 * @date 16.12.2011
 * @author gerd
 */

#ifndef DOTWRITER_H_
#define DOTWRITER_H_

#include <largenet2/io/GraphWriter.h>

namespace largenet
{
namespace io
{

/**
 * Write graph in Graphviz DOT format.
 * 
 * @see http://www.graphviz.org/doc/info/lang.html
 */
class DotWriter: public largenet::io::GraphWriter
{
public:
	DotWriter() {}
	virtual ~DotWriter() {}
	/**
	 * @copydoc GraphWriter::write()
	 */
	void write(const Graph& g, std::ostream& strm);
};

} /* namespace io */
} /* namespace largenet */
#endif /* DOTWRITER_H_ */
