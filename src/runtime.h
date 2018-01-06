#ifndef RUNTIME_H
#define RUNTIME_H

#include <stdbool.h>
#include "hashtable.h"

typedef enum VariableType VariableType;

typedef struct Scope Scope;
typedef struct Variable Variable;
typedef struct Object Object;
typedef struct Return Return;

void initialize_runtime(Scope*);
Scope* new_Scope(Scope*);
Object* new_Object();
Variable* new_undefined();
Variable* new_null();
Variable* new_boolean(bool);
Variable* new_number(double);
Variable* new_string(char*);
Variable* new_function(Return (*)(Scope*, Object*));

char* native_toString(Variable*);
Object* native_toObject(Variable*);

enum VariableType {
    UNDEFINED_VARIABLE_TYPE,
    NULL_VARIABLE_TYPE,
    BOOLEAN_VARIABLE_TYPE,
    NUMBER_VARIABLE_TYPE,
    STRING_VARIABLE_TYPE,
    OBJECT_VARIABLE_TYPE
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
};

struct Object {
    hashtable_t* properties;
    hashtable_t* internalProperties;
    Variable* (*getProperty)(Object*, char*);
    void (*setProperty)(Object*, char*, Variable*);
    Return (*call)(Object*, Scope*, int, ...);
};

struct Return {
    char* error;
    Variable* value;
};

#endif