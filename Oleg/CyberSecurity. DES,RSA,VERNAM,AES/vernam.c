#include "vernam.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Generate a random key of specified length
void vernam_generate_key(unsigned char *key, size_t length) {
    // Seed the random number generator
    srand((unsigned int)time(NULL));

    // Generate random bytes
    for (size_t i = 0; i < length; i++) {
        key[i] = rand() & 0xFF;
    }
}

// Encrypt data using the Vernam cipher (XOR with key)
void vernam_encrypt(const unsigned char *plaintext, unsigned char *ciphertext,
                    const unsigned char *key, size_t length) {
    for (size_t i = 0; i < length; i++) {
        ciphertext[i] = plaintext[i] ^ key[i];
    }
}

// Decrypt data using the Vernam cipher (XOR with key again)
void vernam_decrypt(const unsigned char *ciphertext, unsigned char *plaintext,
                    const unsigned char *key, size_t length) {
    // Decryption is the same as encryption in XOR-based ciphers
    vernam_encrypt(ciphertext, plaintext, key, length);
}