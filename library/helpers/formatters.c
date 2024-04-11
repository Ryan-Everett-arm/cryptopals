#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

const uint8_t B64_PADDING = 0b11111111;

/* Converts a b64 byte to its printable ascii equivalent. */
char b64_to_ascii(uint8_t c)
{
    if (c == B64_PADDING) {
        return '=';
    }
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

uint8_t ascii_to_b64(char c) {
    /* Special cases. */
    /* Padding. */
    if (c == '=') {
        return B64_PADDING;
    }
    if (c == '+') {
        return 0b00111110;
    } else if (c == '/') {
        return 0b00111111;
    } else if ((c >= 'A') && (c <= 'Z')) {
        /* Upper case. */
        return (c - 'A');
    } else if ((c >= 'a') && (c <= 'z')) {
        /* Lower case. */
        return (c - 'a') + 26;
    } else if ((c >= '0') && (c <= '9')) {
        /* Num. */
        return (c - '0') + 52;
    } else {
        printf("\nERROR: Attempted to encode non b64 ascii %x into b64.\n", c);
        return 0b11111111;
    }
}

/* hexIn must have at least 3 bytes of space, out must have 4.
 * Maps abcdefgh ijklmnop qrstuvwx.
 * to   00abcdef 00ghijkl 00mnopqr 00stuvwx. */
static void format_3_b64_chars(char *hexIn, char *out) {
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

/* b64In must have at least 4 bytes of space, out must have 3.
 * Maps 00abcdef 00ghijkl 00mnopqr 00stuvwx
 * to   abcdefgh ijklmnop qrstuvwx. */
void convert_4_b64_to_bytes(char *b64In, char *out) {
    /* B0  =     abcdef00    |    000000gh */
    out[0] = (b64In[0] << 2) | (b64In[1] >> 4);
    /* B1  =     ijkl0000    |    0000mnop */
    out[1] = (b64In[1] << 4) | (b64In[2] >> 2);
    /* B2  =     qr000000    |  00stuvwx */
    out[2] = (b64In[2] << 6) | (b64In[3]);
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

/* Pass in a padded (b64_len%4 == 0) byte array of base 64 characters
 * in binary representation i.e. `A` == 000000.
 * Padding is represented by 0b11111111.
 * Decode the base64 into out.
 * Return the length of the decoded array. */
size_t b64_to_bytes(uint8_t *b64In, size_t b64Len, uint8_t *out) {
    if ((b64Len == 0) | ((b64Len % 4) != 0)) {
        printf("\nERROR: Invalid length.\n");
        return -1;
    }

    size_t outSize = 3 * (b64Len / 4);
    /* Convert the bytes. */
    for (int i = 0; i < (b64Len / 4); i++) {
        convert_4_b64_to_bytes(&b64In[4 * i], &out[3 * i]);
    }

    /* Remove the extra length if padding exists. */
    if (b64In[b64Len - 1] == B64_PADDING) {
        outSize --; 
        if (b64In[b64Len - 2] == B64_PADDING) {
            outSize --;
        }
    }
    return outSize;
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
