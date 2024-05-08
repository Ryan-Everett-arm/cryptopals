#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <formatters.h>
#include <arithmatic.h>
#include <printers.h>
#include <crypto.h>
#include <openssl/evp.h>

/* Switch to mbedtls (make sure to use PSA API) */
int main() {
    /* Load the file into a byte array. */
    FILE * filePointer;
    filePointer = fopen("../library/set1/challenge-data/7.txt", "r");
    if (filePointer == NULL) {
        printf("\nERROR: File does not exist.\n");
        return 1;
    }
    size_t bytesLen;
    char* bytes = decode_b64_file_into_bytes(filePointer, 70, &bytesLen);
    fclose(filePointer);

    /* Init cipher fields. */
    uint8_t* key = "YELLOW SUBMARINE";
    uint8_t* out = malloc(bytesLen * (sizeof(uint8_t)));
    int *outLen = malloc(sizeof(int));
    EVP_CIPHER_CTX * cipherCtx = EVP_CIPHER_CTX_new();
    
    /* Perform decryption. */
    int x = EVP_DecryptInit_ex(cipherCtx, EVP_aes_128_ecb(), NULL, key, NULL);
    if (x != 1) {
        printf("%d", x);
        return 1;
    }
    EVP_DecryptUpdate(cipherCtx, out, outLen, bytes, bytesLen);

    print_ascii_array (out, *outLen);

    return 0;
}