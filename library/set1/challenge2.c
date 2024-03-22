#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <formatters.h>
#include <arithmatic.h>
#include <printers.h>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Incorrect number of args.\n");
        return 1;
    }
    char* in1 = argv[1]; char* in2 = argv[2];

    size_t inputLen = strlen(in1);
    //printf("%d", inputLen);
    if (inputLen != strlen(in2)) {
        printf("Lengths are not equal.\n");
        return 2;
    }

    size_t byteLen = inputLen/2 + (inputLen % 2);
    uint8_t* bytes1 = malloc(byteLen * sizeof(uint8_t));
    uint8_t* bytes2 = malloc(byteLen * sizeof(uint8_t));

    hex_to_bytes(in1, bytes1, inputLen);
    hex_to_bytes(in2, bytes2, inputLen);

    uint8_t* out = malloc(byteLen * sizeof(uint8_t));

    xor_bytes(bytes1, bytes2, out, byteLen);

    print_hex_array(out, byteLen);
    printf("\n");
    free(bytes1); free(bytes2); free(out);
    return 0;
}
