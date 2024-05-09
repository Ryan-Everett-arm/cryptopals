#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

/* xor two equal length byte arrays. */
void xor_bytes(uint8_t* in1, uint8_t* in2, uint8_t* out, size_t len);

/* xor every byte in a sequence with a one byte key. */
void xor_bytes_with_key(uint8_t* bytes, uint8_t key, uint8_t* out, size_t len);

/* Score a sequence of byte.
 * A higher score means that the bytes are more likely to be a base64 encoded English sentence.
 * A base score of 20 for a lower case letter and 40 for a space is added to the inputted scoring table. */
size_t score_english_text(uint8_t* bytes, int* scores, size_t len);

/* Return 1 if the contents of a and b are the same, 0 otherwise. */
int string_equal(char* a, char* b, size_t len);

size_t hamming_distance(uint8_t* in1, uint8_t* in2, size_t len);