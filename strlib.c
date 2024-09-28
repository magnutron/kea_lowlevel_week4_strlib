#include <stdio.h>
#include <string.h>

char toLower(char ch) {
    if (ch >= 'A' && ch <= 'Z') {
        return ch + ('a' - 'A');
    }
    return ch;
}

char toUpper(char ch) {
    if (ch >= 'a' && ch <= 'z') {
        return ch - ('a' - 'A');
    }
    return ch;
}

int isSpace(char ch) {
    return (ch == ' ' || ch == '\t' || ch == '\n' || 
            ch == '\r' || ch == '\v' || ch == '\f');
}

void str_concat(char *dest, const char *src) {
    while (*dest) dest++;
    while ((*dest++ = *src++));
}

size_t str_length(const char *str) {
    const char *s = str;
    while (*s) s++;
    return s - str;
}

int str_indexOf(const char *str, const char *search) {
    const char *p = strstr(str, search);
    return p ? (int)(p - str) : -1;
}

int str_lastIndexOf(const char *str, const char *search) {
    const char *p = strrstr(str, search);
    return p ? (int)(p - str) : -1;
}

int str_startsWith(const char *str, const char *prefix) {
    size_t len = strlen(prefix);
    return strncmp(str, prefix, len) == 0;
}

int str_endsWith(const char *str, const char *suffix) {
    size_t len = strlen(suffix);
    size_t str_len = str_length(str);
    return str_len >= len && strcmp(str + str_len - len, suffix) == 0;
}

void str_toLowerCase(char *str) {
    while (*str) {
        *str = toLower(*str);
        str++;
    }
}

void str_toUpperCase(char *str) {
    while (*str) {
        *str = toUpper(*str);
        str++;
    }
}

void str_trim(char *str) {
    char *end;

    while (isSpace(*str)) str++;

    end = str + strlen(str) - 1;
    while (end > str && isSpace(*end)) end--;

    *(end + 1) = '\0';
}

void str_slice(const char *str, size_t start, size_t end, char *result) {
    size_t len = str_length(str);
    if (start >= len) {
        result[0] = '\0';
        return;
    }
    if (end > len) end = len;
    size_t j = 0;
    for (size_t i = start; i < end; i++) {
        result[j++] = str[i];
    }
    result[j] = '\0';
}

void str_padEnd(char *str, size_t length, const char *padStr) {
    size_t str_len = str_length(str);
    while (str_len < length) {
        str_concat(str, padStr);
        str_len = str_length(str);
    }
    str[str_len] = '\0';
}

void str_repeat(char *result, const char *str, size_t count) {
    result[0] = '\0'; 
    for (size_t i = 0; i < count; i++) {
        str_concat(result, str);
    }
}
