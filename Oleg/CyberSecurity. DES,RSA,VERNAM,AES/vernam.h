#ifndef VERNAM_H
#define VERNAM_H

#include <stdlib.h>

// Function declarations
void vernam_generate_key(unsigned char *key, size_t length);
void vernam_encrypt(const unsigned char *plaintext, unsigned char *ciphertext,
                    const unsigned char *key, size_t length);
void vernam_decrypt(const unsigned char *ciphertext, unsigned char *plaintext,
                    const unsigned char *key, size_t length);

#endif /* VERNAM_H */