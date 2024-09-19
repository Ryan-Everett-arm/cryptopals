#include "mbedtls/entropy.h"
#include <stdio.h>

mbedtls_entropy_context entropy;

/*
 * Initialise the random number generator.
 */
void rand_init() {
    mbedtls_entropy_init(&entropy);
}

/*
 * Fill a buffer out with num independent uniform random bytes.
 */
void gen_rand_bytes(uint8_t* out, size_t num) {
    int rc = mbedtls_entropy_func(&entropy, out, num);
    if (rc != 0) {
        printf("\nERROR: Failed to generate random data.\n");
    }
}

/*
 * Generate a uniform (not yet proven!) random int s.t. low <= n <high.
 */
unsigned int gen_rand_in_range(unsigned int low, unsigned int high) {
    unsigned int range = high - low;
    unsigned int desiredRange = INT_MAX - INT_MAX % range;
    uint8_t buf[4];
    if (range < 2) {
        return low;
    }
    if (range > INT_MAX / 2) {
        printf("ERROR: Cannot generate with such a large range. ");
    }

    while (1) {
        /* Generate a random int between 0 and INT_MAX. */
        gen_rand_bytes(buf, 4);
        unsigned int randInt = 0;
        for (int i = 0; i < 4; i ++) {
            randInt += buf[i] << (8 * i);
        }

        /* Succeed if randInt is within the desired range. */
        if (randInt < desiredRange) {
            return low + (randInt % range);
        }
    }
}

