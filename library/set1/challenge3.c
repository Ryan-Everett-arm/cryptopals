#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <formatters.h>
#include <arithmatic.h>
#include <printers.h>
#include <crypto.h>

/* First convert the input to a byte array.
 * Then brute-force by decoding with every possible key (there are only 256),
 * and pick the plaintext corresponding to the highest score.
 *
 * The scoring system is simple:
 *      - Award any lowercase letter a 20 point base score.
 *      - Add an additional score between 0 and 15 for how frequently the letter is used in the English dictionary.
 *      - Award any ' ' with a score of 40 points. */
int main() {
    char* in = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
    size_t inputLen = strlen(in);
    size_t byteLen = inputLen/2 + (inputLen % 2);
    char* bytes = malloc((byteLen) * sizeof(char));
    char* out = malloc(byteLen * sizeof(char));
    size_t* score = 0;
    /* Get the byte array. */
    hex_to_bytes(in, bytes, inputLen);

    /* Brute force the cipher. */
    brute_force_xor_cipher(bytes, out, score, byteLen);

    /* Print the result. */
    print_ascii_array(out, byteLen);
    printf("\n");

    free(out); free(bytes);
}