#include <stdlib.h>
#include <stdint.h>

extern const uint8_t B64_PADDING;

/* Converts a b64 byte to its printable ascii equivalent. */
char b64_to_ascii(uint8_t c);

/* Converts an ASCII character in the b64 range to the b64 binary.
 * i.e. ascii_to_b64('A') == 00000000.
 * i.e. ascii_to_b64(`9`) == 00111101. */
uint8_t ascii_to_b64(char c);

/* Pass in a byte string.
 * Puts the base64 result into out.
 * Currently only supports hexIn of length 3 * n. */
void bytes_to_b64(char* hexIn, char* out, size_t len);

/* Pass in a padded (b64_len%4 == 0) byte array of base 64 characters
 * in binary representation i.e. `A` == 000000.
 * Padding is represented by 0b11111111.
 * Decode the base64 into out.
 * Return the length of the decoded array. */
size_t b64_to_bytes(uint8_t *b64In, size_t b64Len, uint8_t *out);

/* Pass in a string of textual hex.
 * Puts the binary of this hex into out. */
void hex_to_bytes(char* in, char* out, size_t len);

/* Take as input a file pointer to an open file,
 * return the contents of the file as a byte
 * array with all newlines filtered out.
 * Store the length of the new byte array. */
char* convert_file_to_bytes_without_newlines(FILE * filePointer, int maxLineLen, size_t* outLen);

/* Take as input a file pointer to an open file of encoded base64.
 * Decode the file and store the decoded bytes into the returned array. */
char* decode_b64_file_into_bytes(FILE * filePointer, int maxLineLen, size_t* outLen);