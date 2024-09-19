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
    /* B2  =     qr000000    |    00stuvwx */
    out[2] = (b64In[2] << 6) | (  b64In[3]   );
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
void hex_to_bytes(char *in, char *out, size_t len) {
    for (size_t i = 0; i < (len / 2); i++) {
        sscanf(&in[2 * i], "%2hhx", &out[i]);
    }
    if ((len % 2) == 1) {
        sscanf(&in[len - 1], "%x", (unsigned int*)&out[len / 2]);
    }
}

/* Take as input a file pointer to an open file,
 * return the contents of the file as a byte
 * array with all newlines filtered out.
 * Store the length of the new byte array. */
char* convert_file_to_bytes_without_newlines(FILE * filePointer, int maxLineLen, size_t* outLength) {
    /* Get file length for an upper bound on return size.*/
    fseek(filePointer, 0, SEEK_END);
    size_t fileLen = ftell(filePointer);
    rewind(filePointer);

    char* out = malloc(fileLen * sizeof(char));

    size_t currLength = 0;
    char buffer[maxLineLen];
    while(fgets(buffer, maxLineLen + 1, filePointer)) {
        /* buffer now holds the line including the new line.
         * Cut the new line and copy this to out. */
        memcpy(&out[currLength], buffer, strlen(buffer) - 1);
        currLength += strlen(buffer) - 1;
    }
    *outLength = currLength;
    return out;
}

/* Take as input a file pointer to an open file of encoded base64.
 * Decode the file and store the decoded bytes into the returned array. */
char* decode_b64_file_into_bytes(FILE * filePointer, int maxLineLen, size_t* outLen) {
    size_t b64Len;

    char* bytesB64 = convert_file_to_bytes_without_newlines(filePointer, maxLineLen, &b64Len);

    /* Convert the base64 ascii to binary base 64, removing padding. */
    for (int i = 0; i < b64Len; i ++) {
        if (bytesB64[i] == 0) {
            b64Len = i; /* Terminate the loop. Update the new size of bytes. */
        } else {
            bytesB64[i] = ascii_to_b64(bytesB64[i]);
        }
    }

    /*Decode the base64: */
    char* bytes = malloc((3 * (b64Len * sizeof(char))) / 4);
    *outLen = b64_to_bytes(bytesB64, b64Len, bytes);
    free(bytesB64);

    return bytes;
}

/* Pad a string 'in' to a 'blockLen' size using the PKCS#7 format.
 * Put the result into 'out'. 'out' and 'in' can be the same. */
void pad_pkcs7(char* in, char* out, size_t inLen, uint8_t blockLen, size_t* outLen) {
    if (out != in) {
        /* Copy in into out. */
        for (int i = 0; i < inLen; i ++) {
            out[i] = in[i];
        }
    }

    uint8_t padLen = blockLen - (inLen % blockLen);
    for (int i = inLen; i < inLen + padLen; i++) {
        out[i] = padLen;
    }
    *outLen = inLen + padLen;
}
