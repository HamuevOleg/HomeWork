// utils.h
#ifndef UTILS_H
#define UTILS_H

#include <stddef.h> // For size_t

// Function declarations
void print_hex(const unsigned char *data, size_t length);
void print_raw(const unsigned char *data, size_t length);
void read_input(unsigned char *buffer, size_t max_length, size_t *actual_length);

#endif // UTILS_H