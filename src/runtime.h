#ifndef RUNTIME_H
#define RUNTIME_H

#include <stdbool.h>

typedef enum variable_type variable_type;

typedef struct variable variable;
typedef struct return_t return_t;

variable* new_undefined();
variable* new_null();
variable* new_boolean(bool);
variable* new_number(double);
variable* new_string(char*);
char* native_toString(variable*);

enum variable_type {
    UNDEFINED_VARIABLE_TYPE,
    NULL_VARIABLE_TYPE,
    BOOLEAN_VARIABLE_TYPE,
    NUMBER_VARIABLE_TYPE,
    STRING_VARIABLE_TYPE
};

struct variable {
    variable_type type;
    void* value;
    variable* (*getMember)(char*);
};

struct return_t {
    char* error;
    variable* value;
};

#endif