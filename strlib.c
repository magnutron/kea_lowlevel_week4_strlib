#include <stdio.h>
#include <string.h>

// Helper function to detect if a byte is an ASCII character
int is_ascii(unsigned char ch) {
    return ch <= 0x7F;
}

// Helper function to determine the length of a UTF-8 code point based on the first byte
int utf8_char_length(unsigned char ch) {
    if (ch <= 0x7F) {
        return 1; // ASCII
    } else if ((ch & 0xE0) == 0xC0) {
        return 2; // 2-byte sequence
    } else if ((ch & 0xF0) == 0xE0) {
        return 3; // 3-byte sequence
    } else if ((ch & 0xF8) == 0xF0) {
        return 4; // 4-byte sequence
    }
    return 1; // Fallback to 1 (invalid byte)
}

// Helper function to move to the next UTF-8 character in a string
const char* utf8_next_char(const char *str) {
    int char_len = utf8_char_length((unsigned char)*str);
    return str + char_len;
}

// Function to find the nth code point index in the string
const char* utf8_codepoint_at(const char *str, size_t index) {
    size_t i = 0;
    while (*str && i < index) {
        str = utf8_next_char(str);
        i++;
    }
    return str;
}

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

// Updated str_length function to count UTF-8 code points
size_t str_length(const char *str) {
    size_t len = 0;
    while (*str) {
        int char_len = utf8_char_length((unsigned char)*str);
        str += char_len; // Move to the next character (UTF-8 code point)
        len++;           // Count one code point
    }
    return len;
}

// Updated str_indexOf to handle UTF-8 code points
int str_indexOf(const char *str, const char *search) {
    const char *p = str;
    size_t str_len = str_length(str);
    size_t search_len = str_length(search);

    for (size_t i = 0; i <= str_len - search_len; i++) {
        if (strncmp(utf8_codepoint_at(str, i), search, strlen(search)) == 0) {
            return i;
        }
    }
    return -1;  // Return -1 if not found
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

// Updated str_slice to handle UTF-8 code points
void str_slice(const char *str, size_t start, size_t end, char *result) {
    const char *start_ptr = utf8_codepoint_at(str, start);
    const char *end_ptr = utf8_codepoint_at(str, end);
    size_t slice_len = end_ptr - start_ptr;
    strncpy(result, start_ptr, slice_len);
    result[slice_len] = '\\0';  // Null-terminate the result
}

// Updated str_padEnd to handle UTF-8 code points
void str_padEnd(const char *str, size_t targetLength, const char *padStr, char *result) {
    size_t str_len = str_length(str);
    if (str_len >= targetLength) {
        strcpy(result, str);
        return;
    }

    strcpy(result, str);
    size_t remainingLength = targetLength - str_len;
    size_t padStr_len = str_length(padStr);

    // Append the padding string repeatedly until the desired length is reached
    while (remainingLength > 0) {
        strncat(result, padStr, remainingLength < padStr_len ? remainingLength : padStr_len);
        remainingLength -= (remainingLength < padStr_len ? remainingLength : padStr_len);
    }
}

// Updated str_repeat to handle UTF-8 code points
void str_repeat(const char *str, size_t count, char *result) {
    result[0] = '\\0';  // Initialize the result string as empty
    for (size_t i = 0; i < count; i++) {
        strcat(result, str);
    }
}

// Updated str_substring to extract substrings based on UTF-8 code points
void str_substring(const char *str, size_t start, size_t end, char *result) {
    str_slice(str, start, end, result);
}
