#include <stdlib.h>
#include <stdint.h>
#include <psa/crypto.h>

void repeating_key_xor(uint8_t* bytes, size_t bytesLen, uint8_t* key, size_t keyLen, uint8_t* out);

/* Return the key used to encrypt an ASCII encoded English mainly-lowercase plaintext. */
uint8_t brute_force_xor_cipher(uint8_t* ciphertext, uint8_t* plaintext, size_t * score, size_t len);

/* When ciphertext has been encrypted by a repeating key xor,
 * find the key and store it in out.
 * The ciphertext must be longer than numTries * maxKeyLen. */
int find_repeating_xor_key(uint8_t* ciphertext, uint8_t* out, size_t len, size_t numTries, int maxKeyLen);

void encrypt_ecb_aes_128(uint8_t* bytes, size_t bytesLen, uint8_t* key, size_t keyLen, uint8_t* out);

void decrypt_ecb_aes_128(uint8_t* bytes, size_t bytesLen, uint8_t* key, size_t keyLen, uint8_t* out);

/* In future this could be generalised to just encrypt_cbc, with mode as param. */
void encrypt_cbc_ecb_aes_128(uint8_t* bytes, size_t bytesLen, uint8_t* key, size_t keyLen, uint8_t* iv, uint8_t* out);

void decrypt_cbc_ecb_aes_128(uint8_t* bytes, size_t bytesLen, uint8_t* key, size_t keyLen, uint8_t* iv, uint8_t* out);
