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
    psa_key_id_t key = PSA_KEY_ID_NULL;
    psa_key_attributes_t keyAttr = PSA_KEY_ATTRIBUTES_INIT;
    psa_set_key_usage_flags(&keyAttr, PSA_KEY_USAGE_DECRYPT);
    psa_set_key_type(&keyAttr, PSA_KEY_TYPE_AES);
    psa_set_key_bits(&keyAttr, 128);
    psa_set_key_algorithm(&keyAttr, PSA_ALG_ECB_NO_PADDING);
    status = psa_import_key(&keyAttr, keyData, 16, &key);
    if (status != PSA_SUCCESS) {
        printf("\nERROR: Failed to import key.\n");
        return 1;
    }
    printf("\n%lu\n", bytesLen);
    /* Decrypt the data. */
    uint8_t* out = malloc(bytesLen * (sizeof(uint8_t)));
    size_t outLen;
    status = psa_cipher_decrypt(key, PSA_ALG_ECB_NO_PADDING, bytes, bytesLen, out, bytesLen, &outLen);
    if (status != PSA_SUCCESS) {
        printf("\nERROR: Failed to decrypt, error code: %d.\n", status);
        return 1;
    }
    print_ascii_array (out, outLen);
    printf("\n");
    psa_destroy_key(key);

    free(bytes); free(out);
    return 0;
}