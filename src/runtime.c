#include "runtime.h"

#include <stdbool.h>
#include <stdlib.h>
#include "string.h"

static variable* new_variable();
static variable* getMember();

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
        case STRING_VARIABLE_TYPE:
            return (char*) var->value;
    }
};

static variable* getMember(char* name) {
    return new_undefined();
}

static variable* new_variable() {
    variable* var = (variable*) calloc(1, sizeof(variable));
    var->type = UNDEFINED_VARIABLE_TYPE;
    var->value = NULL;
    var->getMember = getMember;
    return var;
}
