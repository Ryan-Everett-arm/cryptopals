#include <stdlib.h>
#include <stdint.h>

/* xor two equal length byte arrays. */
void xor_bytes(uint8_t* in1, uint8_t* in2, uint8_t* out, size_t len){
    for (size_t i = 0; i < len; i ++) {
        out[i] = in1[i] ^ in2[i];
    }
}

void xor_bytes_with_key(uint8_t* bytes, uint8_t key, uint8_t* out, size_t len) {
    for (size_t i = 0; i < len; i++){
        out[i] = bytes[i] ^ key;
    }
}

/* Score a sequence of byte.
 * A higher score means that the bytes are more likely to be a base64 encoded English sentence.
 * A base score of 20 for a lower case letter and 40 for a space is added to the inputted scoring table. */
size_t score_english_text(uint8_t* bytes, int* scores, size_t len) {
    size_t score = 0;
    for (size_t i = 0; i < len; i ++) {
        if ('a' <= bytes[i] && bytes[i] <= 'z') {
            score += 20 + scores[bytes[i] - 'a'];
        } else if (bytes[i] == ' ') {
            /* Spaces are the most common character. */
            score += 40;
        }
    }
    return score;
}

/* Sorted by the frequency of letter occurences. */
static int english_freq_score[] = 
    {
    //a, b, c, d, e , f, g, h, i, j, k, l, m
      9, 2, 5, 4, 12, 2, 3, 3, 8, 0, 1, 6, 3,

    //n, o, p, q, r, s, t, u, v, w, x, y, z
      7, 7, 3, 0, 8, 6, 7, 4, 1, 1, 0, 2, 0
    };

/* Pass in base64 bytes, decrypt and put output into out, key into key. */
uint8_t brute_force_xor_cipher(uint8_t* bytes, uint8_t* out, size_t len) {
    uint8_t key = 0; size_t score = 0;
    uint8_t bestKey = 0; size_t bestScore = 0;
    uint8_t secondBestScore = 0;
    /* Invarariant: i == key. */
    for (int i = 0; i < 256; i ++) {
        xor_bytes_with_key(bytes, key, out, len);
        score = score_english_text(out, english_freq_score, len);
        if (score > secondBestScore) {
            if (score > bestScore) {
                secondBestScore = bestScore;
                bestScore = score;
                bestKey = key;
            }
            else {
                secondBestScore = score;
            }
        }
        key ++;
    }
    xor_bytes_with_key(bytes, bestKey, out, len);
    return bestKey;
}
