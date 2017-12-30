#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include "args.h"
#include "string_utils.h"

static int argumentCount;
static char** arguments;

void args_init(int argc, char** argv) {
    argumentCount = argc - 1;
    arguments = (char**) calloc(argumentCount, sizeof(char*));
    for ( int i = 0 ; i < argumentCount ; i++ ) {
        arguments[i] = new_string(argv[i+1]);
    }
}

char args_flag(char* name) {
    return args_flagv(1, name);
}

char args_flagv(int vaCount, ...) {
    va_list va;
    va_start(va, vaCount);
    for ( int i = 0 ; i < vaCount ; i++ ) {
        char* name = va_arg(va, char*);
        for ( int j = 0 ; j < argumentCount ; j++ ) {
            if ( strcmp(name, arguments[j]) == 0 ) {
                va_end(va);
                return 1;
            }
        }
    }
    va_end(va);
    return 0;
}

char* args_value(char* name) {
    for ( int i = 0 ; i < argumentCount ; i++ ) {
        if ( strcmp(name, arguments[i]) == 0 && i+1<argumentCount) {
            return arguments[i+1];
        }
    }
    return NULL;
}

int args_varargs(char** varargs) {
    int num = 0;
    for ( int i = 0 ; i < argumentCount ; i++ ) {
        if ( strncmp(arguments[i], "-", 1) == 0 ) {
            i++;
        } else {
            num++;
            if ( varargs != NULL ) {
                varargs = (char**) realloc(varargs, num * sizeof(char*));
                varargs[num-1] = new_string(arguments[i]);
            }
        }
    }
    return num;
}
