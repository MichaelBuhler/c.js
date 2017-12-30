#include <stdlib.h>
#include <string.h>
#include "args.h"
#include "string_utils.h"

static int count;
static char** arguments;

void args_init(int argc, char** argv) {
    count = argc;
    arguments = (char**) calloc(count, sizeof(char*));
    for ( int i = 0 ; i < count ; i++ ) {
        arguments[i] = new_string(argv[i]);
    }
}

char args_flag(char* name) {
    for ( int i = 0 ; i < count ; i++ ) {
        if ( strcmp(name, arguments[i]) == 0 ) {
            return 1;
        }
    }
    return 0;
}

char args_either(char* name, char* otherName) {
    return args_flag(name) || args_flag(otherName);
}

char* args_value(char* name) {
    for ( int i = 0 ; i < count ; i++ ) {
        if ( strcmp(name, arguments[i]) == 0 && i+1<count) {
            return arguments[i+1];
        }
    }
    return NULL;
}
