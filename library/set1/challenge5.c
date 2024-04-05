#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <crypto.h>
#include <arithmatic.h>
#include <printers.h>

int main() {
    char* in = "Burning 'em, if you ain't quick and nimble\nI go crazy when I hear a cymbal";
    size_t inputLen = strlen(in);
    char* key = "ICE";
    size_t keyLen = strlen(key);
    char* out = malloc(inputLen * sizeof(char));

    repeating_key_xor(in, inputLen, key, keyLen, out);
    print_hex_array(out, inputLen);
    free(out);
}