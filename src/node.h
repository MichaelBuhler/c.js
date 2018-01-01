#ifndef NODE_H
#define NODE_H

typedef enum   StatementType_enum             StatementType_enum;
typedef enum   SourceElementType_enum         SourceElementType_enum;
typedef enum   ExpressionType_enum            ExpressionType_enum;
typedef enum   MemberExpressionType_enum      MemberExpressionType_enum;
typedef enum   LeftHandSideExpressionType_enum   LeftHandSideExpressionType_enum;
typedef enum   AssignmentOperator_enum        AssignmentOperator_enum;
typedef enum   LiteralType_enum               LiteralType_enum;

typedef union  Statement_union                Statement_union;
typedef union  SourceElement_union            SourceElement_union;
typedef union  Expression_union               Expression_union;
typedef union  MemberExpression_union         MemberExpression_union;
typedef union  LeftHandSideExpression_union   LeftHandSideExpression_union;
typedef union  Literal_union                  Literal_union;

typedef struct Program_node                   Program_node;
typedef struct SourceElements_node            SourceElements_node;
typedef struct SourceElement_node             SourceElement_node;
typedef struct FunctionDeclaration_node       FunctionDeclaration_node;
typedef struct FormalParameterList_node       FormalParameterList_node;
typedef struct Statement_node                 Statement_node;
typedef struct StatementList_node             StatementList_node;
typedef struct Block_node                     Block_node;
typedef struct Identifier_node                Identifier_node;
typedef struct VariableStatement_node         VariableStatement_node;
typedef struct VariableDeclaration_node       VariableDeclaration_node;
typedef struct VariableDeclarationList_node   VariableDeclarationList_node;
typedef struct Initializer_node               Initializer_node;
typedef struct EmptyStatement_node            EmptyStatement_node;
typedef struct ExpressionStatement_node       ExpressionStatement_node;
typedef struct Expression_node                Expression_node;
typedef struct MemberExpression_node          MemberExpression_node;
typedef struct LeftHandSideExpression_node    LeftHandSideExpression_node;
typedef struct AssignmentExpression_node      AssignmentExpression_node;
typedef struct CallExpression_node            CallExpression_node;
typedef struct ArgumentList_node              ArgumentList_node;
typedef struct ReturnStatement_node           ReturnStatement_node;
typedef struct Literal_node                   Literal_node;
typedef struct NullLiteral_node               NullLiteral_node;
typedef struct BooleanLiteral_node            BooleanLiteral_node;
typedef struct NumberLiteral_node             NumberLiteral_node;
typedef struct StringLiteral_node             StringLiteral_node;

Identifier_node*              createIdentifier(char*);
StatementList_node*           createStatementList(Statement_node*);
Block_node*                   createBlock();
Statement_node*               createStatement(StatementType_enum, void*);
FormalParameterList_node*     createFormalParameterList(Identifier_node*);
FunctionDeclaration_node*     createFunctionDeclaration(Identifier_node*, FormalParameterList_node*, Block_node*);
SourceElement_node*           createSourceElement(SourceElementType_enum, void*);
SourceElements_node*          createSourceElements(SourceElement_node*);
VariableStatement_node*       createVariableStatement();
VariableDeclaration_node*     createVariableDeclaration(Identifier_node*, Initializer_node*);
VariableDeclarationList_node* createVariableDeclarationList(VariableDeclaration_node*);
Initializer_node*             createInitializer(Expression_node*);
Program_node*                 createProgram(SourceElements_node*);
EmptyStatement_node*          createEmptyStatement();
ExpressionStatement_node*     createExpressionStatement(Expression_node*);
Expression_node*              createExpression(ExpressionType_enum, void*);
MemberExpression_node*        createMemberExpression(Expression_node*, MemberExpressionType_enum, void*);
LeftHandSideExpression_node*  createLeftHandSideExpression(LeftHandSideExpressionType_enum, void*);
AssignmentExpression_node*    createAssignmentExpression(LeftHandSideExpression_node*, AssignmentOperator_enum assignmentOperator, Expression_node*);
CallExpression_node*          createCallExpression(Expression_node*, ArgumentList_node*);
ArgumentList_node*            createArgumentList(Expression_node*);
ReturnStatement_node*         createReturnStatement(Expression_node*);
Literal_node*                 createLiteral(LiteralType_enum, void*);
NullLiteral_node*             createNullLiteral();
BooleanLiteral_node*          createBooleanLiteral(char);
NumberLiteral_node*           createNumberLiteral(double);
StringLiteral_node*           createStringLiteral(char*);

