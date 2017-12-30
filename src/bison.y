%{
#include <stdio.h>
#include <stdlib.h>
#include "node.h"

#define YYERROR_VERBOSE

extern char VERBOSE_PARSER;

int yylex();

Program_node* root = NULL;

static void debug(char* string) {
    if (VERBOSE_PARSER) {
        fprintf(stdout, "%s\n", string);
    }
}

static void yyerror(char *s) {
    fprintf(stderr, "Parser error: %s\n", s);
}

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
    CallExpression_node*          callExpression_node;
    ArgumentList_node*            argumentList_node;
    Literal_node*                 literal_node;
    NullLiteral_node*             nullLiteral_node;
    BooleanLiteral_node*          booleanLiteral_node;
    NumberLiteral_node*           numberLiteral_node;
    StringLiteral_node*           stringLiteral_node;
}

%token LEXER_ERROR

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
%type <callExpression_node>          CallExpression
%type <argumentList_node>            ArgumentList
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
    /* empty program */ { debug("parsed empty Program"); root = createProgram(NULL); }
    | SourceElements { debug("parsed Program"); root = createProgram($1); }
    ;

SourceElements:
    SourceElement { debug("parsed SourceElements"); $$ = createSourceElements($1); }
    | SourceElements SourceElement { debug("parsed SourceElements"); $1->append($1, $2); $$ = $1; }
    ;

SourceElement:
    Statement { debug("parsed SourceElement"); $$ = createSourceElement(STATEMENT_SOURCE_ELEMENT_TYPE, $1); }
    | FunctionDeclaration { debug("parsed SourceElement"); $$ = createSourceElement(FUNCTION_DECLARATION_SOURCE_ELEMENT_TYPE, $1); }
    ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 13 Function Definition

FunctionDeclaration:
    FUNCTION Identifier LEFT_PAREN RIGHT_PAREN Block { debug("parsed FunctionDeclaration"); $$ = createFunctionDeclaration($2, NULL, $5); }
    | FUNCTION Identifier LEFT_PAREN FormalParameterList RIGHT_PAREN Block { debug("parsed FunctionDeclaration"); $$ = createFunctionDeclaration($2, $4, $6); }
    ;

FormalParameterList:
    Identifier {debug("parsed FormalParameterList"); $$ = createFormalParameterList($1); }
    | FormalParameterList COMMA Identifier {debug("parsed FormalParameterList"); $1->append($1, $3); $$ = $1; }
    ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 12 Statements

Statement:
    Block { debug("parsed Statement"); $$ = createStatement(BLOCK_STATEMENT_TYPE, $1); }
    | VariableStatement { debug("parsed Statement"); $$ = createStatement(VARIABLE_STATEMENT_TYPE, $1); }
    | EmptyStatement { debug("parsed Statement"); $$ = createStatement(EMPTY_STATEMENT_TYPE, $1); }
    | ExpressionStatement { debug("parsed Statement"); $$ = createStatement(EXPRESSION_STATEMENT_TYPE, $1); }
//    | IfStatement {debug("parsed Statement");}
//    | IterationStatement {debug("parsed Statement");}
//    | ContinueStatement {debug("parsed Statement");}
//    | BreakStatement {debug("parsed Statement");}
//    | ReturnStatement {debug("parsed Statement");}
//    | WithStatement {debug("parsed Statement");}
    ;

Block:
    LEFT_BRACE RIGHT_BRACE { debug("parsed Block"); $$ = createBlock(); }
    | LEFT_BRACE StatementList RIGHT_BRACE { debug("parsed Block"); $$ = createBlock(); $$->statementList = $2; }
    ;

StatementList:
    Statement { debug("parsed StatementList"); $$ = createStatementList($1); }
    | StatementList Statement { debug("parsed StatementList"); $1->append($1, $2); $$ = $1; }
    ;

VariableStatement:
    VAR VariableDeclarationList SEMICOLON { debug("parsed VariableStatement"); $$ = createVariableStatement($2); }
    ;

VariableDeclarationList:
    VariableDeclaration { debug("parsed VariableDeclarationList"); $$ = createVariableDeclarationList($1); }
    | VariableDeclarationList COMMA VariableDeclaration { debug("parsed VariableDeclarationList"); $1->append($1, $3); $$ = $1; }
    ;

VariableDeclaration:
    Identifier { debug("parsed VariableDeclaration"); $$ = createVariableDeclaration($1, NULL); }
    | Identifier Initializer { debug("parsed VariableDeclaration"); $$ = createVariableDeclaration($1, $2); }
    ;

Initializer:
    EQUALS Expression { debug("parsed Initializer"); $$ = createInitializer($2); }
    ;

EmptyStatement:
    SEMICOLON { debug("parsed EmptyStatement"); $$ = createEmptyStatement(); }
    ;

ExpressionStatement:
    Expression SEMICOLON { debug("parsed ExpressionStatement"); $$ = createExpressionStatement($1); }
    ;

