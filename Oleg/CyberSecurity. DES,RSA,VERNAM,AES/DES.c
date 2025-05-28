/**
 * des.c
 *
 * Реализация алгоритма Data Encryption Standard (DES)
 *
 * Эта реализация следует спецификации FIPS 46-3 для DES
 */

#include "des.h"
#include <stdio.h>
#include <string.h>
#include "utils.h"

// Таблицы для алгоритма DES
// Начальная перестановка (IP)
static const int initial_permutation[64] = {
        58, 50, 42, 34, 26, 18, 10, 2,
        60, 52, 44, 36, 28, 20, 12, 4,
        62, 54, 46, 38, 30, 22, 14, 6,
        64, 56, 48, 40, 32, 24, 16, 8,
        57, 49, 41, 33, 25, 17, 9, 1,
        59, 51, 43, 35, 27, 19, 11, 3,
        61, 53, 45, 37, 29, 21, 13, 5,
        63, 55, 47, 39, 31, 23, 15, 7
};

// Конечная перестановка (IP^-1)
static const int final_permutation[64] = {
        40, 8, 48, 16, 56, 24, 64, 32,
        39, 7, 47, 15, 55, 23, 63, 31,
        38, 6, 46, 14, 54, 22, 62, 30,
        37, 5, 45, 13, 53, 21, 61, 29,
        36, 4, 44, 12, 52, 20, 60, 28,
        35, 3, 43, 11, 51, 19, 59, 27,
        34, 2, 42, 10, 50, 18, 58, 26,
        33, 1, 41, 9, 49, 17, 57, 25
};

// Таблица расширения (E-bit selection table)
static const int expansion_table[48] = {
        32, 1, 2, 3, 4, 5,
        4, 5, 6, 7, 8, 9,
        8, 9, 10, 11, 12, 13,
        12, 13, 14, 15, 16, 17,
        16, 17, 18, 19, 20, 21,
        20, 21, 22, 23, 24, 25,
        24, 25, 26, 27, 28, 29,
        28, 29, 30, 31, 32, 1
};

// Функция перестановки (P-box)
static const int permutation[32] = {
        16, 7, 20, 21, 29, 12, 28, 17,
        1, 15, 23, 26, 5, 18, 31, 10,
        2, 8, 24, 14, 32, 27, 3, 9,
        19, 13, 30, 6, 22, 11, 4, 25
};

