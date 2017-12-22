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

void StatementList_append(StatementList_node* statementList, Statement_node* statement) {
    statementList->statements = (Statement_node**) realloc(statementList->statements, ( statementList->count + 1 ) * sizeof(Statement_node*) );
    statementList->statements[statementList->count] = statement;
    statementList->count += 1;
}

char* StatementList_toString(StatementList_node* statementList) {
    char* string = new_string("StatementList");
    for ( int i = 0 ; i < statementList->count ; i++ ) {
        string = concat(string, "\n");
        char* tmp = statementList->statements[i]->toString(statementList->statements[i]);
        string = concat(string, indent(tmp));
        free(tmp);
    }
    return string;
}

StatementList_node* createStatementList(Statement_node* statement) {
    StatementList_node* statementList = (StatementList_node*) calloc(1, sizeof(StatementList_node));
    statementList->count = 0;
    statementList->statements = NULL;
    statementList->append = StatementList_append;
    statementList->toString = StatementList_toString;
    statementList->append(statementList, statement);
    return statementList;
}

char* Block_toString(Block_node* block) {
    char* string = new_string("Block");
    if ( block->statementList != NULL ) {
        string = concat(string, "\n");
        char* tmp = block->statementList->toString(block->statementList);
        string = concat(string, indent(tmp));
        free(tmp);
    }
    return string;
}

Block_node* createBlock() {
    Block_node* block = (Block_node*) calloc(1, sizeof(Block_node));
    block->statementList = NULL;
    block->toString = Block_toString;
    return block;
}

void FormalParameterList_append(FormalParameterList_node* formalParameterList, char* parameter) {
    formalParameterList->parameters = (char**) realloc(formalParameterList->parameters, ( formalParameterList->count + 1 ) * sizeof(char*) );
    formalParameterList->parameters[formalParameterList->count] = parameter;
    formalParameterList->count += 1;
}

char* FormalParameterList_toString(FormalParameterList_node* formalParameterList) {
    if (formalParameterList->count == 0) {
        return new_string("");
    }
    char* string = new_string(formalParameterList->parameters[0]);
    for ( int i = 1 ; i < formalParameterList->count ; i++ ) {
        string = concat(string, ", ");
        string = concat(string, formalParameterList->parameters[i]);
    }
    return string;
}

FormalParameterList_node* createFormalParameterList(char* parameter) {
    FormalParameterList_node* formalParameterList = (FormalParameterList_node*) calloc(1, sizeof(FormalParameterList_node));
    formalParameterList->count = 0;
    formalParameterList->parameters = NULL;
    formalParameterList->append = FormalParameterList_append;
    formalParameterList->toString = FormalParameterList_toString;
    formalParameterList->append(formalParameterList, parameter);
    return formalParameterList;
}

char* FunctionDeclaration_toString(FunctionDeclaration_node* functionDeclaration) {
    char* string = new_string("Function: ");
    string = concat(string, functionDeclaration->name);
    string = concat(string, " (");
    if ( functionDeclaration->formalParameterList != NULL ) {
        char* tmp = functionDeclaration->formalParameterList->toString(functionDeclaration->formalParameterList);
        string = concat(string, tmp);
        free(tmp);
    }
    string = concat(string, ")\n");
    char* tmp = functionDeclaration->block->toString(functionDeclaration->block);
    string = concat(string, indent(tmp));
    free(tmp);
    return string;
}

FunctionDeclaration_node* createFunctionDeclaration(char* name, FormalParameterList_node* formalParameterList, Block_node* block) {
    FunctionDeclaration_node* functionDeclaration = (FunctionDeclaration_node*) calloc(1, sizeof(FunctionDeclaration_node));
    functionDeclaration->name = name;
    functionDeclaration->formalParameterList = formalParameterList;
    functionDeclaration->block = block;
    functionDeclaration->toString = FunctionDeclaration_toString;
    return functionDeclaration;
}

char* SourceElement_toString(SourceElement_node* sourceElement) {
    if ( strcmp(sourceElement->type, STATEMENT_SOURCE_ELEMENT_TYPE) == 0 ) {
        return sourceElement->sourceElement.statement->toString(sourceElement->sourceElement.statement);
    } else if ( strcmp(sourceElement->type, FUNCTION_DECLARATION_SOURCE_ELEMENT_TYPE) == 0 ) {
        return sourceElement->sourceElement.functionDeclaration->toString(sourceElement->sourceElement.functionDeclaration);
    } else {
        fprintf(stderr, "Error: unknown SourceElement type: %s", sourceElement->type);
        exit(1);
    }
}

SourceElement_node* createSourceElement(char* type, void* untypedSourceElement) {
    SourceElement_node* sourceElement = (SourceElement_node*) calloc(1, sizeof(SourceElement_node));
    sourceElement->type = type;
    if ( strcmp(type, STATEMENT_SOURCE_ELEMENT_TYPE) == 0 ) {
        sourceElement->sourceElement.statement = (Statement_node*) untypedSourceElement;
    } else if ( strcmp(type, FUNCTION_DECLARATION_SOURCE_ELEMENT_TYPE) == 0 ) {
        sourceElement->sourceElement.functionDeclaration = (FunctionDeclaration_node*) untypedSourceElement;
    } else {
        fprintf(stderr, "Error: unknown SourceElement type: %s", sourceElement->type);
        exit(1);
    }
    sourceElement->toString = SourceElement_toString;
    return sourceElement;
}

void SourceElements_append(SourceElements_node* sourceElements, SourceElement_node* sourceElement) {
    sourceElements->elements = (SourceElement_node**) realloc(sourceElements->elements, ( sourceElements->count + 1 ) * sizeof(SourceElement_node*) );
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