enum StatementType_enum {
    BLOCK_STATEMENT_TYPE,
    VARIABLE_STATEMENT_TYPE,
    EMPTY_STATEMENT_TYPE,
    EXPRESSION_STATEMENT_TYPE,
    RETURN_STATEMENT_TYPE
};

enum SourceElementType_enum {
    STATEMENT_SOURCE_ELEMENT_TYPE,
    FUNCTION_DECLARATION_SOURCE_ELEMENT_TYPE
};

enum ExpressionType_enum {
    THIS_EXPRESSION_TYPE,
    IDENTIFIER_EXPRESSION_TYPE,
    ASSIGNMENT_EXPRESSION_TYPE,
    LITERAL_EXPRESSION_TYPE,
    MEMBER_EXPRESSION_TYPE,
    CALL_EXPRESSION_TYPE
};

enum MemberExpressionType_enum {
    DOT_MEMBER_EXPRESSION_TYPE,
    BRACKET_MEMBER_EXPRESSION_TYPE
};

enum LeftHandSideExpressionType_enum {
    IDENTIFIER_LEFT_HAND_SIDE_EXPRESSION_TYPE,
    MEMBER_EXPRESSION_LEFT_HAND_SIDE_EXPRESSION_TYPE
};

enum AssignmentOperator_enum {
    EQUALS_ASSIGNMENT_OPERATOR
};

enum LiteralType_enum {
    NULL_LITERAL_TYPE,
    BOOLEAN_LITERAL_TYPE,
    NUMBER_LITERAL_TYPE,
    STRING_LITERAL_TYPE
};

union Statement_union {
    void* any;
    Block_node* block;
    VariableStatement_node* variableStatement;
    EmptyStatement_node* emptyStatement;
    ExpressionStatement_node* expressionStatement;
    ReturnStatement_node* returnStatement;
};

union SourceElement_union {
    void* any; // TODO do we need any ?
    Statement_node* statement;
    FunctionDeclaration_node* functionDeclaration;
};

union Expression_union {
    void* any; // TODO do we need any ?
    Identifier_node* identifier;
    Literal_node* literal;
    MemberExpression_node* memberExpression;
    AssignmentExpression_node* assignmentExpression;
    CallExpression_node* callExpression;
};

union MemberExpression_union {
    void* any; // TODO do we need any ?
    Identifier_node* identifier;
    Expression_node* expression;
};

union LeftHandSideExpression_union {
    void* any;
    Identifier_node* identifier;
    MemberExpression_node* memberExpression;
};

union Literal_union {
    void* any; // TODO do we need any ?
    NullLiteral_node* nullLiteral;
    BooleanLiteral_node* booleanLiteral;
    NumberLiteral_node* numberLiteral;
    StringLiteral_node* stringLiteral;
};

struct Identifier_node {
    char* name;
    char* (*toString)(Identifier_node*);
};

struct StatementList_node {
    int count;
    Statement_node** statements;
    void (*append)(StatementList_node*, Statement_node*);
    char* (*toString)(StatementList_node*);
    char* (*toCode)(StatementList_node*);
};

struct Block_node {
    StatementList_node* statementList;
    char* (*toString)(Block_node*);
    char* (*toCode)(Block_node*, char);
};

struct Statement_node {
    StatementType_enum type;
    Statement_union statementUnion;
    char* (*toString)(Statement_node*);
    char* (*toCode)(Statement_node*);
};

