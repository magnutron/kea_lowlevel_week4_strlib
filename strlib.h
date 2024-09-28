#ifndef STRLIB_H
#define STRLIB_H

#include <stddef.h>

void str_concat(char *dest, const char *src);
size_t str_length(const char *str);
int str_indexOf(const char *str, const char *search);
int str_lastIndexOf(const char *str, const char *search);
int str_startsWith(const char *str, const char *prefix);
int str_endsWith(const char *str, const char *suffix);
void str_toLowerCase(char *str);
void str_toUpperCase(char *str);
void str_trim(char *str);
void str_slice(const char *str, size_t start, size_t end, char *result);
void str_padEnd(char *str, size_t length, const char *padStr);
void str_repeat(char *result, const char *str, size_t count);

#endif // STRLIB_H
