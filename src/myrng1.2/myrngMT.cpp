#include "myrngMT.h"

/****************************************************************************\
* myrng  by  Thilo Gross and Marton Morvai                                 *
* -- s. Header File for more info                                           *
\****************************************************************************/

//--------------------------- DESTRUCTOR -------------------------------------
CMyRng::~CMyRng() 
{
}

/****************************************************************************\
* USER FUNCTIONS                                                             *
\****************************************************************************/

// -------------------------- getName ----------------------------------------
const char* CMyRng::getName() 
/**
 * Example:
 * \code
 *   #include "myrngWELL.h"
 *   printf("Using %s.\n",rng.getName()); 
 *   // Output: Using WELL1024a.
 * \endcode
 */
{ 
    return "MT19937a"; 
}


/****************************************************************************\
* RANDOM  NUMBER  GENERATION                                                 *
\****************************************************************************/

// -------------------------- Uniform01 --------------------------------------
double CMyRng::Uniform01()
/**
 * Example:
 * \code
 *   #include "myrngWELL.h"
 *   double randomNumber;
 *   randomNumber=rng.Uniform01();
 *   if (randomNumber==0 || randomNumber==1)
 *       printf("huh!"); // This won't happen!
 * \endcode
 * \return Uniformly distributed random number \f$ u \sim U(0,1). \f$ 
 */
{
    return BaseRand();
}

//--------------------------- FromTo -----------------------------------------
double CMyRng::FromTo(double from,double to)
/**
 * Transforms the return value of the RNG linearly.
 * Example:
 * \code
 *   #include "myrngWELL.h"
 *   double randomNumber;
 *   randomNumber=rng.FromTo(1,9.9);
 *   if (randomNumber==9.9)
 *       printf("huh!"); // This won't happen!
 *   if (randomNumber==1)
 *       printf("Why not?"); // But this could!
 * \endcode
 * \param from is the start of the interval.
 * \param to   is the end of the interval.
 * \return A real number on the Interval [from, to).
 */
{
    return from+(to-from)*BaseRand();
}

//---------------------------- Chance ----------------------------------------
bool CMyRng::Chance(double chance) 
/**
 * Example:
 * \code
 *   #include "myrngWELL.h"
 *   bool myChance;
 *   myChance=rng.Chance(0.8);
 *   if (myChance) printf("Go to the cinema!");
 *   else printf("Stay at home!");
 * \endcode
 * \param chance The probability to return TRUE. Has to be in the open 
 * interval (0,1).
 * \return TRUE if Uniform01() <= chance \n 
 *         FALSE if Uniform01() > chance
 */
{
    if (BaseRand()<=chance) return true;
    else return false;
}

//---------------------------- Dice ------------------------------------------
int CMyRng::Dice(int faces) 
/**
 * Simulates a dice roll.
 * Example:
 * \code
 *   #include "myrngWELL.h"
 *   int classicDice;
 *   classicDice=rng.Dice();
 * \endcode
 * \param faces are the faces of the virtual dice. The default value is 6.
 * \return An integer number, which is a member of the set {1,2...,faces}.
 */
{
    return (1+(int)(BaseRand()*faces));
}

//---------------------------- IntFromTo -------------------------------------
int CMyRng::IntFromTo(int from,int to)
/**
 * Same as Dice(). But the lower bound can be different from 1.
 * Example:
 * \code
 *   #include "myrngWELL.h"
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
{
    return from+(int)((double)(to-from+1)*BaseRand());
}

//---------------------------- Choices ---------------------------------------
int CMyRng::Choices(double* prob, int numberOfChoices) 
/**
 * k is chosen with the probability prob[k].\n
 * Example:
 * \code
 * #include myrng.h
 * double prob[3]={0.2, 0.2, 0.6};
 * int result;
 * result=rng.Choices(prob,3);
 * printf("Case %d was chosen by the RNG.",result);
 * \endcode
 * \param prob is an array of double values of arbitrary length. <B>The 
 * sum of all elements has to be 1.</B> 
 * \param numberOfChoices is the length of the prob array.
 * \return An integer value between 0 and n-1
 */
{  
    int ret=0;
    double x=BaseRand();
    while (x>0 && numberOfChoices>0)
    {
        numberOfChoices--;
        x-=prob[ret];
        ret++;
    }
    return (ret-1);
}

