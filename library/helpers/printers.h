#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <formatters.h>

static inline void print_hex_array(char* in, size_t len) {
    for (size_t i = 0; i < len; i++) {
        printf("%02x", in[i]);
    }
}

static inline void print_ascii_array(char* in, size_t len) {
    for (size_t i = 0; i < len; i++) {
        printf("%c", in[i]);
    }
}

static inline void print_b64_array(char* in, size_t len) {
    for (size_t i = 0; i < len; i++) {
        printf("%c", b64_to_ascii(in[i]));
    }
}
