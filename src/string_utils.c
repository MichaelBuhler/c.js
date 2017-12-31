#include <stdlib.h>
#include <string.h>
#include "string_utils.h"

char* new_string(char* str) {
    char* string = (char*) calloc(1, sizeof(char));
    return concat(string, str);
}

char* concat(char* dest, char* src) {
    int length = strlen(dest) + strlen(src) + 1;
    dest = (char*) realloc(dest, length);
    strcat(dest, src);
    return dest;
}

char* concat_char(char* dest, char c) {
    int length = strlen(dest);
    dest = (char*) realloc(dest, length + 2);
    dest[length] = c;
    dest[length+1] = 0;
    return dest;
}

char* concat_indent(char* dest, char* src) {
    dest = concat(dest, "  ");
    for ( int i = 0 ; i < strlen(src) ; i++ ) {
        if ( src[i] == '\n' ) {
            dest = concat(dest, "\n  ");
        } else {
            dest = concat_char(dest, src[i]);
        }
    }
    return dest;
}

char* concat_comment(char* dest, char* src) {
    dest = concat(dest, "// ");
    for ( int i = 0 ; i < strlen(src) ; i++ ) {
        if ( src[i] == '\n' ) {
            dest = concat(dest, "\n// ");
        } else {
            dest = concat_char(dest, src[i]);
        }
    }
    return dest;
}
