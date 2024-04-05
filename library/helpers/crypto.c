#include <stdlib.h>
#include <stdint.h>
#include <arithmatic.h>

void repeating_key_xor(uint8_t* bytes, size_t bytesLen, uint8_t* key, size_t keyLen, uint8_t* out) {
    /* Special case for when the key is not shorter than the plaintext. */
    if (keyLen > bytesLen) {
        xor_bytes(bytes, key, out, bytesLen);
        return;
    }

    /* Encrypt all bytes except the final (bytesLen%keyLen). */
    for (size_t i = 0; i < bytesLen; i += keyLen) {
        xor_bytes(bytes + i, key, out + i, keyLen);
    }

    /* Encrypt the final bytes. */
    size_t remaining = bytesLen % keyLen;
    size_t index = bytesLen - remaining;
    xor_bytes(bytes + index, key, out + index, remaining);
}