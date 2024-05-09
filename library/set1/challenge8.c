#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <formatters.h>
#include <arithmatic.h>
#include <printers.h>

/* This simply checks every line of the input file for duplicate blocks.
 *
 * There is only one ciphertext which has a duplicate block (indeed it has 4 duplicate blocks!).
 * Given the heavy hinting in the question, we can quite safely assume that this
 * string is the ECB encrypted string. But this isn't actual proof,
 * and it poses an interesting mathematical question:
 *
 * Given a data set like the one we have: containing only one ECB encrypted ciphertext
 * and assuming that all other ciphertexts are indistinguishable from uniformly generated
 * random strings, what is the probability that this code returns the wrong ciphertext?
 *
 * This code returns a ciphetext as ECB encrypted if the text contains ANY
 * duplicate blocks. The required probability is bounded by the probability
 * that at least one of the 203 "non-target" ciphertexts contains a duplicate
 * block, so let's calculate that.
 * In the Cryptopals spirit of working from first principles, we will prove this
 * result assuming only the fundamentals of probability:
 *
 * Each ciphertext is 160 bytes long, composed of 10 "blocks". Without loss
 * of generality, let C be some ciphertext which is **not** the target,
 * and let Ci denote the ith block of C.
 * We are interested in the probability that C does not have any duplicate blocks.
 * This is an instance of the Birthday Paradox, let's prove it with a counting argument:
 *
 * Each block represents a 128 bit number, so there are 2^128 possible values for any block.
 * For the sake of readablility, let k = 2^128.
 * The number of 10 block strings which do not contain any repeating blocks, N, is given by:
 * N = k *      //Number of possible values for the first block
 *     k - 1 *  //The second block can take any value except for the value of the first block
 *     k - 2 *  //The third block can take any value except for the value of the first two blocks.
 *     ...   *
 *     k - 9    //The final block can take any value except for the value of the previous blocks.
 *   = k! / (k - 10)! //Simplifly the result.
 *
 * The total number of unique 10 block strings, M, is given by:
 * M = k^10 //Each block can take any value between 0 and 2^128 - 1.
 *
 * The strings are uniformally generated, C takes any value with equal chance, so:
 * P(C does not have any duplicate blocks) = N / M = k! / (k^10 * (k - 10)!).
 *
 * This number is not pleasant to work out by hand, so we will instead use
 * an upper bound by noticing that N > (k - 9)^10.
 *
 * N / M > (k - 9)^10 / (k^10) = ((k - 9) / k)^10
 *       > 1 - 10^-36 //A simple approximation accounting only for the most significant digit.
 *
 * Therefore the probability that C contains two duplicate blocks is less than 10^-36.
 *
 * We have 203 non-target strings, the probability that at least one of these
 * has a duplicate block is a binomial, given by:
 *   = 1 - P(All 203 strings have no duplicate blocks)
 *   < 203 * 10^-36 //As the strings are independant and identically distributed.
 *   < 2.03 * 10^-34
 *   < 10^-33.
 *
 *
 * The analyses shows that the probability of the code returning a non ECB encrypted
 * ciphertext is less than 10^-33.
 *
 * We can conclude that it is near certain that the returned string was ECB encrypted.
 */

int main() {
    FILE * filePointer;
    int bufferLength = 350;
    char buffer[10][32];
    int stringNum = 0;
    size_t byteLen = 30;
    filePointer = fopen("../library/set1/challenge-data/8.txt", "r");

    if (filePointer == NULL) {
        printf("\nERROR: File does not exist.\n");
        return 1;
    }

    while(fgets((char *) buffer, bufferLength, filePointer)) {
        /* We detect a string as ECB encrypted if there are any duplicate blocks in the string. */
        int stringECBEncrypted = 0;
        /* For every block, check if there are any blocks of smaller ID equal to this block. */
        for (int i = 1; i < 10; i ++) {
            for (int j = 0; j < i; j ++) {
                if (string_equal(buffer[i], buffer[j], 32)) {
                    if (!stringECBEncrypted) {
                        printf("\nString %d is likely ECB encrypted, with equivalent block pairs: ", stringNum);
                    }
                    printf("(%d, %d), ", j, i);
                    stringECBEncrypted = 1;
                }
            }
        }
        stringNum ++;
    }
    printf("\n");
    return 0;
}
