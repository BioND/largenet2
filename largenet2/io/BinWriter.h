/**
 * @file BinWriter.h
 * @date 15.12.2011
 * @author gerd
 */

#ifndef BINWRITER_H_
#define BINWRITER_H_

#include <largenet2/io/GraphWriter.h>

namespace largenet
{
namespace io
{

/**
 * Write binary graph output
 */
class BinWriter: public largenet::io::GraphWriter
{
public:
	BinWriter() {}
	virtual ~BinWriter() {}
	/**
	 * @copydoc GraphWriter::write()
	 */
	void write(const Graph& g, std::ostream& strm);
};

} /* namespace io */
} /* namespace largenet */
#endif /* BINWRITER_H_ */
