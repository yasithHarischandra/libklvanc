#include <stdint.h>

/**
 * @brief	Alternative function for GCC builtin __builtin_parity
 * @param[x]	uint16_t x, integer value to calculate parity
 * @return      Calculated parity
 */
int __builtin_parity(uint16_t x) {
    int result = 0;
    while (x) {
        result ^= 1;
        x &= x - 1; // This removes the lowest set bit
    }
    return result;
}