//---------------------------- Normal01Polar ---------------------------------
double CMyRng::Normal01Polar() 
/**
 * This is a variant of the Box-Muller method, but it is faster since it 
 * avoids the calculation of the trigonometric functions. \n 
 * Example:
 * \code
 *   #include "myrngWELL.h"
 *   double randomNumber;
 *   randomNumber=rng.Normal01Polar();
 * \endcode
 * Probability density function:
 * \f[ f(x)=\frac{1}{\sqrt{2\pi}} \exp{\left( -\frac12 x^2\right) }  \f]
 * \return A gaussian distributed random number \f$ u\sim N(0,1) \f$.
 */
{
    if (polar_hasvariate) 
    {
        polar_hasvariate=false;
        return polar_variate;
    }
    else
    {
        double V1,V2,U1,U2;
        double W=2;
        while (W>1)
        {
            U1=BaseRand();
            U2=BaseRand();
            V1=2.0*U1-1.0;
            V2=2.0*U2-1.0;
            W=V1*V1+V2*V2;
        }
        double Y=sqrt((-2.0*log(W))/W);
        polar_hasvariate=true;
        polar_variate=V1*Y;
        return V2*Y;
    }
}


//---------------------------- GuassianPolar ---------------------------------
double CMyRng::GaussianPolar(double mean,double variance) 
/**
 * This is a variant of the Box-Muller method, but it is faster since it 
 * avoids the calculation of the trigonometric functions. \n 
 * Example:
 * \code
 *   #include "myrngWELL.h"
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
{ 
    return mean+sqrt(variance)*Normal01Polar();
}

//---------------------------- Exponential -----------------------------------
double CMyRng::Exponential(double mean)
/**
 * Uses the logarithm method:
 * Let \f$ U \sim U(0,1)\f$. Then \f$ T=-mean \cdot \ln{U} \f$
 * is exponentially distributed.\n
 * Example:
 * \code
 * #include "myrngWELL.h"
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
{
    assert(mean > 0);
    double U=BaseRand();
    return -mean*log(U);
}

//---------------------------- Gamma -----------------------------------------
double CMyRng::Gamma(double shape, double scale)
/**
 * Uses an acceptence-rejection algorithm. 
 * See GEORGE MARSAGLIA and WAI WAN TSANG 
 * "A Simple Method for Generating Gamma Variables", ACM TOMS Vol.26,2000.
 * Probability density function:
 * \f[ f(x) = x^{shape-1}  \frac{scale^{shape} \, e^{-scale\,x} }{\Gamma(shape)}  \ \mathrm{for}\ x > 0 \,\!. \f]
 * \note \f$ mean=shape \cdot scale \f$
 */
{
    double d,c,x,v,u,alpha;
    if (shape<1) alpha=shape+1.;
    else alpha=shape;
    d=alpha-1./3.; 
    c=1./sqrt(9.*d);
    
    do 
    {
        do 
        {
            x=Normal01Polar();
            v= 1.+ c*x;
        } while(v<=0.);
        v=v*v*v; 
        u=Uniform01();
    } while ( (u>1.-.0331*(x*x)*(x*x)) && (log(u)>0.5*x*x+d*(1.-v+ log(v))));

    if (shape==alpha) 
        return scale*d*v;
    else 
    {
        u=Uniform01();
        return pow(u,1./shape)*v*d*scale;
    }
}


//---------------------------- Beta ------------------------------------------
double CMyRng::Beta(double shape1, double shape2) 
/**
 * Probability density function:
 * \f[ f(x)=\frac{\Gamma(shape1+shape2)}{\Gamma(shape1)\Gamma(shape2)}\, x^{shape1-1}(1-x)^{shape2-1}\! \f]
 * \note
 * \f$ mean=\frac{shape1}{shape1+shape2} \f$
 */
{
    double Y1=Gamma(shape1,1.0);
    double Y2=Gamma(shape2,1.0);

    return Y1/(Y1+Y2);
}

/****************************************************************************\
* Testing                                                                    *
\****************************************************************************/

