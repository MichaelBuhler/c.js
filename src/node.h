#ifndef NODE_H
#define NODE_H

#define STATEMENT_SOURCE_ELEMENT_TYPE "Statement"
#define FUNCTION_DECLARATION_SOURCE_ELEMENT_TYPE "FunctionDeclaration"

typedef struct Program_node             Program_node;
typedef struct SourceElements_node      SourceElements_node;
typedef struct SourceElement_node       SourceElement_node;
typedef struct FunctionDeclaration_node FunctionDeclaration_node;
typedef struct FormalParameterList_node FormalParameterList_node;
typedef struct Statement_node           Statement_node;
typedef struct StatementList_node       StatementList_node;
typedef struct Block_node               Block_node;
typedef struct Identifier_node          Identifier_node;
typedef struct VariableStatement_node   VariableStatement_node;
typedef struct EmptyStatement_node      EmptyStatement_node;

typedef struct Identifier_node {
    char* name;
} Identifier_node;

Identifier_node* createIdentifier(char*);

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

typedef union Statement_union {
    void* any;
    Block_node* block;
    VariableStatement_node* variableStatement;
    EmptyStatement_node* emptyStatement;
} Statement_union;

typedef enum StatementType_enum {
    BLOCK_STATEMENT_TYPE,
    VARIABLE_STATEMENT_TYPE,
    EMPTY_STATEMENT_TYPE
} StatementType_enum;

typedef struct Statement_node {
    StatementType_enum type;
    Statement_union statementUnion;
    char* (*toString)(struct Statement_node*);
} Statement_node;

Statement_node* createStatement(StatementType_enum, void*);

typedef struct FormalParameterList_node {
    int count;
    Identifier_node** parameters;
    void (*append)(struct FormalParameterList_node*, Identifier_node*);
    char* (*toString)(struct FormalParameterList_node*);
} FormalParameterList_node;

FormalParameterList_node* createFormalParameterList(Identifier_node*);

typedef struct FunctionDeclaration_node {
    Identifier_node* identifier;
    FormalParameterList_node* formalParameterList;
    Block_node* block;
    char* (*toString)(struct FunctionDeclaration_node*);
} FunctionDeclaration_node;

FunctionDeclaration_node* createFunctionDeclaration(Identifier_node*, FormalParameterList_node*, Block_node*);

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

typedef struct VariableStatement_node {
    char* (*toString)(struct VariableStatement_node*);
} VariableStatement_node;

VariableStatement_node* createVariableStatement();

typedef struct EmptyStatement_node {
    char* (*toString)(struct EmptyStatement_node*);
} EmptyStatement_node;

EmptyStatement_node* createEmptyStatement();

#endif