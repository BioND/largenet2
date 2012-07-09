#ifndef WELLENGINE_H_
#define WELLENGINE_H_

/**
 * The WELL1024a random number generator
 *
 * @file WELLEngine.h
 */

namespace myrng
{

/**
 * The WELL1024a random number generator.
 *
 * The acronym WELL stands for "Well Equidistributed Long-period Linear". It
 * has a period of 2^1024, which should be enough for most simulation
 * tasks. It has better equidistribution properties and it recovers faster
 * from a "bad state", e.g. bad initialization, than the MT19937.
 * For more information see F. Panneton, P. L'Ecuyer, and M. Matsumoto,
 * "Improved Long-Period Generators Based on Linear Recurrences Modulo 2",
 * ACM Transactions on Mathematical Software, 32, 1 (2006), 1-16.
 *
 * @author Gerd Zschaler <gzschaler@googlemail.com>
 * @author Marton Morvai
 * @author Thilo Gross <gross@physics.org>
 *
 * @copyright This implementation of the WELL alogrithm is licensed under the
 * Creative Commons Attribution-NonCommercial 3.0 Unported License. To view
 * a copy of this license, visit http://creativecommons.org/licenses/by-nc/3.0/
 * or send a letter to Creative Commons, 444 Castro Street, Suite 900, Mountain
 * View, California, 94041, USA.
 */
class WELLEngine
{
public:
	WELLEngine();
	/// Sets the seed.
	void seed(unsigned long int s);
	/// Returns the seed.
	unsigned long int getSeed() const { return seed_; }
	/// Returns the name of the random number generator engine;
	const char* getName() { return "WELL1024a"; }

protected:
	~WELLEngine() {}
	/// Produce a random number.
	double operator()();

private:
	unsigned long int seed_; ///< the initial seed

	unsigned int z0, z1, z2, state_i;
	unsigned int STATE[32];
};

} /* namespace myrng */
#endif /* WELLENGINE_H_ */
