#ifndef MY_RNG_WELL
#define MY_RNG_WELL

#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <cassert>
using namespace std;

/*************************************************************************//**
 * myrng  by  Thilo Gross and Marton Morvai                  Version 1.2     \n
 * --------------------------------------------------------------------------\n
 *
 * \par A convenient random number generator
 * The purpose of this package is to provide you with convinient random
 * number generators for simulation. The generators shuffle their outputs to
 * avoid unwanted properties of linear RNGs, but nevertheless they are linear,
 * so none of them should be used for encryption.
 *
 * \par
 * To use a random number generator just include the appropriate header file.
 * You can choose between myrngWELL.h and myrngMT.h. Both classes initiate
 * and seed a global random number generator called rng, which you can
 * use instantly everywhere in your code. (See testMT.cpp or testWELL.cpp
 * provided with this package for a very easy working example.)
 * Because both header files define a class with the same name (CMyRng)
 * and both RNGs have the same interface you just have to change the include
 * statement to use the other RNG.
 * \par
 * For a detailed description of the interface please refer to the attached
 * documentation.
 *
 * \par Some information about the two generators
 * - 1. WELL1024a (myrngWELL.h):\n
 * The acronym WELL stands for "Well Equidistributed Long-period Linear". It
 * has a period of 2^1024, which should be enough for the most simulation
 * tasks. It has better equidistribution properties and it recovers faster
 * from a "bad state", e.g. bad initialization, than the MT19937.
 * For more information see F. Panneton, P. L'Ecuyer, and M. Matsumoto,
 * "Improved Long-Period Generators Based on Linear Recurrences Modulo 2",
 * ACM Transactions on Mathematical Software, 32, 1 (2006), 1-16.
 * - 2. MT19937a (myrngMT.h):\n
 * The Marsenne Twister has a ridiculous high period of 2^19937. If it is
 * seeded with a decent value the probability that the generator hits a bad
 * state during the simulation is quite small. If it hits a "bad state" or is
 * badly initialized it can take several hundred thousand steps to recover,
 * i.e. for several hundred thousand steps the bits of the generated numbers
 * will be dominated by either zeros or ones.
 * But the seed function is written to avoid a bad initialization so this
 * generator can also be used without hesitation.
 * For more information see
 * http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/emt .
 *
 * \par
 * The WELL1024a is in this implementation a hint faster than the MT19937.
 *
 * \par Remark on the examples
 * Which generator you use, is up to you. I used the WELL generator in all
 * the examples, but if you want to use MT instead, you just have to substitute
 * \code
 *   include "myrngWELL.h";
 * \endcode
 * by
 * \code
 *   include "myrngMT.h";
 * \endcode
 * \par History
 *---------------------------------------------------------------------------\n
 * 2006-11-18: 1.0 completed                                                 \n
 * 2006-12-05: Version 1.1 now involves a cpp file - neccessary because of
 *             instance creation                                             \n
 * 2007-12-15: Version 1.1.1 added exponential, beta and gamma
 *             distribution (mm)                                             \n
 * 2008-02-17: Now you can choose between myrngMT and myrngWELL (mm)         \n
 *---------------------------------------------------------------------------
 * \par References
 * - The Marsenne Twister algorithm is based on the code by Makoto Matsumoto
 *   and Takuji Nishimura. http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/emt
 * - The WELL algorithm is based on the code in F. Panneton, P. L'Ecuyer,
 *   and M. Matsumoto, "Improved Long-Period Generators Based on Linear Recurrences
 *   Modulo 2", ACM Transactions on Mathematical Software, 32, 1 (2006), 1-16.
 * - Generation of random variates is based on Law and Kelton:
 * "Simulation, Modeling and Analysis".
 * - The generation of the gamma variates is based on
 * George Marsaglia and Wai Wan Tsang:
 * "A Simple Method for Generating Gamma Variables", ACM TOMS Vol.26,2000.
 * \par Lincense and Copyright
 *   Marsenne Twister algorithm: Copyright (C) 1997 - 2002, Makoto Matsumoto
 *   and Takuji Nishimura, All rights reserved.\n
 *   Redistribution and use in source and binary forms, with or without
 *   modification, are permitted provided that the following conditions
 *   are met:\n
 *   1. Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.\n
 *   2. Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the distribution.\n
 *   3. The names of its contributors may not be used to endorse or promote
 *   products derived from this software without specific prior written
 *   permission.\n\n
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *   A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 *   CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 *   EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 *   PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 *   PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 *   LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 *   NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 *   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/********* M Y  R A N D O M  N U M B E R  G E N E R A T O R *****************/
class CMyRng
{
	//----------------- CONSTRUCTION / DESTRUCTION -------------------------------
public:
	/// Constructor.
	CMyRng();
	/// Destructor.
	~CMyRng();

	//----------------- HIGH LEVEL USER FUNCTIONS --------------------------------
public:
	/// Sets the seed.
	void Seed(unsigned long int s);
	/// Returns the seed.
	unsigned long int getSeed() const;
	/// Returns the name of the RNG.
	const char* getName();

	//----------------- RANDOM NUMBER GENERATION ---------------------------------
private:
	/// The Random Number Generator.
	double BaseRand();

	//----------------- RANDOM NUMBER GENERATION ---------------------------------
public:
	/// Uniform distribution on the open interval (0,1).
	double Uniform01();
	/// Uniform distribution on the interval [from,to).
	double FromTo(double from, double to);
	/// Discrete uniform distribution in [1,2,...,faces].
	int Dice(int faces = 6);
	/// Discrete uniform distribution in [from,from+1,...,to].
	int IntFromTo(int from, int to);
	/// Returns TRUE with probability chance.
	bool Chance(double chance = 0.5);
	/// Choose between n choices numbered 0,1,...n-1.
	int Choices(double* prob, int numberOfChoices);
	/// Normal(0,1) distribution with polar method.
	double Normal01Polar();
	/// Gaussian distribution with polar method.
	double GaussianPolar(double mean, double variance);

	/// Exponential distribution.
	double Exponential(double mean);
	/// Gamma distribution.
	double Gamma(double shape, double scale); // Mean: shape*scale !!
	/// Beta distribution.
	double Beta(double shape1, double shape2);

	//----------------- D I A G N O S T I C S ------------------------------------
public:
	/// @name Test Functions
	/// Functions for Diagnostics
	//@{
	void AllTests(); //!< Run all tests
	void TestUniform01(); //!< Test Uniform01
	void TestFromTo(); //!< Test FromTo
	void TestDice(); //!< Test Dice
	void TestIntFromTo(); //!< Test IntFromTo
	void TestChance(); //!< Test Chance
	void TestChoices(); //!< Test Choices
	void TestNormal01Polar(); //!< Test Normal01Polar
	void TestGaussianPolar(); //!< Test GaussianPolar
	void TestExponential(); //!< Test Exponential
	void TestGamma(); //!< Test Gamma
	void TestBeta(); //!< Test Beta
	//@}


	//----------------- PRIVATE  VARIABLES ---------------------------------------
private:
	// Polar Method static variable
	bool polar_hasvariate; // A random number is still stored
	double polar_variate; // The random number

	unsigned long int seed_; // the initial seed

	//----------------- WELL  VARIABLES ------------------------------------------
private:
	unsigned int z0, z1, z2, state_i;
	unsigned int STATE[32];
};

extern CMyRng rng;
#endif
