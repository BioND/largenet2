/**
 * Random variates generation
 *
 * @file RandomVariates.h
 */

#ifndef RANDOMVARIATES_H_
#define RANDOMVARIATES_H_

#include <cmath>
#include <cassert>

namespace myrng
{

/**
 * Random variates generation.
 *
 * Generates random variates according to different distributions
 * using the supplied random number generator @p Engine.
 *
 * @author Gerd Zschaler <gzschaler@googlemail.com>
 */
template<class Engine>
class RandomVariates: public Engine
{
public:
	/**
	 * Constructor
	 */
	RandomVariates() {}

	/**
	 *  Seed the random number generator engine.
	 *
	 *  This is an alias for Engine::seed()
	 *  @param s New seed
	 */
	void Seed(unsigned long int s)
	{
		Engine::seed(s);
	}

	/**
	 * Uniform distribution on the open interval (0,1).
	 *
	 * Example:
	 * @code
	 *   double randomNumber;
	 *   randomNumber=rng.Uniform01();
	 *   if (randomNumber==0 || randomNumber==1)
	 *       std::cout << "huh!"; // This won't happen!
	 * @endcode
	 * @return Uniformly distributed random number \f$ u \sim U(0,1). \f$
	 */
	double Uniform01()
	{
		return (*this)();
	}

	/**
	 * Uniform distribution on the interval [from,to).
	 *
	 * Transforms the return value of the RNG linearly.
	 * Example:
	 * \code
	 *   double randomNumber;
	 *   randomNumber=rng.FromTo(1,9.9);
	 *   if (randomNumber==9.9)
	 *       std::cout << "huh!"; // This won't happen!
	 *   if (randomNumber==1)
	 *       std::cout << "Why not?"; // But this could!
	 * \endcode
	 * \param from is the start of the interval.
	 * \param to   is the end of the interval.
	 * \return A real number on the Interval [from, to).
	 */
	double FromTo(double from, double to)
	{
		return from + (to - from) * Uniform01();
	}

	/**
	 * Discrete uniform distribution in [1,2,...,faces].
	 *
	 * Simulates a dice roll.
	 * Example:
	 * \code
	 *   int classicDice;
	 *   classicDice=rng.Dice();
	 * \endcode
	 * \param faces are the faces of the virtual dice. The default value is 6.
	 * \return An integer number, which is a member of the set {1,2...,faces}.
	 */
	int Dice(int faces = 6)
	{
		return (1 + (int) (Uniform01() * faces));
	}

	/**
	 * Discrete uniform distribution in [from,from+1,...,to].
	 *
	 * Same as Dice(). But the lower bound can be different from 1.
	 * Example:
	 * \code
	 *   int modernDice;
	 *   int classicDice;
	 *   modernDice=rng.Dice(2,7);
	 *   classicDice=modernDice-1;
	 * \endcode
	 * \param from is the lower bound.
	 * \param to is the upper bound.
	 * \return An integer number in the discrete interval [from,from+1,...,to].
	 * @see Dice()
	 */
	int IntFromTo(int from, int to)
	{
		return from + (int) ((double) (to - from + 1) * Uniform01());
	}

	/**
	 * Returns true with probability @p chance.
	 *
	 * Example:
	 * \code
	 *   bool myChance;
	 *   myChance=rng.Chance(0.8);
	 *   if (myChance) std::cout << "Go to the cinema!";
	 *   else std::cout << "Stay at home!";
	 * \endcode
	 * \param chance The probability to return TRUE. Has to be in the open
	 * interval (0,1).
	 * \return true if Uniform01() <= chance \n
	 *         false if Uniform01() > chance
	 */
	bool Chance(double chance = 0.5)
	{
		return (Uniform01() <= chance);
	}

	/**
	 * Choose between n choices numbered 0,1,...n-1.
	 *
	 * k is chosen with the probability prob[k].\n
	 * Example:
	 * \code
	 * double prob[3]={0.2, 0.2, 0.6};
	 * int result;
	 * result=rng.Choices(prob,3);
	 * std::cout << "Case " << result << " was chosen by the RNG.";
	 * \endcode
	 * \param prob is an array of double values of arbitrary length. <B>The
	 * sum of all elements has to be 1.</B>
	 * \param numberOfChoices is the length of the prob array.
	 * \return An integer value between 0 and n-1
	 */
	int Choices(double* prob, int numberOfChoices)
	{
		int ret = 0;
		double x = Uniform01();
		while (x > 0 && numberOfChoices > 0)
		{
			--numberOfChoices;
			x -= prob[ret];
			++ret;
		}
		return (ret - 1);
	}

