#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <formatters.h>
#include <arithmatic.h>
#include <printers.h>
#include <random.h>
#include <crypto.h>
#include <string.h>

/*
 * Construct a 4 block plaintext where blocks 2 and 3 are the same.
 * In ECB mode, blocks 2 and 3 will still be the same.
 */

int encryption_oracle(uint8_t* in, size_t inLen, uint8_t* out, size_t* outLen) {
    /* Generate random key. */
    uint8_t key[16];
    gen_rand_bytes(key, 16);

    //Add pre and post bytes to the plaintext.
    uint8_t prePad[10];
    uint8_t postPad[10];
    uint8_t* plaintext = malloc(26 + inLen + 16);
    gen_rand_bytes(key, 16);
    int numBytesBefore = 5 + gen_rand_in_range(0,5);
    int numBytesAfter = 5 + gen_rand_in_range(0,5);
    gen_rand_bytes(prePad + (6 - numBytesBefore), numBytesBefore);
    gen_rand_bytes(postPad, numBytesAfter);

    /* Gen Full plaintext := prePad[nBB,10]::in::postPad[0,nBA]::PKCS7pad. */
    int i = 0;
    while (i < numBytesBefore) {
        plaintext[i] = prePad[i + (6 - numBytesBefore)];
        i += 1;
    }
    int j = 0;
    while (j < inLen) {
        plaintext[i] = in[j];
        i += 1;
        j += 1;
    }
    j = 0;
    while (j < numBytesAfter) {
        plaintext[i] = postPad[j];
        j += 1;
        i += 1;
    }
    pad_pkcs7(plaintext, plaintext, numBytesBefore + inLen + numBytesAfter, 16, outLen);

    unsigned int useECB = gen_rand_in_range(0,2);
    if (useECB) {
        encrypt_ecb_aes_128(plaintext, *outLen, key, 16, out);
    } else {
        /* Gen random IV. */
        uint8_t iv[16];
        gen_rand_bytes(iv, 16);
        encrypt_cbc_aes_128(plaintext, *outLen, key, 16, iv, out);
    }
    free(plaintext);
    return useECB;
}

int main() {
    rand_init();
    uint8_t* in = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
    size_t inLen = 48;
    uint8_t out[26];
    size_t outLen;
    for (int i = 0; i < 10000; i ++) {
        int useECB = encryption_oracle(in, inLen, out, &outLen);
        if (string_equal(out + 16, out + 32, 16)){
            if (useECB != 1) {
                printf("Extremely lucky coincidence!");
            }
        } else {
            if (useECB != 0) {
                printf("ERROR!\n");
                break;
            }
        }
    }
}