#include "runtime.h"

#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static Variable* new_variable();
static void createMember(char*);
static Variable* getMember(char*);
static Variable* setMember(char*, Variable*);
static Return call(Scope*, int, ...);

Scope* new_Scope(Scope* parentScope) {
    Scope* scope = (Scope*) calloc(1, sizeof(Scope));
    scope->parent = parentScope;
    scope->createMember = createMember;
    scope->getMember = getMember;
    scope->setMember = setMember;
    return scope;
}

Variable* new_undefined() {
    return new_variable();
}

Variable* new_null() {
    Variable* var = new_variable();
    var->type = NULL_VARIABLE_TYPE;
    return var;
}

Variable* new_boolean(bool value) {
    Variable* var = new_variable();
    var->type = BOOLEAN_VARIABLE_TYPE;
    bool* tmp = var->value = (bool*) calloc(1, sizeof(bool));
    *tmp = value;
    return var;

}

Variable* new_number(double value) {
    Variable* var = new_variable();
    var->type = NUMBER_VARIABLE_TYPE;
    double* tmp = var->value = (double*) calloc(1, sizeof(double));
    *tmp = value;
    return var;
}

Variable* new_string(char* string) {
    Variable* var = new_variable();
    var->type = STRING_VARIABLE_TYPE;
    char* tmp = var->value = (char*) calloc(1, strlen(string)+1);
    strcpy(tmp, string);
    return var;
}

char* native_toString(Variable* var) {
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

static Return call(Scope* scope, int argc, ...) {
    va_list varargs;
    va_start(varargs, argc);
    for ( int i = 0 ; i < argc ; i++ ) {
        // TODO
    }
    va_end(varargs);
    Return ret;
    ret.value = new_undefined();
    return ret;
}

static Variable* new_variable() {
    Variable* var = (Variable*) calloc(1, sizeof(Variable));
    var->type = UNDEFINED_VARIABLE_TYPE;
    var->value = NULL;
    var->getMember = getMember;
    var->setMember = setMember;
    var->call = call;
    return var;
}

static void createMember(char* name) {
    // TODO
}

static Variable* getMember(char* name) {
    // TODO
    return new_undefined();
}

static Variable* setMember(char* name, Variable* value) {
    // TODO
    return value;
}