//---------------------------- AllTests --------------------------------------
void CMyRng::AllTests()
{
    printf("\n\nRunning All RNG Tests ============================== \n\n");
    TestUniform01();
    TestFromTo();
    TestDice();
    TestIntFromTo();
    TestChance();
    TestChoices();
    TestNormal01Polar();
    TestGaussianPolar();
    TestExponential();
    TestGamma();
    TestBeta();
    printf("RNG Tests Finished ================================= \n\n");
}

//---------------------------- TestUniform01----------------------------------
void CMyRng::TestUniform01()
{
    printf("  Testing Uniform01 --------------------------------\n");
    unsigned int x[10];
    double largest=0;  
    double smallest=0;
    int i;
    for (i=0;i<10;i++)    x[i]=0;
    long t1=time(0);
    for (i=0;i<1e7;i++)
    {
        double res=Uniform01();
        if (res>largest) largest=res;
        if (res<smallest) smallest=res;
        int z=(int)(res*10.0);
        x[z]++;
    }
    long t2=time(0);
    printf("    Largest value:  %1.2lf [1.00]\n",largest);
    printf("    Smallest value: %1.2lf [0.00]\n",smallest);
    for (i=0;i<10;i++)
    {
        printf("    %1.1lf...%1.1lf: %1.1lf%% [10.0%%]\n",
            (double)(i)/10.0,(double)(i+1)/10.0,((double)x[i]/1e7)*100.0);
    }
    printf("    Time: %lds\n",t2-t1);
    printf("\n");
}

//---------------------------- TestFromTo ------------------------------------
void CMyRng::TestFromTo()
{
    printf("  Testing FROM-TO ----------------------------------\n");
    double from=-Uniform01()*5;
    double to=Uniform01()*5;
    printf("    Test task: From %1.3lf to %1.3lf\n",from,to);
    double lo=10;
    double hi=-10;
    int i;
    int x[10];
    for (i=0;i<10;i++) x[i]=0;
    long t1=time(0);
    for (i=0;i<1e7;i++)
    {
        double res=FromTo(from,to);
        if (res>hi) hi=res;
        if (res<lo) lo=res;
        int z=(int)((res-from)/(to-from)*10.0);
        x[z]++;
    }
    long t2=time(0);
    printf("    Largest value:  %+1.3lf [%+1.3lf]\n",hi,to);
    printf("    Smallest value: %+1.3lf [%+1.3lf]\n",lo,from);
    for (i=0;i<10;i++)
    {
        printf("    %+1.3lf...%+1.3lf: %1.1lf%% [10.0%%]\n",
            from+(double)(i)*(to-from)/10.0,
            from+(double)(i+1)*(to-from)/10.0,((double)x[i]/1e7)*100.0);
    }
    printf("    Time: %lds\n",t2-t1);
    printf("\n");
}

//---------------------------- TestDice --------------------------------------
void CMyRng::TestDice()
{
    printf("  Testing DICE ------------------------------------\n");
    int x[10];
    int i;
    for (i=0;i<10;i++) x[i]=0;
    long t1=time(0);
    for (i=0;i<1e7;i++)
    {
        int q=Dice(10)-1;
        x[q]++;
    }
    long t2=time(0);
    for (i=0;i<10;i++)
    {
        printf("    %2d: %1.1lf%% [10.0%%]\n",i+1,((double)x[i]/1e7)*100.0);
    }
    printf("    Time: %lds\n",t2-t1);
    printf("\n");
}

//---------------------------- TestIntFromTo ---------------------------------
void CMyRng::TestIntFromTo()
{
    printf("  Testing INTEGER FROM-TO -------------------------\n");
    int x[11];
    int from=-Dice(5);
    int to=Dice(5);
    printf("    Test task: From %d to %d\n",from,to);
    int i;
    for (i=0;i<11;i++) x[i]=0;
    long t1=time(0);
    for (i=0;i<1e7;i++)
    {
        int q=IntFromTo(from,to);
        q-=from;
        x[q]++;
    }
    long t2=time(0);
    for (i=0;i<(to-from)+1;i++)
    {
        printf("    %2d: %2.1lf%% [%2.1lf%%]\n",
            i+from,((double)x[i]/1e7)*100.0,100.0/(double)(to-from+1));
    }
    printf("    Time: %lds\n",t2-t1);
    printf("\n");
}