	/**
	 * Normal(0,1) distribution with polar method.
	 *
	 * This is a variant of the Box-Muller method, but it is faster since it
	 * avoids the calculation of the trigonometric functions. \n
	 * Example:
	 * \code
	 *   double randomNumber;
	 *   randomNumber=rng.Normal01Polar();
	 * \endcode
	 * Probability density function:
	 * \f[ f(x)=\frac{1}{\sqrt{2\pi}} \exp{\left( -\frac12 x^2\right) }  \f]
	 * \return A gaussian distributed random number \f$ u\sim N(0,1) \f$.
	 */
	double Normal01Polar()
	{
		if (polar_hasvariate)
		{
			polar_hasvariate = false;
			return polar_variate;
		}
		else
		{
			double V1, V2, U1, U2;
			double W = 2;
			while (W > 1)
			{
				U1 = Uniform01();
				U2 = Uniform01();
				V1 = 2.0 * U1 - 1.0;
				V2 = 2.0 * U2 - 1.0;
				W = V1 * V1 + V2 * V2;
			}
			double Y = sqrt((-2.0 * log(W)) / W);
			polar_hasvariate = true;
			polar_variate = V1 * Y;
			return V2 * Y;
		}
	}

	/**
	 * Gaussian distribution with polar method.
	 *
	 * This is a variant of the Box-Muller method, but it is faster since it
	 * avoids the calculation of the trigonometric functions. \n
	 * Example:
	 * \code
	 *   double randomNumber;
	 *   int myIQ;
	 *   randomNumber=rng.GaussianPolar(100,225);
	 *   myIQ=(int) randomNumber;
	 * \endcode
	 * Probability density function:
	 * \f[ f(x)=\frac{1}{\sigma\sqrt{2\pi}} \exp{\left( -\frac12 \left(\frac{x-\mu}{\sigma}\right)^2\right) }  \f]
	 * (\f$ mean=\mu \textrm{ and } variance=\sigma^2\f$)
	 * \return A gaussian distributed random number \f$ u\sim N(mean,variance) \f$.
	 */
	double GaussianPolar(double mean, double variance)
	{
		return mean + sqrt(variance) * Normal01Polar();
	}

	/**
	 * Exponential distribution.
	 *
	 * Uses the logarithm method:
	 * Let \f$ U \sim U(0,1)\f$. Then \f$ T=-mean \cdot \ln{U} \f$
	 * is exponentially distributed.\n
	 * Example:
	 * \code
	 * // the time it takes before your next telephone call (in minutes)
	 * double nextCall;
	 * nextCall=Exponential(20);
	 * \endcode
	 * Probability density function:
	 * \f[ f(x)= \frac{1}{mean} exp({-\frac{1}{mean} x}) \textrm{ if } x \geq 0 \f]
	 * \f[ f(x)= 0 \textrm{ if } x < 0 \f]
	 * \param mean has to be greater than 0.
	 * \return An exponential distributed random number
	 * \f$ u\sim Exponential(mean) \f$.
	 */
	double Exponential(double mean)
	{
		assert(mean > 0);
		double U = Uniform01();
		return -mean * log(U);
	}

	/**
	 * Gamma distribution.
	 *
	 * Uses an acceptence-rejection algorithm.
	 * See GEORGE MARSAGLIA and WAI WAN TSANG
	 * "A Simple Method for Generating Gamma Variables", ACM TOMS Vol.26,2000.
	 * Probability density function:
	 * \f[ f(x) = x^{shape-1}  \frac{scale^{shape} \, e^{-scale\,x} }{\Gamma(shape)}  \ \mathrm{for}\ x > 0 \,\!. \f]
	 * \note \f$ mean=shape \cdot scale \f$
	 */
	double Gamma(double shape, double scale)
	{
		double d, c, x, v, u, alpha;
		if (shape < 1)
			alpha = shape + 1.;
		else
			alpha = shape;
		d = alpha - 1. / 3.;
		c = 1. / sqrt(9. * d);

		do
		{
			do
			{
				x = Normal01Polar();
				v = 1. + c * x;
			} while (v <= 0.);
			v = v * v * v;
			u = Uniform01();
		} while ((u > 1. - .0331 * (x * x) * (x * x)) && (log(u) > 0.5 * x * x + d
				* (1. - v + log(v))));

		if (shape == alpha)
			return scale * d * v;
		else
		{
			u = Uniform01();
			return pow(u, 1. / shape) * v * d * scale;
		}
	}

	/**
	 * Beta distribution.
	 *
	 * Probability density function:
	 * \f[ f(x)=\frac{\Gamma(shape1+shape2)}{\Gamma(shape1)\Gamma(shape2)}\, x^{shape1-1}(1-x)^{shape2-1}\! \f]
	 * \note
	 * \f$ mean=\frac{shape1}{shape1+shape2} \f$
	 */
	double Beta(double shape1, double shape2)
	{
		double Y1 = Gamma(shape1, 1.0);
		double Y2 = Gamma(shape2, 1.0);

		return Y1 / (Y1 + Y2);
	}

private:
	// Polar Method variables
	bool polar_hasvariate; // A random number is still stored
	double polar_variate; // The random number

};

}

#endif /* RANDOMVARIATES_H_ */
