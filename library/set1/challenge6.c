#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <formatters.h>
#include <arithmatic.h>
#include <printers.h>
#include <crypto.h>

int hamming_distance_test() {
    uint8_t* in1 = "this is a test";
    uint8_t* in2 = "wokka wokka!!!";
    size_t inLen = strlen(in1);
    size_t d = hamming_distance(in1, in2, inLen);
    if (d != 37) {
        printf("\nERROR: Corruption detected.\n");
        return 1;
    }
}

int main() {
    if (hamming_distance_test() == 1) {
        return 1;
    }

    /* Load the file into a byte array. */
    FILE * filePointer;
    filePointer = fopen("../library/set1/challenge-data/6.txt", "r");
    if (filePointer == NULL) {
        printf("\nERROR: File does not exist.\n");
        return 1;
    }
    size_t bytesLen;
    char* bytes = decode_b64_file_into_bytes(filePointer, 70, &bytesLen);
    fclose(filePointer);

    /* Find the key and decode the plaintext. */
    uint8_t key [40];
    uint8_t keyLen = find_repeating_xor_key(bytes, key, bytesLen, 4, 40);

    uint8_t* plaintext = malloc(bytesLen);
    repeating_key_xor(bytes, bytesLen, key, keyLen, plaintext);

    printf("\nKey: ");
    print_ascii_array(key, keyLen);
    printf("\n\nPlaintext: ");
    print_ascii_array(plaintext, bytesLen);

    free(bytes); free(plaintext);
}
