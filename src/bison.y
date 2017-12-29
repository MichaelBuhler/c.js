%{
#include <stdio.h>
#include <stdlib.h>
#include "node.h"

#define YYERROR_VERBOSE

int yylex();
int yyparse();
FILE* yyin;

void yyerror(const char *s);

Program_node* root = NULL;

%}

%union {
    int                           token_id;
    char*                         char_array;
    double                        double_val;
    Program_node*                 program_node;
    SourceElements_node*          sourceElements_node;
    SourceElement_node*           sourceElement_node;
    FunctionDeclaration_node*     functionDeclaration_node;
    FormalParameterList_node*     formalParameterList_node;
    Statement_node*               statement_node;
    StatementList_node*           statementList_node;
    Block_node*                   block_node;
    Identifier_node*              identifier_node;
    VariableStatement_node*       variableStatement_node;
    VariableDeclaration_node*     variableDeclaration_node;
    VariableDeclarationList_node* variableDeclarationList_node;
    Initializer_node*             initializer_node;
    EmptyStatement_node*          emptyStatement_node;
    ExpressionStatement_node*     expressionStatement_node;
    Expression_node*              expression_node;
    AssignmentExpression_node*    assignmentExpression_node;
    AssignmentOperator_enum       assignmentOperator_enum;
    Literal_node*                 literal_node;
    NullLiteral_node*             nullLiteral_node;
    BooleanLiteral_node*          booleanLiteral_node;
    NumberLiteral_node*           numberLiteral_node;
    StringLiteral_node*           stringLiteral_node;
}

%token FALSE_LITERAL
%token FUNCTION
%token NULL_LITERAL
%token THIS
%token TRUE_LITERAL
%token VAR

%token COMMA
%token EQUALS
%token LEFT_BRACE
%token LEFT_PAREN
%token RIGHT_BRACE
%token RIGHT_PAREN
%token SEMICOLON

%token <char_array> IDENTIFIER
%token <double_val> NUMBER_LITERAL
%token <char_array> STRING_LITERAL

%type <sourceElements_node>          SourceElements
%type <sourceElement_node>           SourceElement
%type <functionDeclaration_node>     FunctionDeclaration
%type <formalParameterList_node>     FormalParameterList
%type <statement_node>               Statement
%type <statementList_node>           StatementList
%type <block_node>                   Block
%type <identifier_node>              Identifier
%type <variableStatement_node>       VariableStatement
%type <variableDeclaration_node>     VariableDeclaration
%type <variableDeclarationList_node> VariableDeclarationList
%type <initializer_node>             Initializer
%type <emptyStatement_node>          EmptyStatement
%type <expressionStatement_node>     ExpressionStatement
%type <expression_node>              Expression
%type <assignmentExpression_node>    AssignmentExpression
%type <assignmentOperator_enum>      AssignmentOperator
%type <literal_node>                 Literal
%type <nullLiteral_node>             NullLiteral
%type <booleanLiteral_node>          BooleanLiteral
%type <numberLiteral_node>           NumberLiteral
%type <stringLiteral_node>           StringLiteral

%start Program

%%

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 14 Program

Program:
    /* empty program */ { puts("parsed empty Program"); root = createProgram(); }
    | SourceElements { puts("parsed Program"); root = createProgram(); root->sourceElements = $1; }
    ;

SourceElements:
    SourceElement { puts("parsed SourceElements"); $$ = createSourceElements($1); }
    | SourceElements SourceElement { puts("parsed SourceElements"); $1->append($1, $2); $$ = $1; }
    ;

SourceElement:
    Statement { puts("parsed SourceElement"); $$ = createSourceElement(STATEMENT_SOURCE_ELEMENT_TYPE, $1); }
    | FunctionDeclaration { puts("parsed SourceElement"); $$ = createSourceElement(FUNCTION_DECLARATION_SOURCE_ELEMENT_TYPE, $1); }
    ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 13 Function Definition