// S-блоки (Substitution boxes)
static const int sbox[8][4][16] = {
        {   // S1
                {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
                {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
                {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
                {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}
        },
        {   // S2
                {15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
                {3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
                {0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},
                {13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9}
        },
        {   // S3
                {10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
                {13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
                {13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},
                {1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12}
        },
        {   // S4
                {7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15},
                {13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9},
                {10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4},
                {3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14}
        },
        {   // S5
                {2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9},
                {14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6},
                {4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14},
                {11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3}
        },
        {   // S6
                {12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11},
                {10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8},
                {9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6},
                {4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13}
        },
        {   // S7
                {4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1},
                {13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6},
                {1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2},
                {6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12}
        },
        {   // S8
                {13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7},
                {1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},
                {7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8},
                {2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}
        }
};

// Таблицы перестановки ключей
// Permuted Choice 1 (PC-1)
static const int pc1[56] = {
        57, 49, 41, 33, 25, 17, 9,
        1, 58, 50, 42, 34, 26, 18,
        10, 2, 59, 51, 43, 35, 27,
        19, 11, 3, 60, 52, 44, 36,
        63, 55, 47, 39, 31, 23, 15,
        7, 62, 54, 46, 38, 30, 22,
        14, 6, 61, 53, 45, 37, 29,
        21, 13, 5, 28, 20, 12, 4
};

// Permuted Choice 2 (PC-2)
static const int pc2[48] = {
        14, 17, 11, 24, 1, 5,
        3, 28, 15, 6, 21, 10,
        23, 19, 12, 4, 26, 8,
        16, 7, 27, 20, 13, 2,
        41, 52, 31, 37, 47, 55,
        30, 40, 51, 45, 33, 48,
        44, 49, 39, 56, 34, 53,
        46, 42, 50, 36, 29, 32
};

// Расписание сдвигов ключей - количество циклических сдвигов влево на каждом раунде
static const int key_shifts[16] = {
        1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1
};

// Вспомогательные функции

// Получить значение бита в указанной позиции
static int get_bit(uint64_t data, int position) {
    return (data >> (63 - position)) & 1;
}

// Установить значение бита в указанной позиции
static uint64_t set_bit(uint64_t data, int position, int value) {
    if (value)
        return data | ((uint64_t)1 << (63 - position));
    else
        return data & ~((uint64_t)1 << (63 - position));
}


static uint64_t permute(uint64_t input, const int *permutation_table, int output_size) {
    uint64_t output = 0;
    for (int i = 0; i < output_size; i++) {
        int bit = get_bit(input, permutation_table[i] - 1);
        output = set_bit(output, i, bit);
    }
    return output;
}

// Выполнить циклический сдвиг влево 28-битного значения
static uint32_t circular_left_shift(uint32_t value, int shift_count) {
    return ((value << shift_count) | (value >> (28 - shift_count))) & 0x0FFFFFFF;
}

// Сгенерировать 16 раундовых ключей из основного ключа
static void generate_subkeys(uint64_t key, uint64_t *subkeys) {
    // Применить перестановку PC-1 к ключу
    uint64_t permuted_choice_1 = permute(key, pc1, 56);

    // Разделить на левую и правую половины
    uint32_t c = (uint32_t)((permuted_choice_1 >> 28) & 0x0FFFFFFF);
    uint32_t d = (uint32_t)(permuted_choice_1 & 0x0FFFFFFF);

    // Сгенерировать 16 подключей с вращениями
    for (int i = 0; i < 16; i++) {
        // Выполнить соответствующий левый сдвиг
        c = circular_left_shift(c, key_shifts[i]);
        d = circular_left_shift(d, key_shifts[i]);

        // Объединить c и d
        uint64_t combined = ((uint64_t)c << 28) | d;

        // Применить перестановку PC-2 для генерации под-ключа
        subkeys[i] = permute(combined, pc2, 48);
    }
}

// F-функция в сети Фейстеля
static uint32_t f_function(uint32_t r, uint64_t subkey) {
    // Расширить R с 32 до 48 бит с использованием таблицы расширения
    uint64_t expanded_r = 0;
    for (int i = 0; i < 48; i++) {
        int bit = (r >> (31 - (expansion_table[i] - 1))) & 1;
        expanded_r = expanded_r | ((uint64_t)bit << (47 - i));
    }

    // XOR с подключом
    uint64_t xored = expanded_r ^ subkey;

    // Применить S-блоки
    uint32_t s_output = 0;
    for (int i = 0; i < 8; i++) {
        // Извлечь 6 бит для этого S-блока
        int six_bits = (xored >> (42 - i * 6)) & 0x3F;

        // Вычислить строку и столбец для поиска в S-блоке
        int row = ((six_bits & 0x20) >> 4) | (six_bits & 0x01);
        int col = (six_bits >> 1) & 0x0F;

        // Подстановка S-блока
        int s_value = sbox[i][row][col];

        // Добавить 4-битный выход S-блока к нашему результату
        s_output |= (s_value << (28 - i * 4));
    }

    // Применить перестановку (P-Box)
    uint32_t output = 0;
    for (int i = 0; i < 32; i++) {
        int bit = (s_output >> (31 - (permutation[i] - 1))) & 1;
        output |= (bit << (31 - i));
    }

    return output;
}

// Один раунд DES
static void des_round(uint32_t *left, uint32_t *right, uint64_t subkey) {
    uint32_t temp = *right;
    *right = *left ^ f_function(*right, subkey);
    *left = temp;
}

// Основная функция шифрования DES для одного блока
uint64_t des_encrypt_block(uint64_t block, uint64_t key) {
    uint64_t subkeys[16];
    generate_subkeys(key, subkeys);

    // Начальная перестановка
    block = permute(block, initial_permutation, 64);

    // Разделить блок на левую и правую половины
    uint32_t left = (uint32_t)(block >> 32);
    uint32_t right = (uint32_t)(block & 0xFFFFFFFF);

    // 16 раундов обработки
    for (int i = 0; i < 16; i++) {
        des_round(&left, &right, subkeys[i]);
    }

    // Поменять местами левую и правую половины (отменить последнюю перестановку последнего раунда)
    uint64_t combined = ((uint64_t)right << 32) | left;

    // Конечная перестановка
    return permute(combined, final_permutation, 64);
}

// Основная функция дешифрования DES для одного блока
uint64_t des_decrypt_block(uint64_t block, uint64_t key) {
    uint64_t subkeys[16];
    generate_subkeys(key, subkeys);

    // Начальная перестановка
    block = permute(block, initial_permutation, 64);

    // Разделить блок на левую и правую половины
    uint32_t left = (uint32_t)(block >> 32);
    uint32_t right = (uint32_t)(block & 0xFFFFFFFF);

    // 16 раундов обработки (с использованием ключей в обратном порядке)
    for (int i = 15; i >= 0; i--) {
        des_round(&left, &right, subkeys[i]);
    }

    // Поменять местами левую и правую половины
    uint64_t combined = ((uint64_t)right << 32) | left;

    // Конечная перестановка
    return permute(combined, final_permutation, 64);
}

// Преобразовать массив байтов в 64-битное целое число (big-endian)
uint64_t bytes_to_uint64(const unsigned char *bytes) {
    uint64_t result = 0;
    for (int i = 0; i < 8; i++) {
        result = (result << 8) | bytes[i];
    }
    return result;
}

// Преобразовать 64-битное целое число в массив байтов (big-endian)
void uint64_to_bytes(uint64_t value, unsigned char *bytes) {
    for (int i = 7; i >= 0; i--) {
        bytes[i] = value & 0xFF;
        value >>= 8;
    }
}

// Зашифровать блок данных (8 байтов)
void encrypt_block(const unsigned char *input, unsigned char *output, uint64_t key) {
    uint64_t input_block = bytes_to_uint64(input);
    uint64_t output_block = des_encrypt_block(input_block, key);
    uint64_to_bytes(output_block, output);
}

// Расшифровать блок данных (8 байтов)
void decrypt_block(const unsigned char *input, unsigned char *output, uint64_t key) {
    uint64_t input_block = bytes_to_uint64(input);
    uint64_t output_block = des_decrypt_block(input_block, key);
    uint64_to_bytes(output_block, output);
}

// Зашифровать данные произвольной длины (используя режим Electronic Codebook)
// Примечание: В реальных приложениях обычно используется более безопасный режим, например CBC
void des_encrypt_ecb(const unsigned char *input, unsigned char *output,
                     size_t length, uint64_t key) {
    // Дополнить входные данные до кратности размера блока, если необходимо
    size_t padded_length = ((length + DES_BLOCK_SIZE - 1) / DES_BLOCK_SIZE) * DES_BLOCK_SIZE;

    // Обработать каждый блок
    for (size_t i = 0; i < padded_length; i += DES_BLOCK_SIZE) {
        // Создать временный входной блок (с нулевым заполнением, если нужно)
        unsigned char block_input[DES_BLOCK_SIZE] = {0};
        for (size_t j = 0; j < DES_BLOCK_SIZE && (i + j) < length; j++) {
            block_input[j] = input[i + j];
        }

        // Зашифровать блок
        encrypt_block(block_input, output + i, key);
    }
}

// Расшифровать данные произвольной длины (используя режим Electronic Codebook)
void des_decrypt_ecb(const unsigned char *input, unsigned char *output,
                     size_t length, uint64_t key) {
    // Обработать каждый блок
    for (size_t i = 0; i < length; i += DES_BLOCK_SIZE) {
        decrypt_block(input + i, output + i, key);
    }
}

// Вспомогательная функция для печати байтов в шестнадцатеричном формате
void print_hex(const unsigned char *data, size_t length) {
    for (size_t i = 0; i < length; i++) {
        printf("%02X ", data[i]);
        if ((i + 1) % 8 == 0) printf("\n");
    }
    if (length % 8 != 0) printf("\n");
}

// Напечатать необработанный зашифрованный текст (может содержать непечатаемые символы)
void print_raw(const unsigned char *data, size_t length) {
    printf("Необработанные зашифрованные данные (могут включать непечатаемые символы):\n");

    // Записать непосредственно в stdout
    fwrite(data, 1, length, stdout);
    printf("\n");

    printf("\nПредставление в стиле C с экранированием:\n\"");
    for (size_t i = 0; i < length; i++) {
        unsigned char c = data[i];
        if (c >= 32 && c <= 126) {
            printf("%c", c);
        } else {
            printf("\\x%02X", c);
        }
    }
    printf("\"\n");
}

#ifdef DES_TEST
#include <stdio.h>

int main() {
    // Пример ключа (8 байтов = 64 бита, хотя эффективно используется только 56 бит)
    unsigned char key_bytes[8] = {0x13, 0x34, 0x57, 0x79, 0x9B, 0xBC, 0xDF, 0xF1};
    uint64_t key = bytes_to_uint64(key_bytes);

    // Пример открытого текста (16 байтов = 2 блока)
    unsigned char plaintext[16] = "Hello, DES!";
    printf("Исходный открытый текст: %s\n", plaintext);
    printf("Открытый текст в hex:\n");
    print_hex(plaintext, 16);

    // Зашифровать открытый текст
    unsigned char ciphertext[16];
    des_encrypt_ecb(plaintext, ciphertext, 16, key);

    // Напечатать зашифрованный текст в разных форматах
    printf("\nЗашифрованный текст в hex:\n");
    print_hex(ciphertext, 16);

    // Напечатать необработанный зашифрованный текст в консоль
    printf("\n");
    print_raw(ciphertext, 16);

    // Расшифровать зашифрованный текст
    unsigned char decrypted[16];
    des_decrypt_ecb(ciphertext, decrypted, 16, key);
    printf("\nРасшифрованный текст: %s\n", decrypted);
    printf("Расшифрованный текст в hex:\n");
    print_hex(decrypted, 16);

    // Сравнить исходный и расшифрованный тексты
    if (memcmp(plaintext, decrypted, 12) == 0) { // Сравниваем первые 12 байт "Hello, DES!"
        printf("\nШифрование и дешифрование прошли успешно!\n");
    } else {
        printf("\nОшибка: Расшифрованный текст не совпадает с исходным.\n");
    }

    return 0;
}
#endif