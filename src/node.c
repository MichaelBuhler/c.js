#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "node.h"





char* concat(char* dest, char* src) {
    int length = strlen(dest) + strlen(src) + 1;
    dest = (char*) realloc(dest, length);
    strcat(dest, src);
    return dest;
}

char* new_string(char* str) {
    char* string = (char*) calloc(1, sizeof(char));
    return concat(string, str);
}

char* indent(char* src) {
    char* string = (char*) calloc(1, sizeof(char));
    string = concat(string, "  ");
    for (unsigned long i = 0 ; i < strlen(src) ; i++ ) {
        if ( src[i] == '\n' ) {
            string = concat(string, "\n  ");
        } else {
            char* tmp = (char*) calloc(2, sizeof(char));
            tmp[0] = src[i];
            string = concat(string, tmp);
            free(tmp);
        }
    }
    return string;
}





char* Statement_toString(Statement_node* statement) {
    return new_string(statement->value);
}

Statement_node* createStatement(char* value) {
    Statement_node* statement = (Statement_node*) calloc(1, sizeof(Statement_node));
    statement->value = value;
    statement->toString = Statement_toString;
    return statement;
}

char* FunctionDeclaration_toString(FunctionDeclaration_node* functionDeclaration) {
    char* string = new_string("function:");
    return concat(string, functionDeclaration->name);
}

FunctionDeclaration_node* createFunctionDeclaration(char* name) {
    FunctionDeclaration_node* functionDeclaration = (FunctionDeclaration_node*) calloc(1, sizeof(FunctionDeclaration_node));
    functionDeclaration->name = name;
    functionDeclaration->toString = FunctionDeclaration_toString;
    return functionDeclaration;
}

char* SourceElement_toString(SourceElement_node* sourceElement) {
    if ( strcmp(sourceElement->type, STATEMENT_SOURCE_ELEMENT_TYPE) ) {
        return sourceElement->sourceElement.statement->toString(sourceElement->sourceElement.statement);
    } else if ( strcmp(sourceElement->type, FUNCTION_DECLARATION_SOURCE_ELEMENT_TYPE) ) {
        return sourceElement->sourceElement.functionDeclaration->toString(sourceElement->sourceElement.functionDeclaration);
    } else {
        fprintf(stderr, "Error: unknown SourceElement type: %s", sourceElement->type);
        exit(1);
    }
}

SourceElement_node* createSourceElement(char* type, void* untypedSourceElement) {
    SourceElement_node* sourceElement = (SourceElement_node*) calloc(1, sizeof(SourceElement_node));
    sourceElement->type = type;
    if ( strcmp(type, STATEMENT_SOURCE_ELEMENT_TYPE) ) {
        sourceElement->sourceElement.statement = (Statement_node*) untypedSourceElement;
    } else if ( strcmp(type, FUNCTION_DECLARATION_SOURCE_ELEMENT_TYPE) ) {
        sourceElement->sourceElement.functionDeclaration = (FunctionDeclaration_node*) untypedSourceElement;
    } else {
        fprintf(stderr, "Error: unknown SourceElement type: %s", sourceElement->type);
        exit(1);
    }
    sourceElement->toString = SourceElement_toString;
    return sourceElement;
}

void SourceElements_append(SourceElements_node* sourceElements, SourceElement_node* sourceElement) {
    sourceElements->elements = (SourceElement_node**) realloc(sourceElements->elements, ( sourceElements->count + 1 ) * sizeof(SourceElement_node*));
    sourceElements->elements[sourceElements->count] = sourceElement;
    sourceElements->count += 1;
}

char* SourceElements_toString(SourceElements_node* sourceElements) {
    char* string = new_string("SourceElements");
    for ( int i = 0 ; i < sourceElements->count ; i++ ) {
        string = concat(string, "\n");
        char* tmp = sourceElements->elements[i]->toString(sourceElements->elements[i]);
        string = concat(string, indent(tmp));
        free(tmp);
    }
    return string;
}

SourceElements_node* createSourceElements(SourceElement_node* sourceElement) {
    SourceElements_node* sourceElements = (SourceElements_node*) calloc(1, sizeof(SourceElements_node));
    sourceElements->count = 0;
    sourceElements->elements = NULL;
    sourceElements->append = SourceElements_append;
    sourceElements->toString = SourceElements_toString;
    sourceElements->append(sourceElements, sourceElement);
    return sourceElements;
}

char* Program_toString(Program_node* program) {
    char* string = new_string("Program");
    if ( program->sourceElements != NULL ) {
        string = concat(string, "\n");
        char* tmp = program->sourceElements->toString(program->sourceElements);
        string = concat(string, indent(tmp));
        free(tmp);
    }
    return string;
}

Program_node* createProgram() {
    Program_node* program = (Program_node*) calloc(1, sizeof(Program_node));
    program->sourceElements = NULL;
    program->toString = Program_toString;
    return program;
}