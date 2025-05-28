#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "des.h"
#include "rsa.h"
#include "vernam.h"
#include "utils.h"

#define MAX_INPUT_SIZE 1024
#define MAX_CIPHER_SIZE 8192  // Especially for RSA which expands data

void clear_screen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void des_menu() {
    unsigned char input[MAX_INPUT_SIZE] = {0};
    unsigned char output[MAX_INPUT_SIZE] = {0};
    unsigned char decrypted[MAX_INPUT_SIZE] = {0};
    unsigned char key_bytes[8] = {0};
    size_t input_length = 0;

    clear_screen();
    printf("=== DES Encryption/Decryption ===\n\n");

    // Get key
    printf("Enter 8 character key: ");
    fgets((char *)key_bytes, 9, stdin);
    // Remove trailing newline
    if (key_bytes[strlen((char *)key_bytes) - 1] == '\n')
        key_bytes[strlen((char *)key_bytes) - 1] = '\0';

    while (strlen((char *)key_bytes) < 8) {
        // Pad key with zeros if too short
        key_bytes[strlen((char *)key_bytes)] = '0';
    }

    uint64_t key = bytes_to_uint64(key_bytes);

    // Get input text
    read_input(input, MAX_INPUT_SIZE, &input_length);

    // Encrypt
    des_encrypt_ecb(input, output, input_length, key);

    printf("\nPlaintext: %s\n", input);
    printf("\nCiphertext in hex:\n");
    print_hex(output, ((input_length + 7) / 8) * 8);  // Round up to nearest block

    // Decrypt
    des_decrypt_ecb(output, decrypted, ((input_length + 7) / 8) * 8, key);
    printf("\nDecrypted text: %s\n", decrypted);

    printf("\nPress Enter to continue...");
    getchar();
}

void rsa_menu() {
    unsigned char input[MAX_INPUT_SIZE] = {0};
    unsigned char encrypted[MAX_CIPHER_SIZE] = {0};
    unsigned char decrypted[MAX_INPUT_SIZE] = {0};
    size_t input_length = 0;
    RSA_KEY key;

    clear_screen();
    printf("=== RSA Encryption/Decryption ===\n\n");

    // Using small primes for demonstration purposes
    // In real-world applications, these would be much larger
    uint64_t p = 61;
    uint64_t q = 53;
    uint64_t e = 17;

    printf("Using p=%llu, q=%llu, e=%llu for key generation\n",
           (unsigned long long)p, (unsigned long long)q, (unsigned long long)e);

    // Generate keys
    rsa_generate_keys(&key, p, q, e);

    printf("Generated RSA parameters:\n");
    printf("n = %llu (modulus)\n", (unsigned long long)key.n);
    printf("e = %llu (public exponent)\n", (unsigned long long)key.e);
    printf("d = %llu (private exponent)\n", (unsigned long long)key.d);

    // Get input text
    read_input(input, MAX_INPUT_SIZE, &input_length);

    // Encrypt
    rsa_encrypt_message(input, encrypted, input_length, &key);

    printf("\nPlaintext: %s\n", input);
    printf("\nCiphertext in hex:\n");
    print_hex(encrypted, input_length * 8);  // Each byte expands to 8 bytes

    // Decrypt
    rsa_decrypt_message(encrypted, decrypted, input_length * 8, &key);
    printf("\nDecrypted text: %s\n", decrypted);

    printf("\nPress Enter to continue...");
    getchar();
}

void vernam_menu() {
    unsigned char input[MAX_INPUT_SIZE] = {0};
    unsigned char key[MAX_INPUT_SIZE] = {0};
    unsigned char encrypted[MAX_INPUT_SIZE] = {0};
    unsigned char decrypted[MAX_INPUT_SIZE] = {0};
    size_t input_length = 0;

    clear_screen();
    printf("=== Vernam (One-Time Pad) Encryption/Decryption ===\n\n");

    // Get input text
    read_input(input, MAX_INPUT_SIZE, &input_length);

    // Generate random key of the same length
    vernam_generate_key(key, input_length);

    // Encrypt
    vernam_encrypt(input, encrypted, key, input_length);

    printf("\nPlaintext: %s\n", input);
    printf("\nGenerated key in hex:\n");
    print_hex(key, input_length);
    printf("\nCiphertext in hex:\n");
    print_hex(encrypted, input_length);

    // Decrypt
    vernam_decrypt(encrypted, decrypted, key, input_length);
    printf("\nDecrypted text: %s\n", decrypted);

    printf("\nPress Enter to continue...");
    getchar();
}

int main() {
    int choice = 0;

    while (1) {
        clear_screen();
        printf("=== Encryption Algorithm Selection ===\n\n");
        printf("1. DES (Data Encryption Standard)\n");
        printf("2. RSA (Rivest-Shamir-Adleman)\n");
        printf("3. Vernam Cipher (One-Time Pad)\n");
        printf("4. Exit\n\n");
        printf("Enter your choice (1-4): ");

        if (scanf("%d", &choice) != 1) {
            // Clear input buffer if invalid input
            while (getchar() != '\n');
            continue;
        }

        // Clear the newline character from the input buffer
        getchar();

        switch (choice) {
            case 1:
                des_menu();
                break;
            case 2:
                rsa_menu();
                break;
            case 3:
                vernam_menu();
                break;
            case 4:
                printf("Exiting program...\n");
                return 0;
            default:
                printf("Invalid choice. Press Enter to try again...");
                getchar();
        }
    }

    return 0;
}