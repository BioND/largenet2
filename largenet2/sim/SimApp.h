/**
 * @file SimApp.h
 * @date 12.11.2009
 * @author gerd
 */

#ifndef SIMAPP_H_
#define SIMAPP_H_

#include <largenet2/sim/output/Outputter.h>
#include <string>
#include <fstream>
#include <boost/noncopyable.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

namespace sim {

class SimApp: public boost::noncopyable
{
public:
	SimApp(int argc, char** argv)
	{
	}

	virtual ~SimApp()
	{ // actually, this is not necessary
		for (ofstream_ptr_v::iterator i = outStreams_.begin(); i
				!= outStreams_.end(); ++i)
			i->close();
	}

	virtual int exec()
	{
		return 0;
	}

	void setAppName(std::string name)
	{
		appName_ = name;
	}

	void setAppName(const char* name)
	{
		appName_ = name;
	}

	std::string appName() const
	{
		return appName_;
	}

protected:
	std::ofstream& openOutputStream(std::string filename)
	{
		std::auto_ptr<std::ofstream> o(new std::ofstream(filename.c_str()));
		if (o->bad())
		{
			o->close();
			throw("Could not open " + filename + " for writing!\n");
		}
		outStreams_.push_back(o);
		return outStreams_.back();

	}

	void registerOutput(output::IntervalOutput* output)
	{
		outputter_.addOutput(output);
	}

	void writeHeaders()
	{
		outputter_.writeHeaders();
	}

	void output(double t, bool force = false)
	{
		outputter_.output(t, force);
	}

private:
	std::string appName_;
	output::Outputter outputter_;
	typedef boost::ptr_vector<std::ofstream> ofstream_ptr_v;
	ofstream_ptr_v outStreams_;
};
}
#endif /* SIMAPP_H_ */
