#include "runtime.h"

#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"

static Variable* Variable_getMember(char* name) {
    // TODO
    return new_undefined();
}

static void Variable_setMember(char* name, Variable* member) {
    // TODO
}

static Return Variable_call(Scope* scope, int argc, ...) {
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
    var->getMember = Variable_getMember;
    var->setMember = Variable_setMember;
    var->call = Variable_call;
    return var;
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

static void Scope_defineVariable(Scope* scope, char* name) {
    ht_set(scope->hashtable, name, NULL);
}

static Variable* Scope_getVariable(Scope* scope, char* name) {
    Variable* var = ht_get(scope->hashtable, name);
    if ( var == NULL ) {
        Scope* parentScope = scope->parent;
        if ( parentScope == NULL ) {
            return new_undefined();
        } else {
            return parentScope->getVariable(parentScope, name);
        }
    } else {
        return var;
    }
}

static void Scope_setVariable(Scope* scope, char* name, Variable* var) {
    ht_set(scope->hashtable, name, var);
}

Scope* new_Scope(Scope* parentScope) {
    Scope* scope = (Scope*) calloc(1, sizeof(Scope));
    scope->parent = parentScope;
    scope->hashtable = ht_create(1);
    scope->defineVariable = Scope_defineVariable;
    scope->getVariable = Scope_getVariable;
    scope->setVariable = Scope_setVariable;
    return scope;
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