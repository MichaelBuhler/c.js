#include "runtime.h"

#include <stdlib.h>

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
