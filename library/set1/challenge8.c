#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <formatters.h>
#include <arithmatic.h>
#include <printers.h>

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