//---------------------------- TestChance ------------------------------------
void CMyRng::TestChance()
{
    printf("  Testing CHANCE ----------------------------------\n");
    int x[10];
    double chance[10];
    int i;
    for (i=0;i<10;i++) 
    {
        x[i]=0;
        chance[i]=FromTo(0.1,0.999);
    }
    long t1=time(0);
    for (int j=0;j<10;j++)
    {
        for (i=0;i<1e6;i++)
        {
            if (Chance(chance[j])) x[j]++;
        }
    }
    long t2=time(0);
    for (i=0;i<10;i++)
    {
        printf("    Chance %2.1lf: Success %2.1lf%% [%2.1lf%%]\n",
            100.0*chance[i],((double)x[i]/1e6)*100.0,100.0*chance[i]);
    }
    printf("    Time: %lds\n",t2-t1);
    printf("\n");
}

//---------------------------- TestChoices -----------------------------------
void CMyRng::TestChoices()
{
    printf("  Testing CHOICES ---------------------------------\n");
    int x[9];
    int numchoice=4+Dice(5);
    double chance[9];
    int i;
    double sum=0;
    for (i=0;i<numchoice;i++) 
    {
        x[i]=0;
        chance[i]=Uniform01()+sum;
        sum+=chance[i];
    }
    for (i=0;i<numchoice;i++)
    {
        chance[i]/=sum;
    }
    long t1=time(0);
    for (i=0;i<1e7;i++)
    {
        int q=Choices(chance,numchoice);
        x[q]++;
    }
    long t2=time(0);
    for (i=0;i<numchoice;i++)
    {
        printf("    Choice %d (%3.1lf%%): %3.1lf%% [%3.1lf%%]\n",i,
            100.0*chance[i],((double)x[i]/1e7)*100.0,100.0*chance[i]);
    }
    printf("    Time: %lds\n",t2-t1);
    printf("\n");
}

//---------------------------- TestNormal01Polar -----------------------------
void CMyRng::TestNormal01Polar()
{
    printf("  Testing Normal 01 Polar Method -------------------\n");
    double erf[11];
    erf[0]=0.6; erf[1]=1.7; erf[2]=4.4; erf[3]=9.2; erf[4]=15.0; 
    erf[5]=38.3; erf[10]=0.6; erf[9]=1.7; erf[8]=4.4; erf[7]=9.2; 
    erf[6]=15.0;
    unsigned int x[11];
    double sum=0;
    double sumsq=0;
    int testset=10000000;
    int i;
    for (i=0;i<11;i++)    x[i]=0;
    long t1=time(0);
    for (i=0;i<testset;i++)
    {
        double res=Normal01Polar();
        int z=(int)(res*2.0)+5;
        if (z<0) z=0;
        if (z>10) z=10;
        sum+=res;
        sumsq+=res*res;
        x[z]++;
    }
    long t2=time(0);
    double mean=sum/testset;
    double meansq=sumsq/testset;
    double sqmean=mean*mean;
    double var=meansq-sqmean;
    printf("    Mean:     %1.2lf [0.00]\n",mean);
    printf("    Variance: %1.2lf [1.00]\n",var);
    printf("    -inf...-2.5: %2.1lf%% [0.6%%]\n",
            ((double)x[0]/testset)*100.0);
    for (i=1;i<10;i++)
    {
        printf("    %+1.1lf...%+1.1lf: %2.1lf%% [%2.1lf%%]\n",
            (double)(i-5)/2.0-0.5,(double)(i-5)/2.0+0.5,
            ((double)x[i]/testset)*100.0,erf[i]);
    }
    printf("    +2.5...+inf: %2.1lf%% [0.6%%]\n",
            ((double)x[10]/testset)*100.0);
    printf("    Time: %lds\n",t2-t1);
    printf("\n");
}

