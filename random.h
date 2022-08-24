
#ifndef __RANDOM_C_DECL_H
#define __RANDOM_C_DECL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/**
 * @brief Set the seed for the random number generators.
 * 
 * @param _seed Valid seed values [0x00000000 - 0xFFFFFFFF].
 */
void setSeed(int32_t _seed);

/**
 * @brief Return random double value.
 * 
 * @return double - Random value, [0, 1).
 */
double uniform();

/**
 * @brief Return random 32 bit signed integer.
 * 
 * @param lower Lower bound, inclusive.
 * @param upper Upper bound, exclusive.
 * @return int32_t - Random value, [lower, upper).
 */
int32_t randRange(int32_t lower, int32_t upper);




#ifdef __cplusplus
}
#endif

#endif

