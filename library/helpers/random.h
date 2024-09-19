#include "mbedtls/entropy.h"
#include <stdio.h>

/**
 * Random number generation library which wraps around
 * MbedTLS's entropy library.
**/

/*
 * Initialise the random number generator.
*/
void rand_init();

/*
 * Fill a buffer out with num independent random bytes.
 */
void gen_rand_bytes(uint8_t* out, size_t num);

/*
 * Generate a uniform random int s.t. low <= n <= high.
 */
unsigned int gen_rand_in_range(unsigned int low, unsigned int high);