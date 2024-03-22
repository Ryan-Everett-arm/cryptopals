#include <stdlib.h>
#include <stdint.h>

/* xor two equal length byte arrays. */
void xor_bytes(uint8_t* in1, uint8_t* in2, uint8_t* out, size_t len){
    for (size_t i = 0; i < len; i ++) {
        out[i] = in1[i] ^ in2[i];
    }
}