//IfStatement:
//    IF '(' Expression ')' Statement ELSE Statement {debug("parsed IfStatement")}
//    | IF '(' Expression ')' Statement %prec NO_ELSE {debug("parsed IfStatement")}
//    ;
//
//IterationStatement:
//    WHILE '(' Expression ')' {debug("parsed IterationStatement")}
//    | FOR '(' ';' ';' ')' Statement {debug("parsed IterationStatement")}
//    | FOR '(' ';' ';' Expression ')' Statement {debug("parsed IterationStatement")}
//    | FOR '(' ';' Expression ';' ')' Statement {debug("parsed IterationStatement")}
//    | FOR '(' ';' Expression ';' Expression ')' Statement {debug("parsed IterationStatement")}
//    | FOR '(' Expression ';' ';' ')' Statement {debug("parsed IterationStatement")}
//    | FOR '(' Expression ';' ';' Expression ')' Statement {debug("parsed IterationStatement")}
//    | FOR '(' Expression ';' Expression ';' ')' Statement {debug("parsed IterationStatement")}
//    | FOR '(' Expression ';' Expression ';' Expression ')' Statement {debug("parsed IterationStatement")}
//    | FOR '(' VAR VariableDeclarationList ';' ';' ')' Statement {debug("parsed IterationStatement")}
//    | FOR '(' VAR VariableDeclarationList ';' ';' Expression ')' Statement {debug("parsed IterationStatement")}
//    | FOR '(' VAR VariableDeclarationList ';' Expression ';' ')' Statement {debug("parsed IterationStatement")}
//    | FOR '(' VAR VariableDeclarationList ';' Expression ';' Expression ')' Statement {debug("parsed IterationStatement")}
//    | FOR '(' LeftHandSideExpression IN Expression ')' Statement {debug("parsed IterationStatement")}
//    | FOR '(' VAR Identifier IN Expression ')' Statement {debug("parsed IterationStatement")}
//    | FOR '(' VAR Identifier Initializer IN Expression ')' Statement {debug("parsed IterationStatement")}
//    ;
//
//ContinueStatement:
//    CONTINUE ';' {debug("parsed ContinueStatement")}
//    ;
//
//BreakStatement:
//    BREAK ';' {debug("parsed BreakStatement")}
//    ;
//
//ReturnStatement:
//    RETURN ';' {debug("parsed ReturnStatement")}
//    | RETURN Expression ';' {debug("parsed ReturnStatement")}
//    ;
//
//WithStatement:
//    WITH '(' Expression ')' Statement {debug("parsed WithStatement")}

///////////////////////////////////////////////////////////
// 11 Expressions

Expression:
    THIS { debug("parsed Expression"); $$ = createExpression(THIS_EXPRESSION_TYPE, NULL); }
    | Identifier { debug("parsed Expression"); $$ = createExpression(IDENTIFIER_EXPRESSION_TYPE, $1); }
    | Literal { debug("parsed Expression"); $$ = createExpression(LITERAL_EXPRESSION_TYPE, $1); }
    | LEFT_PAREN Expression RIGHT_PAREN { debug("parsed Expression"); $$ = $2; }
    | AssignmentExpression { debug("parsed Expression"); $$ = createExpression(ASSIGNMENT_EXPRESSION_TYPE, $1); }
    | CallExpression { debug("parsed Expression"); $$ = createExpression(CALL_EXPRESSION_TYPE, $1); }
    ;

CallExpression:
    Expression LEFT_PAREN RIGHT_PAREN { debug("parsed CallExpression"); $$ = createCallExpression($1, NULL); }
    | Expression LEFT_PAREN ArgumentList RIGHT_PAREN { debug("parsed CallExpression"); $$ = createCallExpression($1, $3); }
    ;

ArgumentList:
    Expression { debug("parsed ArgumentList"); $$ = createArgumentList($1); }
    | ArgumentList COMMA Expression { debug("parsed ArgumentList"); $1->append($1, $3); $$ = $1; }
    ;

AssignmentExpression:
// TODO Identifier needs to be LeftHandSideExpression
    Identifier AssignmentOperator Expression { debug("parsed AssignmentExpression"); $$ = createAssignmentExpression($1, $2, $3); }
    ;

AssignmentOperator:
    EQUALS { debug("parsed AssignmentOperator"); $$ = EQUALS_ASSIGNMENT_OPERATOR; }
    ;

///////////////////////////////////////////////////////////
// 7.5 Identifier

Identifier:
    IDENTIFIER { debug("parsed Identifier"); $$ = createIdentifier($1); }
    ;

///////////////////////////////////////////////////////////
// 7.7 Literals

Literal:
    NullLiteral { debug("parsed Literal"); $$ = createLiteral(NULL_LITERAL_TYPE, $1); }
    | BooleanLiteral { debug("parsed Literal"); $$ = createLiteral(BOOLEAN_LITERAL_TYPE, $1); }
    | NumberLiteral { debug("parsed Literal"); $$ = createLiteral(NUMBER_LITERAL_TYPE, $1); }
    | StringLiteral { debug("parsed Literal"); $$ = createLiteral(STRING_LITERAL_TYPE, $1); }
    ;

NullLiteral:
    NULL_LITERAL { debug("parsed NullLiteral"); $$ = createNullLiteral(); }
    ;

BooleanLiteral:
    TRUE_LITERAL { debug("parsed BooleanLiteral"); $$ = createBooleanLiteral(1); }
    | FALSE_LITERAL { debug("parsed BooleanLiteral"); $$ = createBooleanLiteral(0); }
    ;

NumberLiteral:
    NUMBER_LITERAL { debug("parsed NumberLiteral"); $$ = createNumberLiteral($1); }
    ;

StringLiteral:
    STRING_LITERAL { debug("parsed StringLiteral"); $$ = createStringLiteral($1); }
    ;
