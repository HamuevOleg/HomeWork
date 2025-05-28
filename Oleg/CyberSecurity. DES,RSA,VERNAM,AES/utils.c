#include "utils.h"
#include <stdio.h>
#include <string.h>

void read_input(unsigned char *buffer, size_t max_length, size_t *actual_length) {
    printf("Enter text (max %zu characters): ", max_length - 1);

    fgets((char *)buffer, max_length, stdin);

    size_t len = strlen((char *)buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
        len--;
    }

    *actual_length = len;
}