struct FormalParameterList_node {
    int count;
    Identifier_node** parameters;
    void (*append)(FormalParameterList_node*, Identifier_node*);
    char* (*toString)(FormalParameterList_node*);
};

struct FunctionDeclaration_node {
    Identifier_node* identifier;
    FormalParameterList_node* formalParameterList;
    Block_node* block;
    char* (*toString)(FunctionDeclaration_node*);
    char* (*toCode)(FunctionDeclaration_node*);
};

struct SourceElement_node {
    SourceElementType_enum type;
    SourceElement_union sourceElementUnion;
    char* (*toString)(SourceElement_node*);
};

struct SourceElements_node {
    int count;
    SourceElement_node** elements;
    void (*append)(SourceElements_node*, SourceElement_node*);
    char* (*toString)(SourceElements_node*);
};

struct Program_node {
    SourceElements_node* sourceElements;
    char* (*toString)(Program_node*);
    char* (*toCode)(Program_node*);
};

struct VariableStatement_node {
    VariableDeclarationList_node* variableDeclarationList;
    char* (*toString)(VariableStatement_node*);
    char* (*toCode)(VariableStatement_node*);
};

struct VariableDeclaration_node {
    Identifier_node* identifier;
    Initializer_node* initializer;
    char* (*toString)(VariableDeclaration_node*);
    char* (*toCode)(VariableDeclaration_node*);
};

struct Initializer_node {
    Expression_node* expression;
    char* (*toString)(Initializer_node*);
};

struct VariableDeclarationList_node {
    int count;
    VariableDeclaration_node** variableDeclarations;
    void (*append)(VariableDeclarationList_node*, VariableDeclaration_node*);
    char* (*toString)(VariableDeclarationList_node*);
    char* (*toCode)(VariableDeclarationList_node*);
};

struct EmptyStatement_node {
    char* (*toString)(EmptyStatement_node*);
    char* (*toCode)(EmptyStatement_node*);
};

struct ExpressionStatement_node {
    Expression_node* expression;
    char* (*toString)(ExpressionStatement_node*);
    char* (*toCode)(ExpressionStatement_node*);
};

struct Expression_node {
    ExpressionType_enum type;
    Expression_union expressionUnion;
    char* (*toString)(Expression_node*);
};

struct MemberExpression_node {
    Expression_node* parent;
    MemberExpressionType_enum type;
    MemberExpression_union child;
    char* (*toString)(MemberExpression_node*);
};

struct LeftHandSideExpression_node {
    LeftHandSideExpressionType_enum type;
    LeftHandSideExpression_union leftHandSideExpressionUnion;
    char* (*toString)(LeftHandSideExpression_node*);
};

struct AssignmentExpression_node {
    LeftHandSideExpression_node* leftHandSideExpression;
    AssignmentOperator_enum assignmentOperator;
    Expression_node* expression;
    char* (*toString)(AssignmentExpression_node*);
};

struct CallExpression_node {
    Expression_node* function;
    ArgumentList_node* argumentList;
    char* (*toString)(CallExpression_node*);
};

struct ArgumentList_node {
    int count;
    Expression_node** arguments;
    void (*append)(ArgumentList_node*, Expression_node*);
    char* (*toString)(ArgumentList_node*);
};

struct ReturnStatement_node {
    Expression_node* expression;
    char* (*toString)(ReturnStatement_node*);
    char* (*toCode)(ReturnStatement_node*);
};

struct Literal_node {
    LiteralType_enum type;
    Literal_union literalUnion;
    char* (*toString)(Literal_node*);
};

struct NullLiteral_node {
    char* (*toString)(NullLiteral_node*);
};

struct BooleanLiteral_node {
    char boolean;
    char* (*toString)(BooleanLiteral_node*);
};

struct NumberLiteral_node {
    double number;
    char* (*toString)(NumberLiteral_node*);
};

struct StringLiteral_node {
    char* string;
    char* (*toString)(StringLiteral_node*);
};

#endif