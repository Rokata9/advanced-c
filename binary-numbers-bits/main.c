#include <math.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int get_nth_bit(int num, int n) {
    return (num >> n) & 1U;
}

// need to use manual implementation as double results
// in errors when converting to int
long long ten_pow_long_long(int n) {
    if (n == 0) {
        return 1;
    }

    long long result = 10;

    for (int i = 1; i < n; i++) {
        result *= 10;
    }

    return result;
}

long long decimal_to_binary(int n) {
    int max_bit = 19;
    long long result = 0;
    int bit = 0;

    // 10^19 doesn't fit in long long, so we only use bits 0..18 (19 bits)
    while (bit < max_bit) {
        int bit_value = (n >> bit) & 1U;

        // printf("Bit #%d value: %d\n", bit, bit_value);

        if (bit_value == 1) {
            result += ten_pow_long_long(bit);
            // printf("Running total: %lld\n", result);
        }

        bit++;
    }

    return result;
}

int binary_to_decimal(long long bin) {
    int long_long_bits_size = sizeof(long long) * 8;
    int sign = get_nth_bit(bin, long_long_bits_size-1);
    int result = 0;
    int i = 0;

    if (1 == sign) {
        bin = ~bin;
        bin += 1;
    }

    while (0 != bin) {
        int remainder = bin % 10;
        result += remainder * pow(2, i);
        bin /= 10;
        ++i;
    }

    return result * (sign == 1 ? -1 : 1);
}


int main(void) {
    long long x = 100001010; // (long long)0b1111111111111111111111111111111111111111111111111111111111111011ULL; // -5
    
    int dec = binary_to_decimal(x);
    printf("Decimal: %d\n", dec);

    int num = -5;
    long long bin = decimal_to_binary(num);
    printf("Binary: %lld", bin);
}
