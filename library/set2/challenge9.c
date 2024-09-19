#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <formatters.h>
#include <printers.h>

int main() {
    char in [] = "YELLOW SUBMARINE    ";
    size_t outLen;
    pad_pkcs7(in, in, 16, 20, &outLen);
    printf("\n");
    print_ascii_array(in, 16);
    for (int i = 16; i < outLen; i ++) {
        printf("\\x%d", in[i]);
    }
}
