// DES.h
/**
 * DES.h
 *
 * Заголовочный файл для реализации алгоритма Data Encryption Standard (DES)
 *
 * Эта реализация следует спецификации FIPS 46-3 для DES
 */

#ifndef DES_H
#define DES_H

#include <stdint.h>
#include <stdlib.h>
#include <stddef.h> // Для size_t

#define DES_BLOCK_SIZE 8  // в байтах (64 бита)

// Объявления функций
uint64_t des_encrypt_block(uint64_t block, uint64_t key);
uint64_t des_decrypt_block(uint64_t block, uint64_t key);
void encrypt_block(const unsigned char *input, unsigned char *output, uint64_t key);
void decrypt_block(const unsigned char *input, unsigned char *output, uint64_t key);
void des_encrypt_ecb(const unsigned char *input, unsigned char *output, size_t length, uint64_t key);
void des_decrypt_ecb(const unsigned char *input, unsigned char *output, size_t length, uint64_t key);
uint64_t bytes_to_uint64(const unsigned char *bytes);
void uint64_to_bytes(uint64_t value, unsigned char *bytes);
// Note: print_hex and print_raw are NOT declared here, they are in utils.h

#endif /* DES_H */