FunctionDeclaration:
    FUNCTION Identifier LEFT_PAREN RIGHT_PAREN Block { puts("parsed FunctionDeclaration"); $$ = createFunctionDeclaration($2, NULL, $5); }
    | FUNCTION Identifier LEFT_PAREN FormalParameterList RIGHT_PAREN Block { puts("parsed FunctionDeclaration"); $$ = createFunctionDeclaration($2, $4, $6); }
    ;

FormalParameterList:
    Identifier {puts("parsed FormalParameterList"); $$ = createFormalParameterList($1); }
    | FormalParameterList COMMA Identifier {puts("parsed FormalParameterList"); $1->append($1, $3); $$ = $1; }
    ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 12 Statements

Statement:
    Block { puts("parsed Statement"); $$ = createStatement(BLOCK_STATEMENT_TYPE, $1); }
    | VariableStatement { puts("parsed Statement"); $$ = createStatement(VARIABLE_STATEMENT_TYPE, $1); }
    | EmptyStatement { puts("parsed Statement"); $$ = createStatement(EMPTY_STATEMENT_TYPE, $1); }
    | ExpressionStatement { puts("parsed Statement"); $$ = createStatement(EXPRESSION_STATEMENT_TYPE, $1); }
//    | IfStatement {puts("parsed Statement");}
//    | IterationStatement {puts("parsed Statement");}
//    | ContinueStatement {puts("parsed Statement");}
//    | BreakStatement {puts("parsed Statement");}
//    | ReturnStatement {puts("parsed Statement");}
//    | WithStatement {puts("parsed Statement");}
    ;

Block:
    LEFT_BRACE RIGHT_BRACE { puts("parsed Block"); $$ = createBlock(); }
    | LEFT_BRACE StatementList RIGHT_BRACE { puts("parsed Block"); $$ = createBlock(); $$->statementList = $2; }
    ;

StatementList:
    Statement { puts("parsed StatementList"); $$ = createStatementList($1); }
    | StatementList Statement { puts("parsed StatementList"); $1->append($1, $2); $$ = $1; }
    ;

VariableStatement:
    VAR VariableDeclarationList SEMICOLON { puts("parsed VariableStatement"); $$ = createVariableStatement($2); }
    ;

VariableDeclarationList:
    VariableDeclaration { puts("parsed VariableDeclarationList"); $$ = createVariableDeclarationList($1); }
    | VariableDeclarationList COMMA VariableDeclaration { puts("parsed VariableDeclarationList"); $1->append($1, $3); $$ = $1; }
    ;

VariableDeclaration:
    Identifier { puts("parsed VariableDeclaration"); $$ = createVariableDeclaration($1, NULL); }
    | Identifier Initializer { puts("parsed VariableDeclaration"); $$ = createVariableDeclaration($1, $2); }
    ;

Initializer:
    EQUALS Expression { puts("parsed Initializer"); $$ = createInitializer($2); }
    ;

EmptyStatement:
    SEMICOLON { puts("parsed EmptyStatement"); $$ = createEmptyStatement(); }
    ;

ExpressionStatement:
    Expression SEMICOLON { puts("parsed ExpressionStatement"); $$ = createExpressionStatement($1); }
    ;

