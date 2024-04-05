#include <stdlib.h>
#include <stdint.h>

/* Converts a b64 byte to its printable ascii equivalent. */
char b64_to_ascii(uint8_t c);

/* Pass in a byte string.
 * Puts the base64 result into out.
 * Currently only supports hexIn of length 3 * n. */
void bytes_to_b64(char* hexIn, char* out, size_t len);

/* Pass in a string of textual hex.
 * Puts the binary of this hex into out. */
void hex_to_bytes(char* in, char* out, size_t len);

/* Return the key used to encrypt an ASCII encoded English mainly-lowercase plaintext. */
uint8_t brute_force_xor_cipher(uint8_t* ciphertext, uint8_t* plaintext, size_t * score, size_t len);
