#include "runtime.h"

#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"

static Variable* new_Variable() {
    Variable* variable = (Variable*) calloc(1, sizeof(Variable));
    variable->type = UNDEFINED_VARIABLE_TYPE;
    variable->value = NULL;
    return variable;
}

static void Scope_defineVariable(Scope* scope, char* name) {
    ht_set(scope->hashtable, name, NULL);
}

static Variable* Scope_getVariable(Scope* scope, char* name) {
    Variable* variable = ht_get(scope->hashtable, name);
    if ( variable == NULL ) {
        Scope* parentScope = scope->parent;
        if ( parentScope == NULL ) {
            return new_undefined();
        } else {
            return parentScope->getVariable(parentScope, name);
        }
    } else {
        return variable;
    }
}

static void Scope_setVariable(Scope* scope, char* name, Variable* variable) {
    // TODO throw exception if variable is not defined
    ht_set(scope->hashtable, name, variable);
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

static Variable* Object_getProperty(Object* object, char* name) {
    Variable* variable = ht_get(object->properties, name);
    if ( variable == NULL ) {
        variable = ht_get(object->properties, "prototype");
        if ( variable == NULL ) {
            return new_undefined();
        } else {
            Object* prototype = (Object*) variable->value;
            return prototype->getProperty(prototype, name);
        }
    } else {
        return variable;
    }
}

static void Object_setProperty(Object* object, char* name, Variable* property) {
    ht_set(object->properties, name, property);
}

static Return Object_call(Object* object, Scope* scope, int argc, ...) {
    Return (*function)(Scope*, Object*) = (Return (*)(Scope*, Object*)) ht_get(object->internalProperties, "call");
    if ( function == NULL ) {
        // TODO this object is not a function, throw runtime exception
        Return ret;
        ret.error = "object is not a function";
        return ret;
    } else {
        va_list varargs;
        va_start(varargs, argc);
        Object* arguments = new_Object();
        for ( int i = 0 ; i < argc ; i++ ) {
            char* tmp = (char*) calloc(20, sizeof(char));
            sprintf(tmp, "%i", i);
            tmp = (char*) realloc(tmp, strlen(tmp)+1);
            arguments->setProperty(arguments, tmp, (Variable*) va_arg(varargs, Variable*));
            free(tmp);
        }
        va_end(varargs);
        return function(scope, arguments);
    }
}

Object* new_Object() {
    Object* object = (Object*) calloc(1, sizeof(Object));
    object->properties = ht_create(1);
    object->internalProperties = ht_create(1);
    object->getProperty = Object_getProperty;
    object->setProperty = Object_setProperty;
    object->call = Object_call;
    return object;
}

Variable* new_undefined() {
    return new_Variable();
}

Variable* new_null() {
    Variable* variable = new_Variable();
    variable->type = NULL_VARIABLE_TYPE;
    return variable;
}

Variable* new_boolean(bool value) {
    Variable* variable = new_Variable();
    variable->type = BOOLEAN_VARIABLE_TYPE;
    bool* tmp = variable->value = (bool*) calloc(1, sizeof(bool));
    *tmp = value;
    return variable;

}

Variable* new_number(double value) {
    Variable* variable = new_Variable();
    variable->type = NUMBER_VARIABLE_TYPE;
    double* tmp = variable->value = (double*) calloc(1, sizeof(double));
    *tmp = value;
    return variable;
}

Variable* new_string(char* string) {
    Variable* variable = new_Variable();
    variable->type = STRING_VARIABLE_TYPE;
    char* tmp = variable->value = (char*) calloc(1, strlen(string)+1);
    strcpy(tmp, string);
    return variable;
}

Variable* new_function(Return (*function)(Scope*, Object*)) {
    Object* object = new_Object();
    ht_set(object->internalProperties, "call", function);
    Variable* variable = new_Variable();
    variable->type = OBJECT_VARIABLE_TYPE;
    variable->value = object;
    return variable;
}

char* native_toString(Variable* variable) {
    switch (variable->type) {
        case UNDEFINED_VARIABLE_TYPE:
            return "undefined";
        case NULL_VARIABLE_TYPE:
            return "null";
        case BOOLEAN_VARIABLE_TYPE:
            if (*(bool*)variable->value) {
                return "true";
            } else {
                return "false";
            }
        case NUMBER_VARIABLE_TYPE: {
            char* tmp = (char*) calloc(30, sizeof(char));
            sprintf(tmp, "%.18e", *(double*)variable->value);
            tmp = (char*) realloc(tmp, strlen(tmp)+1);
            return tmp;
        }
        case STRING_VARIABLE_TYPE:
            return (char*) variable->value;
        case OBJECT_VARIABLE_TYPE:
            // TODO
            fprintf(stderr, "Unsupported Operation: called native_toString() on an Object\n");
            return "Unsupported Operation";
    }
};

Object* native_toObject(Variable* variable) {
    switch (variable->type) {
        case UNDEFINED_VARIABLE_TYPE:
            fprintf(stderr, "Unsupported Operation: called native_toObject on undefined\n");
            return new_Object();
        case NULL_VARIABLE_TYPE:
            fprintf(stderr, "Unsupported Operation: called native_toObject on null\n");
            return new_Object();
        case BOOLEAN_VARIABLE_TYPE:
            fprintf(stderr, "Unsupported Operation: called native_toObject on a boolean\n");
            return new_Object();
        case NUMBER_VARIABLE_TYPE:
            fprintf(stderr, "Unsupported Operation: called native_toObject on a number\n");
            return new_Object();
        case STRING_VARIABLE_TYPE:
            fprintf(stderr, "Unsupported Operation: called native_toObject on a string\n");
            return new_Object();
        case OBJECT_VARIABLE_TYPE:
            return (Object*) variable->value;
    }
}

void initialize_runtime(Scope* global) {

}