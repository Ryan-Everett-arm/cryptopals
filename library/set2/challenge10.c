#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <formatters.h>
#include <printers.h>
#include <crypto.h>

int main() {
    uint8_t* key = "YELLOW SUBMARINE";
    size_t keyLen = 16;
    /* Load the decoded file into a byte array. */
    FILE * filePointer;
    filePointer = fopen("../library/set2/challenge-data/10.txt", "r");
    if (filePointer == NULL) {
        printf("\nERROR: File does not exist.\n");
        return 1;
    }
    size_t bytesLen;
    char* ctx = decode_b64_file_into_bytes(filePointer, 70, &bytesLen);
    printf("\n%lu\n", bytesLen);
    fclose(filePointer);
    char* ptx = malloc(bytesLen);
    char iv [16];
    for (int i = 0; i < 16; i ++){
        iv[i] = 0;
    }
    decrypt_cbc_aes_128(ctx, bytesLen, key, keyLen, iv, ptx);
    uint8_t res[bytesLen];
    memcpy(res, ptx, bytesLen);

    encrypt_cbc_aes_128(ptx, bytesLen, key, keyLen, iv, ctx);
    decrypt_cbc_aes_128(ctx, bytesLen, key, keyLen, iv, ptx);

    for (int i = 0; i < bytesLen; i ++) {
        if (ptx[i] != res[i]) {
            printf("\nERROR: Dec(Enc(ptx)) != ptx. \n");
            return 1;
        }
    }

    print_ascii_array(ptx, bytesLen);
    free(ptx);
}