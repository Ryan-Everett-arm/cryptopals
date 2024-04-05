#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <formatters.h>
#include <arithmatic.h>
#include <printers.h>

int main() {
    FILE * filePointer;
    int bufferLength = 80;
    char buffer[bufferLength];
    size_t byteLen = 30;
    filePointer = fopen("/data_nvme1n1/ryaeve01//cryptopals/library/set1/challenge-data/3.4.txt", "r");
    
    if (filePointer == NULL) {
        printf("\nERROR: File does not exist.\n");
        return 1;
    }
    char* out = malloc((byteLen) * sizeof(char));
    char* bytes = malloc((byteLen) * sizeof(char));
    char* maxPlaintext = malloc((byteLen) * sizeof(char));
    size_t* score = malloc((sizeof(size_t)));
    size_t maxScore = 0; size_t secondMaxScore = 0;
    size_t maxIndex = 0;
    size_t i = 0;
    uint8_t bestKey = 0; uint8_t key = 0;
    while(fgets(buffer, bufferLength, filePointer)) {
        //printf("%s\n", buffer);
        hex_to_bytes(buffer, bytes, bufferLength);
        key = brute_force_xor_cipher(bytes, out, score, byteLen);
        //printf("\n");
        //print_ascii_array(out, byteLen);
        if (*score > secondMaxScore) {
            if (*score > maxScore) {
                secondMaxScore = maxScore;
                bestKey = key;
                maxScore = *score;
                maxIndex = i;
                brute_force_xor_cipher(bytes, maxPlaintext, score, byteLen);
            } else {
                secondMaxScore = *score;
            }
        }
        i ++;
    }
    printf("The plaintext is \"");
    print_ascii_array(maxPlaintext, byteLen);
    printf("\".\nThis is string %lu, with a score of %lu.\n", maxIndex, maxScore);
    printf("The second highest scoring string scored %lu.\n", secondMaxScore);
    fclose(filePointer);
    free(bytes); free(out); free(score);
}