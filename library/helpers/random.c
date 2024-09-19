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
 * Generate a uniform random int s.t. low <= n <high.
 * Sketch proof of uniformity:
 * P(x returned) = Exists N s.t. P((rK rejected forall K<N) AND P((rN % range == x))
 *                             = P((rN rejected forall n))   *  P((rN % range == x))
 * (By independance, assuming uniformity of underlying randomness).
 * Now, notice that P((rN % range == x)) = 1/range.
 * Therefore, P(x returned at step N) = 1/range * P(rK rejected forall K<N).
 * Which is independant of x.
 * Therefore, forall i,j in range, P(i returned) == P(j returned). (1)
 * P(no return) = lim k->inf: P(rejction at step n)^k = 0. (2)
 * (1) ^ (2) => P(x (in range) returned) = 1/range.
 * => Function is uniform.
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

