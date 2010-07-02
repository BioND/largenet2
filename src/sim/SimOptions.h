/**
 * @file SimOptions.h
 * @date 12.11.2009
 * @author gerd
 */

#ifndef SIMOPTIONS_H_
#define SIMOPTIONS_H_

#include <string>
#include <iostream>
#include <boost/noncopyable.hpp>

namespace sim {

class SimOptions: public boost::noncopyable
{
public:
	SimOptions() {}
	virtual ~SimOptions() {}
	void setup(int argc, char** argv) { parseCommandLine(argc, argv); }
	void printHelp(std::ostream& out) const { printHelpText(out); }
	std::string str() const { return toStr(); }
	void write(std::ostream& out) const { toStream(out); }

private:
	virtual void printHelpText(std::ostream& out) const = 0;
	virtual void parseCommandLine(int argc, char** argv) = 0;
	virtual std::string toStr() const = 0;
	virtual void toStream(std::ostream& out) const = 0;
};

inline std::ostream& operator<<(std::ostream &out, const SimOptions& o)
{
	o.write(out);
	return out;
}

}
#endif /* SIMOPTIONS_H_ */
