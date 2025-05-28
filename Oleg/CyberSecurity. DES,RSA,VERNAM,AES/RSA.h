#ifndef RSA_H
#define RSA_H

#include <stdint.h>
#include <stdlib.h>

typedef struct {
    uint64_t n;       // Modulus (n = p * q)
    uint64_t e;       // Public exponent
    uint64_t d;       // Private exponent
    uint64_t p;       // First prime factor
    uint64_t q;       // Second prime factor
} RSA_KEY;

void rsa_generate_keys(RSA_KEY *key, uint64_t p, uint64_t q, uint64_t e);
uint64_t rsa_encrypt(uint64_t message, uint64_t e, uint64_t n);
uint64_t rsa_decrypt(uint64_t cipher, uint64_t d, uint64_t n);
void rsa_encrypt_message(const unsigned char *input, unsigned char *output, size_t length, RSA_KEY *key);
void rsa_decrypt_message(const unsigned char *input, unsigned char *output, size_t length, RSA_KEY *key);

#endif