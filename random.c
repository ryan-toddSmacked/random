#include "random.h"
#include <float.h>

//*********************************
//*      Generator formula        *
//*      Schrage's method         *
//*********************************
//*                               *
//*   z = a (z % q) - r (z / q)   *
//*   if (z < 0) z = z + m        *
//*                               *
//*   q = m / a                   *
//*********************************



//***********************
//* Generator Constants *
//***********************

// These values were described as "good" enough for a
//  generator function to return pseudo-random values.
// Two generators functions are used to increase the
//  period before repetition.

#define M1 (2147483563)
#define A1 (40014)
#define Q1 (M1 / A1)
#define R1 (12211)

#define M2 (2147483399)
#define A2 (40692)
#define Q2 (M2 / A2)
#define R2 (3791)

#define SHUFFLE_TABLE_LEN     (255)
#define EPS                   (DBL_EPSILON)
#define RANDMAX_DOUBLE        (1.0 - EPS)
#define LOAD_TABLE_ITERATIONS (56)

static volatile int32_t ISLOADED = 0;
static volatile int32_t SEED1 = 0;
static volatile int32_t TABLE[SHUFFLE_TABLE_LEN] = { 0 };
static volatile int32_t SEED2 = 0;
static volatile int32_t INT32RAND = 0;

void setSeed(int32_t _seed)
{
    SEED1 = _seed;
    ISLOADED = 0;
}

double uniform()
{

    int32_t j = 0;   

    double randValue = 0.0;

    if (SEED1 <= 0 || !ISLOADED)
    {
        if (SEED1 == 0)
            SEED1 = 1;

        if (SEED1 < 0)
            SEED1 = -SEED1;

        for (j = 0; j < LOAD_TABLE_ITERATIONS; j++)
        {
            SEED1 = A1 * (SEED1 % Q1) - SEED1 * R1 / Q1;
            if (SEED1 < 0)
                SEED1 += M1;
        }

        for (j = 0; j < SHUFFLE_TABLE_LEN; j++)
        {
            SEED1 = A1 * (SEED1 % Q1) - SEED1 * R1 / Q1;
            if (SEED1 < 0)
                SEED1 += M1;

            if (j < SHUFFLE_TABLE_LEN)
                TABLE[j] = SEED1;
        }

        INT32RAND = TABLE[0];
        SEED2 = SEED1;
        ISLOADED = 1;
    }


    SEED1 = A1 * (SEED1 % Q1) - SEED1 * R1 / Q1;
    if (SEED1 < 0)
        SEED1 += M1;

    SEED2 = A2 * (SEED2 % Q2) - SEED2 * R2 / Q2;
    if (SEED2 < 0)
        SEED2 += M2;

    j = INT32RAND % SHUFFLE_TABLE_LEN;
    INT32RAND = TABLE[j] - SEED2;
    TABLE[j] = SEED1;

    if (INT32RAND < 1)
        INT32RAND += (M1 - 1);

    randValue = (1.0 / M1) * INT32RAND;

    if (randValue > RANDMAX_DOUBLE)
        return RANDMAX_DOUBLE;

    return randValue;
}


int32_t randRange(int32_t lower, int32_t upper)
{
    const double val = uniform();
    int32_t diff;
    if (lower > upper)
    {
        int32_t temp = lower;
        lower = upper;
        upper = temp;
    }

    diff = upper - lower;

    return lower + (int32_t)(val * diff);
}




