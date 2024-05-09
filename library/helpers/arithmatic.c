#include <stdlib.h>
#include <stdint.h>

/* xor two equal length byte arrays. */
void xor_bytes(uint8_t* in1, uint8_t* in2, uint8_t* out, size_t len){
    for (size_t i = 0; i < len; i ++) {
        out[i] = in1[i] ^ in2[i];
    }
}

void xor_bytes_with_key(uint8_t* bytes, uint8_t key, uint8_t* out, size_t len) {
    for (size_t i = 0; i < len; i++){
        out[i] = bytes[i] ^ key;
    }
}

/* Return the number of differing bits between two bytes. */
int byte_distance(uint8_t b1, uint8_t b2) {
    int d = 0;
    uint8_t diff = b1 ^ b2;

    /* The byte distance is the number of set bits in diff; calculate this. */
    for (int i = 0; i < 8; i++) {
        if (diff % 2) {
            d ++;
        }
        diff = diff >> 1;
    }
    return d;
}

/* Return 1 if the contents of a and b are the same, 0 otherwise. */
int string_equal(char* a, char* b, size_t len) {
    for (size_t i = 0; i < len; i ++) {
        if (a[i] != b[i]) {
            return 0;
        }
    }
    return 1;
}

size_t hamming_distance(uint8_t* in1, uint8_t* in2, size_t len) {
    size_t d = 0;

    /* For each byte, add the number of differing bits. */
    for (int i = 0; i < len; i ++) {
        d += byte_distance(in1[i], in2[i]);
    }
    return d;
}
