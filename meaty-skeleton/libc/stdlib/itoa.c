#include <stddef.h>

void itoa(int num, char* buffer, int base) {
    char digits[] = "0123456789abcdef";
    int i = 0;
    int is_negative = 0;

    // Handle special case for 0
    if (num == 0) {
        buffer[i++] = '0';
        buffer[i] = '\0';
        return;
    }

    // Handle negative numbers for decimal base
    if (num < 0 && base == 10) {
        is_negative = 1;
        num = -num;
    }

    // Convert number to the desired base
    while (num != 0) {
        buffer[i++] = digits[num % base];
        num /= base;
    }

    // If the number was negative, add '-' sign for decimal
    if (is_negative) {
        buffer[i++] = '-';
    }

    buffer[i] = '\0';

    // Reverse the string to get the correct order
    int start = 0;
    int end = i - 1;
    while (start < end) {
        char temp = buffer[start];
        buffer[start] = buffer[end];
        buffer[end] = temp;
        start++;
        end--;
    }
}
