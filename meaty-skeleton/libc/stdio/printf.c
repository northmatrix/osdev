#include <limits.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static bool print(const char* data, size_t length) {
	const unsigned char* bytes = (const unsigned char*) data;
	for (size_t i = 0; i < length; i++)
		if (putchar(bytes[i]) == EOF)
			return false;
	return true;
}

int printf(const char* restrict format, ...) {
    va_list parameters;
    va_start(parameters, format);

    int written = 0;

    while (*format != '\0') {
        size_t maxrem = INT_MAX - written;

        if (format[0] != '%' || format[1] == '%') {
            if (format[0] == '%')
                format++;
            size_t amount = 1;
            while (format[amount] && format[amount] != '%')
                amount++;
            if (maxrem < amount) {
                return -1;
            }
            if (!print(format, amount))
                return -1;
            format += amount;
            written += amount;
            continue;
        }

        const char* format_begun_at = format++;

        if (*format == 'c') {
            format++;
            char c = (char) va_arg(parameters, int /* char promotes to int */);
            if (!maxrem) {
                return -1;
            }
            if (!print(&c, sizeof(c)))
                return -1;
            written++;
        } else if (*format == 'd') {
            format++;
            int num = va_arg(parameters, int);
            char buffer[20];
            itoa(num, buffer, 10);
            size_t len = strlen(buffer);
            if (maxrem < len) return -1;
            if (!print(buffer, len)) return -1;
            written += len;
        } else if (*format == 's') {
            format++;
            const char* str = va_arg(parameters, const char*);
            size_t len = strlen(str);
            if (maxrem < len) {
                return -1;
            }
            if (!print(str, len))
                return -1;
            written += len;
        } else if (*format == 'x') {  // Hexadecimal format
            format++;
            unsigned int num = va_arg(parameters, unsigned int);
            char buffer[20];
            itoa(num, buffer, 16);
            size_t len = strlen(buffer);
            if (maxrem < len) {
                return -1;
            }
            if (!print(buffer, len))
                return -1;
            written += len;
        } else if (*format == 'l' && *(format + 1) == 'x') {  // Long hexadecimal format (%lx)
            format += 2;

            unsigned long num_high = va_arg(parameters, unsigned long);
            unsigned long num_low = va_arg(parameters, unsigned long);

            char buffer[17];  // 16 hex digits + null terminator
            int len = 0;

            // Combine the high and low parts into a single 64-bit value
            unsigned long long combined = ((unsigned long long) num_high << 32) | num_low;

            // Convert to hexadecimal (base 16)
            while (combined != 0) {
                int rem = combined % 16;
                buffer[len++] = (rem < 10) ? ('0' + rem) : ('a' + (rem - 10));
                combined /= 16;
            }

            // If the number is 0, ensure at least one character (0)
            if (len == 0) {
                buffer[len++] = '0';
            }

            // Reverse the buffer to get the correct order
            for (int i = 0; i < len / 2; i++) {
                char tmp = buffer[i];
                buffer[i] = buffer[len - i - 1];
                buffer[len - i - 1] = tmp;
            }

            // Print the hex number
            if (maxrem < len) {
                return -1;
            }
            if (!print(buffer, len))
                return -1;
            written += len;
        } else {
            format = format_begun_at;
            size_t len = strlen(format);
            if (maxrem < len) {
                return -1;
            }
            if (!print(format, len))
                return -1;
            written += len;
            format += len;
        }
    }

    va_end(parameters);
    return written;
}
