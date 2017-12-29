#include <stdlib.h>
#include <string.h>
#include "string_utils.h"

char* concat(char* dest, char* src) {
    int length = strlen(dest) + strlen(src) + 1;
    dest = (char*) realloc(dest, length);
    strcat(dest, src);
    return dest;
}

char* concatc(char* dest, char c) {
    int length = strlen(dest);
    dest = (char*) realloc(dest, length + 2);
    dest[length] = c;
    dest[length+1] = 0;
    return dest;
}

char* new_string(char* str) {
    char* string = (char*) calloc(1, sizeof(char));
    return concat(string, str);
}

char* indent(char* src) {
    char* string = (char*) calloc(1, sizeof(char));
    string = concat(string, "  ");
    for (unsigned long i = 0 ; i < strlen(src) ; i++ ) {
        if ( src[i] == '\n' ) {
            string = concat(string, "\n  ");
        } else {
            char* tmp = (char*) calloc(2, sizeof(char));
            tmp[0] = src[i];
            string = concat(string, tmp);
            free(tmp);
        }
    }
    return string;
}