//---------------------------- TestGaussianPolar -----------------------------
void CMyRng::TestGaussianPolar()
{
    printf("  Testing Gaussian Polar Method --------------------\n");
    double targetmean=FromTo(-10,10);
    double targetvar=FromTo(0.001,1);
    printf("    Test task: Mean %2.2lf Variance %1.2lf\n",
            targetmean,targetvar);
    double sum=0;
    double sumsq=0;
    int testset=10000000;
    int i;
    long t1=time(0);
    for (i=0;i<testset;i++)
    {
        double res=GaussianPolar(targetmean,targetvar);
        sum+=res;
        sumsq+=res*res;
    }
    long t2=time(0);
    double mean=sum/testset;
    double meansq=sumsq/testset;
    double sqmean=mean*mean;
    double var=meansq-sqmean;
    printf("    Mean:     %2.2lf [%2.2lf]\n",mean,targetmean);
    printf("    Variance: %2.2lf [%2.2lf]\n",var,targetvar);
    printf("    Time: %lds\n",t2-t1);
    printf("\n");
}

//---------------------------- TestExponential -------------------------------
void CMyRng::TestExponential()
{
    printf("  Testing Exponential --------------------\n");
    double targetmean=FromTo(0.1,10);
    double targetvar=targetmean*targetmean;
    printf("    Test task: Mean %2.2lf Variance %2.2lf\n",
            targetmean,targetvar);
    double sum=0;
    double sumsq=0;
    int testset=(int)1e7;
    int i;
    long t1=time(0);
    for (i=0;i<testset;i++)
    {
        double res=Exponential(targetmean);
        sum+=res;
        sumsq+=res*res;
    }
    long t2=time(0);
    double mean=sum/testset;
    double meansq=sumsq/testset;
    double sqmean=mean*mean;
    double var=meansq-sqmean;
    printf("    Mean:     %2.2lf [%2.2lf]\n",mean,targetmean);
    printf("    Variance:     %2.2lf [%2.2lf]\n",var,targetvar);
    printf("    Time: %lds\n",t2-t1);
    printf("\n");
}

//---------------------------- TestGamma -------------------------------------
void CMyRng::TestGamma()
{
    double shape;
    double scale;
    printf("  Testing Gamma --------------------\n");
    for (int j=0; j<2; j++) {
    scale=FromTo(0.1,2);
    if (j==0)
      shape=FromTo(0.1,1);
    if (j==1)
      shape=FromTo(1,3);
    double targetmean=scale*shape;
    double targetvar=targetmean*scale;

    if (j==0)
        printf("    Test task: Mean %2.2lf, Variance %2.2lf for shape < 1 (shape %2.2lf scale %2.2lf)\n", targetmean,targetvar,shape,scale);
    if (j==1)
        printf("    Test task: Mean %2.2lf, Variance %2.2lf for shape >= 1 (shape %2.2lf scale %2.2lf)\n",targetmean,targetvar,shape,scale);

    double sum=0;
    double sumsq=0;
    int testset=(int) 1e7;
    long t1=time(0);
    for (int i=0;i<testset;i++)
    {
        double res=Gamma(shape,scale);
        sum+=res;
        sumsq+=res*res;
    }
    long t2=time(0);
    double mean=sum/testset;
    double meansq=sumsq/testset;
    double sqmean=mean*mean;
    double var=meansq-sqmean;
    printf("    Mean:     %2.2lf [%2.2lf]\n",mean,targetmean);
    printf("    Variance:     %2.2lf [%2.2lf]\n",var,targetvar);
    printf("    Time: %lds\n",t2-t1);
    printf("\n");
     }
}

//---------------------------- TestBeta --------------------------------------
void CMyRng::TestBeta()
{
    printf("  Testing Beta --------------------\n");
    double shape1=FromTo(0.1,3);
    double shape2=FromTo(0.1,3);
    double targetmean=shape1/(shape2+shape1);
    double targetvar=(shape1*shape2)/( (shape1+shape2)*(shape1+shape2)
                      *(shape1+shape2+1.));
    printf("    Test task: Mean %2.2lf Variance %2.2lf (shape1 %2.2lf shape2 %2.2lf)\n",targetmean,targetvar,shape1,shape2);
    double sum=0;
    double sumsq=0;
    int testset=(int)1e7;
    int i;
    long t1=time(0);
    for (i=0;i<testset;i++)
    {
        double res=Beta(shape1,shape2);
        sum+=res;
        sumsq+=res*res;
    }
    long t2=time(0);
    double mean=sum/testset;
    double meansq=sumsq/testset;
    double sqmean=mean*mean;
    double var=meansq-sqmean;
    printf("    Mean:     %2.2lf [%2.2lf]\n",mean,targetmean);
    printf("    Variance:     %2.2lf [%2.2lf]\n",var,targetvar);
    printf("    Time: %lds\n",t2-t1);
    printf("\n");
}

