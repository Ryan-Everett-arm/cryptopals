#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <formatters.h>
#include <arithmatic.h>
#include <printers.h>
#include <crypto.h>
#include <psa/crypto.h>

int main() {
    /* Load the decoded file into a byte array. */
    FILE * filePointer;
    filePointer = fopen("../library/set1/challenge-data/7.txt", "r");
    if (filePointer == NULL) {
        printf("\nERROR: File does not exist.\n");
        return 1;
    }
    size_t bytesLen;
    char* bytes = decode_b64_file_into_bytes(filePointer, 70, &bytesLen);
    fclose(filePointer);

    /* Initialize PSA Crypto */
    psa_status_t status = psa_crypto_init();
    if (status != PSA_SUCCESS) {
        printf("Failed to initialize PSA Crypto\n");
        return 1;
    }

    /* Load the key. */
    uint8_t* keyData = "YELLOW SUBMARINE";
    uint8_t* out = malloc(bytesLen * (sizeof(uint8_t)));
    decrypt_ecb_aes_128(bytes, bytesLen, keyData, 16, out);
    encrypt_ecb_aes_128(out, bytesLen, keyData, 16, bytes);
    decrypt_ecb_aes_128(bytes, bytesLen, keyData, 16, out);
    print_ascii_array(out, bytesLen);
    printf("\n");

    free(bytes); free(out);
    return 0;
}