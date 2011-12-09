/**
 * WELL1024a implementation
 *
 * @file WELLEngine.cpp
 */

#include "WELLEngine.h"
#include <cassert>
#include <ctime>

namespace myrng
{

WELLEngine::WELLEngine()
{
	// Long has to be at least 32 bits!
	assert(sizeof(long) >= 4);
	state_i = 0;
	seed((unsigned long) time(0));
}

void WELLEngine::seed(unsigned long int s)
{
	/**
	 * After the engine has been seeded, this function generates 50.000
	 * random numbers to let it recover at least a little bit from a
	 * bad init state.
	 * \param s seed
	 */
	seed_ = s;
	STATE[0] = s & 0xffffffffUL;
	for (int i = 1; i < 32; ++i)
	{
		STATE[i] = (1812433253UL * (STATE[i - 1] ^ (STATE[i - 1] >> 30)) + i);
		STATE[i] &= 0xffffffffUL;
		// for >32 bit machines
	}
	for (int j = 0; j < 10000; ++j)
		(*this)();
}

double WELLEngine::operator()()
{
	/**
	 * This generator is an Implementation of WELL1024a
	 * (F. Panneton, P. L'Ecuyer, and M. Matsumoto,
	 * "Improved Long-Period Generators Based on Linear Recurrences Modulo 2",
	 * ACM Transactions on Mathematical Software, 32, 1 (2006), 1-16.)
	 */
	z0 = STATE[(state_i + 31) & 0x0000001fU];
	z1 = (STATE[state_i]) ^ STATE[(state_i + 3) & 0x0000001fU];
	z2 = (STATE[(state_i + 24) & 0x0000001fU]
			^ (STATE[(state_i + 24) & 0x0000001fU] << (19)))
			^ (STATE[(state_i + 10) & 0x0000001fU]
					^ (STATE[(state_i + 10) & 0x0000001fU] << (14)));

	STATE[state_i] = z1 ^ z2;
	STATE[(state_i + 31) & 0x0000001fU] = (z0 ^ (z0 << (11)))
			^ (z1 ^ (z1 << (7))) ^ (z2 ^ (z2 << (13)));

	state_i = (state_i + 31) & 0x0000001fUL;
	return ((double) STATE[state_i] * 2.32830643653869628906e-10);
}

} /* namespace myrng */

