#ifndef NODE_H
#define NODE_H

#define STATEMENT_SOURCE_ELEMENT_TYPE "Statement"
#define FUNCTION_DECLARATION_SOURCE_ELEMENT_TYPE "FunctionDeclaration"

typedef enum  StatementType_enum        StatementType_enum;

typedef union  Statement_union          Statement_union;
typedef union  SourceElement_union      SourceElement_union;

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

Identifier_node*          createIdentifier(char*);
StatementList_node*       createStatementList(Statement_node*);
Block_node*               createBlock();
Statement_node*           createStatement(StatementType_enum, void*);
FormalParameterList_node* createFormalParameterList(Identifier_node*);
FunctionDeclaration_node* createFunctionDeclaration(Identifier_node*, FormalParameterList_node*, Block_node*);
SourceElement_node*       createSourceElement(char*, void*);
SourceElements_node*      createSourceElements(SourceElement_node*);
VariableStatement_node*   createVariableStatement();
Program_node*             createProgram();
EmptyStatement_node*      createEmptyStatement();

enum StatementType_enum {
    BLOCK_STATEMENT_TYPE,
    VARIABLE_STATEMENT_TYPE,
    EMPTY_STATEMENT_TYPE
};

union Statement_union {
    void* any;
    Block_node* block;
    VariableStatement_node* variableStatement;
    EmptyStatement_node* emptyStatement;
};

union SourceElement_union {
    Statement_node* statement;
    FunctionDeclaration_node* functionDeclaration;
};

struct Identifier_node {
    char* name;
};

struct StatementList_node {
    int count;
    Statement_node** statements;
    void (*append)(struct StatementList_node*, Statement_node*);
    char* (*toString)(struct StatementList_node*);
};

struct Block_node {
    StatementList_node* statementList;
    char* (*toString)(struct Block_node*);
};

struct Statement_node {
    StatementType_enum type;
    Statement_union statementUnion;
    char* (*toString)(struct Statement_node*);
};

struct FormalParameterList_node {
    int count;
    Identifier_node** parameters;
    void (*append)(struct FormalParameterList_node*, Identifier_node*);
    char* (*toString)(struct FormalParameterList_node*);
};

struct FunctionDeclaration_node {
    Identifier_node* identifier;
    FormalParameterList_node* formalParameterList;
    Block_node* block;
    char* (*toString)(struct FunctionDeclaration_node*);
};

struct SourceElement_node {
    char* type;
    SourceElement_union sourceElement;
    char* (*toString)(struct SourceElement_node*);
};

struct SourceElements_node {
    int count;
    SourceElement_node** elements;
    void (*append)(struct SourceElements_node*, SourceElement_node*);
    char* (*toString)(struct SourceElements_node*);
};

struct Program_node {
    SourceElements_node* sourceElements;
    char* (*toString)(struct Program_node*);
};

struct VariableStatement_node {
    char* (*toString)(struct VariableStatement_node*);
};

struct EmptyStatement_node {
    char* (*toString)(struct EmptyStatement_node*);
};

#endif