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
    size_t* bytesLenPointer = malloc(sizeof(size_t));
    char* bytes = convert_file_to_bytes_without_newlines(filePointer, 70, bytesLenPointer);
    size_t bytesLen = *bytesLenPointer;
    fclose(filePointer);

    /* Convert the bytes to binary base 64, removing padding. */
    for (int i = 0; i < bytesLen; i ++) {
        if (bytes[i] == 0) {
            bytesLen = i; /* Terminate the loop. Update the new size of bytes. */
        } else {
            bytes[i] = ascii_to_b64(bytes[i]);
        }
    }

    /* Decode the base 64, store it in a new array. */
    /* These don't check if malloc is successful. */
    char* decodedB64 = malloc(3 * (bytesLen * sizeof(char) / 4));
    size_t decodedB64Len = b64_to_bytes(bytes, bytesLen, decodedB64);

    /* Find the key and decode the plaintext. */
    uint8_t key [40];
    uint8_t keyLen = find_repeating_xor_key(decodedB64, key, decodedB64Len, 4, 40);
    uint8_t* plaintext = malloc(decodedB64Len);
    repeating_key_xor(decodedB64, decodedB64Len, key, keyLen, plaintext);

    printf("\nKey: ");
    print_ascii_array(key, keyLen);
    printf("\n\nPlaintext: ");
    print_ascii_array(plaintext, decodedB64Len);

    free(bytes); free(bytesLenPointer); free(decodedB64);
}
