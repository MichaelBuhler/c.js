#ifndef RUNTIME_H
#define RUNTIME_H

#include <stdbool.h>
#include "hashtable.h"

typedef enum VariableType VariableType;

typedef struct Scope Scope;
typedef struct Variable Variable;
typedef struct Return Return;

Scope* new_Scope(Scope* parentScope);
Variable* new_undefined();
Variable* new_null();
Variable* new_boolean(bool);
Variable* new_number(double);
Variable* new_string(char*);

char* native_toString(Variable*);

enum VariableType {
    UNDEFINED_VARIABLE_TYPE,
    NULL_VARIABLE_TYPE,
    BOOLEAN_VARIABLE_TYPE,
    NUMBER_VARIABLE_TYPE,
    STRING_VARIABLE_TYPE
};

struct Scope {
    Scope* parent;
    hashtable_t* hashtable;
    void (*defineVariable)(Scope*, char*);
    Variable* (*getVariable)(Scope*, char*);
    void (*setVariable)(Scope*, char*, Variable*);
};

struct Variable {
    enum VariableType type;
    void* value;
    Variable* (*getMember)(char*);
    void (*setMember)(char*, Variable*);
    Return (*call)(Scope*, int, ...);
};

struct Return {
    char* error;
    Variable* value;
};

#endif