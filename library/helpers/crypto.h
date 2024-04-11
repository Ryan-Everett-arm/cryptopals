#include <stdlib.h>
#include <stdint.h>

void repeating_key_xor(uint8_t* bytes, size_t bytesLen, uint8_t* key, size_t keyLen, uint8_t* out);/* Return the key used to encrypt an ASCII encoded English mainly-lowercase plaintext. */
/* Return the key used to encrypt an ASCII encoded English mainly-lowercase plaintext. */
uint8_t brute_force_xor_cipher(uint8_t* ciphertext, uint8_t* plaintext, size_t * score, size_t len);

