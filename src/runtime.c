#include "runtime.h"

#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static variable* new_variable();
static void createMember(char*);
static variable* getMember(char*);
static variable* setMember(char*, variable*);
static return_t call(variable*, int, ...);

variable* new_scope(variable* parentScope) {
    return new_undefined(); // TODO
}

variable* new_undefined() {
    return new_variable();
}

variable* new_null() {
    variable* var = new_variable();
    var->type = NULL_VARIABLE_TYPE;
    return var;
}

variable* new_boolean(bool value) {
    variable* var = new_variable();
    var->type = BOOLEAN_VARIABLE_TYPE;
    bool* tmp = var->value = (bool*) calloc(1, sizeof(bool));
    *tmp = value;
    return var;

}

variable* new_number(double value) {
    variable* var = new_variable();
    var->type = NUMBER_VARIABLE_TYPE;
    double* tmp = var->value = (double*) calloc(1, sizeof(double));
    *tmp = value;
    return var;
}

variable* new_string(char* string) {
    variable* var = new_variable();
    var->type = STRING_VARIABLE_TYPE;
    char* tmp = var->value = (char*) calloc(1, strlen(string)+1);
    strcpy(tmp, string);
    return var;
}

char* native_toString(variable* var) {
    switch (var->type) {
        case UNDEFINED_VARIABLE_TYPE:
            return "undefined";
        case NULL_VARIABLE_TYPE:
            return "null";
        case BOOLEAN_VARIABLE_TYPE:
            if (*(bool*)var->value) {
                return "true";
            } else {
                return "false";
            }
        case NUMBER_VARIABLE_TYPE: {
            char* tmp = (char*) calloc(30, sizeof(char));
            sprintf(tmp, "%.18e", *(double*)var->value);
            tmp = (char*) realloc(tmp, strlen(tmp)+1);
            return tmp;
        }
        case STRING_VARIABLE_TYPE:
            return (char*) var->value;
    }
};

static return_t call(variable* scope, int argc, ...) {
    va_list varargs;
    va_start(varargs, argc);
    for ( int i = 0 ; i < argc ; i++ ) {
        // TODO
    }
    va_end(varargs);
    return_t ret;
    ret.value = new_undefined();
    return ret;
}

static variable* new_variable() {
    variable* var = (variable*) calloc(1, sizeof(variable));
    var->type = UNDEFINED_VARIABLE_TYPE;
    var->value = NULL;
    var->createMember = createMember;
    var->getMember = getMember;
    var->setMember = setMember;
    var->call = call;
    return var;
}

static void createMember(char* name) {
    // TODO
}

static variable* getMember(char* name) {
    // TODO
    return new_undefined();
}

static variable* setMember(char* name, variable* value) {
    // TODO
    return value;
}