//IfStatement:
//    IF '(' Expression ')' Statement ELSE Statement {puts("parsed IfStatement")}
//    | IF '(' Expression ')' Statement %prec NO_ELSE {puts("parsed IfStatement")}
//    ;
//
//IterationStatement:
//    WHILE '(' Expression ')' {puts("parsed IterationStatement")}
//    | FOR '(' ';' ';' ')' Statement {puts("parsed IterationStatement")}
//    | FOR '(' ';' ';' Expression ')' Statement {puts("parsed IterationStatement")}
//    | FOR '(' ';' Expression ';' ')' Statement {puts("parsed IterationStatement")}
//    | FOR '(' ';' Expression ';' Expression ')' Statement {puts("parsed IterationStatement")}
//    | FOR '(' Expression ';' ';' ')' Statement {puts("parsed IterationStatement")}
//    | FOR '(' Expression ';' ';' Expression ')' Statement {puts("parsed IterationStatement")}
//    | FOR '(' Expression ';' Expression ';' ')' Statement {puts("parsed IterationStatement")}
//    | FOR '(' Expression ';' Expression ';' Expression ')' Statement {puts("parsed IterationStatement")}
//    | FOR '(' VAR VariableDeclarationList ';' ';' ')' Statement {puts("parsed IterationStatement")}
//    | FOR '(' VAR VariableDeclarationList ';' ';' Expression ')' Statement {puts("parsed IterationStatement")}
//    | FOR '(' VAR VariableDeclarationList ';' Expression ';' ')' Statement {puts("parsed IterationStatement")}
//    | FOR '(' VAR VariableDeclarationList ';' Expression ';' Expression ')' Statement {puts("parsed IterationStatement")}
//    | FOR '(' LeftHandSideExpression IN Expression ')' Statement {puts("parsed IterationStatement")}
//    | FOR '(' VAR Identifier IN Expression ')' Statement {puts("parsed IterationStatement")}
//    | FOR '(' VAR Identifier Initializer IN Expression ')' Statement {puts("parsed IterationStatement")}
//    ;
//
//ContinueStatement:
//    CONTINUE ';' {puts("parsed ContinueStatement")}
//    ;
//
//BreakStatement:
//    BREAK ';' {puts("parsed BreakStatement")}
//    ;
//
//ReturnStatement:
//    RETURN ';' {puts("parsed ReturnStatement")}
//    | RETURN Expression ';' {puts("parsed ReturnStatement")}
//    ;
//
//WithStatement:
//    WITH '(' Expression ')' Statement {puts("parsed WithStatement")}

///////////////////////////////////////////////////////////
// 11 Expressions

Expression:
    THIS { puts("parsed Expression"); $$ = createExpression(THIS_EXPRESSION_TYPE, NULL); }
    | Identifier { puts("parsed Expression"); $$ = createExpression(IDENTIFIER_EXPRESSION_TYPE, $1); }
    | Literal { puts("parsed Expression"); $$ = createExpression(LITERAL_EXPRESSION_TYPE, $1); }
    | LEFT_PAREN Expression RIGHT_PAREN { puts("parsed Expression"); $$ = $2; }
    | AssignmentExpression { puts("parsed Expression"); $$ = createExpression(ASSIGNMENT_EXPRESSION_TYPE, $1); }
    ;

AssignmentExpression:
// TODO Identifier needs to be LeftHandSideExpression
    Identifier AssignmentOperator Expression { puts("parsed AssignmentExpression"); $$ = createAssignmentExpression($1, $2, $3); }
    ;

AssignmentOperator:
    EQUALS { puts("parsed AssignmentOperator"); $$ = EQUALS_ASSIGNMENT_OPERATOR; }
    ;

///////////////////////////////////////////////////////////
// 7.5 Identifier

Identifier:
    IDENTIFIER { puts("parsed Identifier"); $$ = createIdentifier($1); }
    ;

///////////////////////////////////////////////////////////
// 7.7 Literals

Literal:
    NullLiteral { puts("parsed Literal"); $$ = createLiteral(NULL_LITERAL_TYPE, $1); }
    | BooleanLiteral { puts("parsed Literal"); $$ = createLiteral(BOOLEAN_LITERAL_TYPE, $1); }
    | NumberLiteral { puts("parsed Literal"); $$ = createLiteral(NUMBER_LITERAL_TYPE, $1); }
    | StringLiteral { puts("parsed Literal"); $$ = createLiteral(STRING_LITERAL_TYPE, $1); }
    ;

NullLiteral:
    NULL_LITERAL { puts("parsed NullLiteral"); $$ = createNullLiteral(); }
    ;

BooleanLiteral:
    TRUE_LITERAL { puts("parsed BooleanLiteral"); $$ = createBooleanLiteral(1); }
    | FALSE_LITERAL { puts("parsed BooleanLiteral"); $$ = createBooleanLiteral(0); }
    ;

NumberLiteral:
    NUMBER_LITERAL { puts("parsed NumberLiteral"); $$ = createNumberLiteral($1); }
    ;

StringLiteral:
    STRING_LITERAL { puts("parsed StringLiteral"); $$ = createStringLiteral($1); }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Parser error: %s\n", s);
}