/****************************************************************************\
* Mersenne Twister specific Functions:                                       *
* 1. Constructor                                                             *
* 2. Seed                                                                    *
* 3. BaseRand                                                                *
\****************************************************************************/
//--------------------------- CONSTRUCTOR MT----------------------------------
CMyRng::CMyRng()
/**
 * The constrcutor doesn't need any paramater. It calls the Seed() function 
 * with the current time in seconds. If you want to seed the RNG 
 * manually, please use the Seed() function.
 * @see Seed(unsigned long int s)
 */
{
    // Long has to be at least 32 bits!
    assert(sizeof(long)>=4);
    CMyRng::mti=624+1;
 //   unsigned long CMyRng::mt[624];
    CMyRng::Seed( (unsigned long)time(0)) ;
}

//--------------------------- Seed MT ----------------------------------------
void CMyRng::Seed(unsigned long int s) 
/**
 * After the RNG has been seeded, this function generates 50.000
 * random numbers to let the RNG recover at least a little bit from a
 * bad init state.
 * Example:
 * \code
 *  #include "myrngWELL.h"
 *  rng.Seed(5489UL);
 * \endcode
 * \param s has to be an unsigned long.
 */ 
{
    CMyRng::mt[0]= s & 0xffffffffUL;
    for (CMyRng::mti=1; CMyRng::mti<624; CMyRng::mti++) 
    {
        CMyRng::mt[CMyRng::mti] = (1812433253UL * (
            CMyRng::mt[CMyRng::mti-1] ^ (CMyRng::mt[CMyRng::mti-1] 
            >> 30)) + CMyRng::mti); 
        // See Knuth TAOCP Vol2. 3rd Ed. P.106 for multiplier. 
        // In the previous versions, MSBs of the seed affect   
        // only MSBs of the array CMyRng::mt[].              
        // 2002/01/09 modified by Makoto Matsumoto             
        CMyRng::mt[CMyRng::mti] &= 0xffffffffUL;
        // for >32 bit machines 
    }
}
double CMyRng::BaseRand()
{
/**
 * This generator is an implementation of MT19937. 
 * For more information visit 
 * http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/emt.html
 */
  unsigned long y;
  static unsigned long mag01[2]={0x0UL, 0x9908b0dfUL};
  // mag01[x] = x * MATRIX_A  for x=0,1 
  
    if (CMyRng::mti >= 624) // generate N words at one time 
    {     
        int kk;

        for (kk=0;kk<624-397;kk++) 
        {
            y = (CMyRng::mt[kk]&0x80000000UL)|(CMyRng::mt[kk+1]
                     &0x7fffffffUL);
            CMyRng::mt[kk] = 
                     CMyRng::mt[kk+397] ^ (y >> 1) ^ mag01[y & 0x1UL];
        }
        for (;kk<624-1;kk++) 
        {
            y = (CMyRng::mt[kk]&0x80000000UL)|(CMyRng::mt[kk+1]
                     &0x7fffffffUL);
            CMyRng::mt[kk] = 
                     CMyRng::mt[kk+(397-624)] ^ (y >> 1) ^ mag01[y & 0x1UL];
        }
        y = (CMyRng::mt[624-1]&0x80000000UL)|(CMyRng::mt[0]&0x7fffffffUL);
        CMyRng::mt[624-1] = CMyRng::mt[397-1] ^ (y >> 1) ^ mag01[y & 0x1UL];

        CMyRng::mti = 0;
   }

    y = CMyRng::mt[CMyRng::mti++];

    /* Tempering */
    y ^= (y >> 11);
    y ^= (y << 7) & 0x9d2c5680UL;
    y ^= (y << 15) & 0xefc60000UL;
    y ^= (y >> 18);

    return (((double) y) + 0.5)*(1.0/4294967296.0); 
    /* divided by 2^32 */
}

/****************************************************************************\
* Misceleaneous Definitions                                                  *
\****************************************************************************/

CMyRng rng;            // This is my MT rng

