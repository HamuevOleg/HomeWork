#include "rsa.h"
#include <stdio.h>

// Calculate Greatest Common Divisor (GCD)
uint64_t gcd(uint64_t a, uint64_t b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

// Compute modular multiplicative inverse (extended Euclidean algorithm)
uint64_t mod_inverse(uint64_t a, uint64_t m) {
    int64_t m0 = m, t, q;
    int64_t x0 = 0, x1 = 1;

    if (m == 1)
        return 0;

    // Apply extended Euclid Algorithm
    while (a > 1) {
        // q is quotient
        q = a / m;
        t = m;

        // m is remainder now, process same as Euclid's algo
        m = a % m;
        a = t;

        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }

    // Make x1 positive
    if (x1 < 0)
        x1 += m0;

    return x1;
}

// Compute a^b mod n efficiently using square and multiply algorithm
uint64_t mod_pow(uint64_t base, uint64_t exponent, uint64_t modulus) {
    if (modulus == 1) return 0;

    uint64_t result = 1;
    base = base % modulus;

    while (exponent > 0) {
        // If exponent is odd, multiply base with result
        if (exponent & 1)
            result = (result * base) % modulus;

        // Exponent is even now
        exponent >>= 1;
        base = (base * base) % modulus;
    }

    return result;
}

// Generate RSA keys
void rsa_generate_keys(RSA_KEY *key, uint64_t p, uint64_t q, uint64_t e) {
    // Calculate n = p * q
    key->n = p * q;

    // Calculate Euler's totient function φ(n) = (p-1) * (q-1)
    uint64_t phi = (p - 1) * (q - 1);

    // Choose e such that 1 < e < phi and gcd(e, phi) = 1
    // Note: In practice, e is usually 65537, but for simplicity we're using the provided e
    key->e = e;

    // Ensure e and phi are coprime
    if (gcd(e, phi) != 1) {
        printf("Error: e and phi are not coprime. Choose another e.\n");
        return;
    }

    // Calculate private key: d = e^(-1) mod phi
    key->d = mod_inverse(e, phi);

    // Save p and q
    key->p = p;
    key->q = q;
}

// Encrypt a single block
uint64_t rsa_encrypt(uint64_t message, uint64_t e, uint64_t n) {
    return mod_pow(message, e, n);
}

// Decrypt a single block
uint64_t rsa_decrypt(uint64_t cipher, uint64_t d, uint64_t n) {
    return mod_pow(cipher, d, n);
}

// Encrypt a message (one byte at a time for simplicity)
void rsa_encrypt_message(const unsigned char *input, unsigned char *output, size_t length, RSA_KEY *key) {
    for (size_t i = 0; i < length; i++) {
        uint64_t encrypted = rsa_encrypt(input[i], key->e, key->n);

        // Store the encrypted value in output (assume enough space allocated)
        // Here we're using 8 bytes per original byte, which is inefficient but simple
        for (int j = 7; j >= 0; j--) {
            output[i * 8 + j] = encrypted & 0xFF;
            encrypted >>= 8;
        }
    }
}

// Decrypt a message
void rsa_decrypt_message(const unsigned char *input, unsigned char *output, size_t length, RSA_KEY *key) {
    for (size_t i = 0; i < length / 8; i++) {
        // Read 8 bytes from input and convert to uint64_t
        uint64_t encrypted = 0;
        for (int j = 0; j < 8; j++) {
            encrypted = (encrypted << 8) | input[i * 8 + j];
        }

        // Decrypt
        uint64_t decrypted = rsa_decrypt(encrypted, key->d, key->n);

        // Write the decrypted byte
        output[i] = (unsigned char)decrypted;
    }
}