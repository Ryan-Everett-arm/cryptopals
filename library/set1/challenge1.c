#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <formatters.h>
#include <printers.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        /* Incorrect number of args. */
        return -1;
    }

    char* in = argv[1];
    size_t inputLen = strlen(in);

    char* bytes = malloc((1 + inputLen/2) * sizeof(char));
    char* out = malloc(inputLen * sizeof(char));

    /* Get the byte array. */
    hex_to_bytes(in, bytes, inputLen);

    /* Convert to base64 format. */
    bytes_to_b64(bytes, out, inputLen/2);

    /* Print b64. */
    print_b64_array(out, 4 * (inputLen/6));
    printf("\n");
    free(out);
    free(bytes);
    return 0;
}
