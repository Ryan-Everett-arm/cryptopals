#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>


/* Converts a b64 byte to its printable ascii equivalent. */
char b64_to_ascii(uint8_t c) {
    if (c > 63) {
        printf("\nERROR: %d is not base64.\n", c);
        return '#';
    }

    if (c < 26) {
        /* Upper case char. */
        return c + 'A';
    }

    c = c - 26;
    if (c < 26) {
        /* Lower case char. */
        return c + 'a';
    }

    c = c - 26;
    if (c < 10) {
        /* Number. */
        return c + '0';
    }

    return (c == 10) ? '+' : '/';
}

/* hexIn must have at least 3 bytes of space, out must have 4.
 * Maps abcdefgh ijklmnop qrstuvwx.
 * to   00abcdef 00ghijkl 00mnopqr 00stuvwx. */
static void format_3_b64_chars(char* hexIn, char* out) {
    uint8_t mask2 = 0b00000011;
    uint8_t mask4 = 0b00001111;
    uint8_t mask6 = 0b00111111;
    uint8_t hi, lo, c;

    /* Set output byte 0. */
    out[0] = (hexIn[0] & (mask6 << 2)) >> 2;

    /* Set output byte 1. */
    hi = hexIn[0] & mask2;
    lo = hexIn[1] & (mask4 << 4);
    out[1] = (hi << 4) | (lo >> 4);

    /* Set output byte 2. */
    hi = hexIn[1] & mask4;
    lo = hexIn[2] & (mask2 << 6);
    out[2] = (hi << 2) | (lo >> 6);

    /* Set output byte 3. */
    out[3] = hexIn[2] & mask6;
}

/* Pass in a byte string.
 * Puts the base64 result into out.
 * Currently only supports hexIn of length 3 * n. */
void bytes_to_b64(char* hexIn, char* out, size_t len) {
    for (size_t i = 0; i < (len/3); i ++) {
        format_3_b64_chars(&hexIn[3 * i], &out[4 * i]);
    }

    if ((len % 3) != 0) {
        printf("\nERROR: Part of input ignored.\n");
    }
}

/* Pass in a string of textual hex.
 * Puts the binary of this hex into out. */
void hex_to_bytes(char* in, char* out, size_t len) {
    for (size_t i = 0; i < (len/2); i ++) {
        sscanf(&in[2 * i], "%2hhx", &out[i]);
    }
    if ((len % 2) == 1) {
        sscanf(&in[len - 1], "%x", (unsigned int*) &out[len/2]);
    }
}
