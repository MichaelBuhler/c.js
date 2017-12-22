#ifndef NODE_H
#define NODE_H

#define STATEMENT_SOURCE_ELEMENT_TYPE "Statement"
#define FUNCTION_DECLARATION_SOURCE_ELEMENT_TYPE "FunctionDeclaration"

typedef struct Statement_node {
    char* value; // TODO
    char* (*toString)(struct Statement_node*);
} Statement_node;

Statement_node* createStatement(char*);

typedef struct StatementList_node {
    int count;
    Statement_node** statements;
    void (*append)(struct StatementList_node*, Statement_node*);
    char* (*toString)(struct StatementList_node*);
} StatementList_node;

StatementList_node* createStatementList(Statement_node*);

typedef struct Block_node {
    StatementList_node* statementList;
    char* (*toString)(struct Block_node*);
} Block_node;

Block_node* createBlock();

typedef struct FormalParameterList_node {
    int count;
    char** parameters;
    void (*append)(struct FormalParameterList_node*, char*);
    char* (*toString)(struct FormalParameterList_node*);
} FormalParameterList_node;

FormalParameterList_node* createFormalParameterList(char*);

typedef struct FunctionDeclaration_node {
    char* name;
    FormalParameterList_node* formalParameterList;
    Block_node* block;
    char* (*toString)(struct FunctionDeclaration_node*);
} FunctionDeclaration_node;

FunctionDeclaration_node* createFunctionDeclaration(char*, FormalParameterList_node*, Block_node*);

typedef union SourceElement_union {
    Statement_node* statement;
    FunctionDeclaration_node* functionDeclaration;
} SourceElement_union;

typedef struct SourceElement_node {
    char* type;
    SourceElement_union sourceElement;
    char* (*toString)(struct SourceElement_node*);
} SourceElement_node;

SourceElement_node* createSourceElement(char*, void*);

typedef struct SourceElements_node {
    int count;
    SourceElement_node** elements;
    void (*append)(struct SourceElements_node*, SourceElement_node*);
    char* (*toString)(struct SourceElements_node*);
} SourceElements_node;

SourceElements_node* createSourceElements(SourceElement_node*);

typedef struct Program_node {
    SourceElements_node* sourceElements;
    char* (*toString)(struct Program_node*);
} Program_node;

Program_node* createProgram();

#endif