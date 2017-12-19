%{
#include <stdio.h>
#include <stdlib.h>

#define YYERROR_VERBOSE

int yylex();
int yyparse();
FILE* yyin;

void yyerror(const char *s);
%}

%union {
    int   int_val;
    char* string_val;
}

%token <string_val> IDENTIFIER

%token LINE_TERMINATOR

%token FUNCTION
%token VAR

%token COMMA
%token EQUALS
%token LEFT_BRACE
%token LEFT_PAREN
%token RIGHT_BRACE
%token RIGHT_PAREN
%token SEMICOLON

%%

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 14 Program

Program:
    /* empty program */ {puts("parsed empty Program");}
    | SourceElements {puts("parsed Program");}
    ;

SourceElements:
    SourceElement {puts("parsed SourceElements");}
    | SourceElements SourceElement {puts("parsed SourceElements");}
    ;

SourceElement:
    Statement {puts("parsed SourceElement");}
    | FunctionDeclaration {puts("parsed SourceElement");}
    ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 13 Function Definition

FunctionDeclaration:
    FUNCTION Identifier LEFT_PAREN RIGHT_PAREN Block {puts("parsed FunctionDeclaration");}
//    | FUNCTION Identifier '(' FormalParameterList ')' Block {puts("parsed FunctionDeclaration");}
    ;

//FormalParameterList:
//    Identifier {puts("parsed FormalParameterList");}
//    | FormalParameterList ',' Identifier {puts("parsed FormalParameterList");}
//    ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 12 Statements

Statement:
    Block {puts("parsed Statement");}
    | VariableStatement {puts("parsed Statement");}
    | EmptyStatement {puts("parsed Statement");}
//    | ExpressionStatement {puts("parsed Statement");}
//    | IfStatement {puts("parsed Statement");}
//    | IterationStatement {puts("parsed Statement");}
//    | ContinueStatement {puts("parsed Statement");}
//    | BreakStatement {puts("parsed Statement");}
//    | ReturnStatement {puts("parsed Statement");}
//    | WithStatement {puts("parsed Statement");}
    ;

Block:
    LEFT_BRACE RIGHT_BRACE {puts("parsed Block");}
    | LEFT_BRACE StatementList RIGHT_BRACE {puts("parsed Block");}
    ;

StatementList:
    Statement {puts("parsed StatementList");}
    | StatementList Statement {puts("parsed StatementList");}
    ;

VariableStatement:
    VAR VariableDeclarationList SEMICOLON {puts("parsed VariableStatement");}
    ;

VariableDeclarationList :
    VariableDeclaration {puts("parsed VariableDeclarationList");}
    | VariableDeclarationList COMMA VariableDeclaration {puts("parsed VariableDeclarationList");}
    ;

VariableDeclaration :
    Identifier {puts("parsed VariableDeclaration");}
//    | Identifier Initializer {puts("parsed VariableDeclaration");}
    ;

//Initializer :
//   EQUALS AssignmentExpression {puts("parsed Initializer");}
//    ;

EmptyStatement:
    SEMICOLON {puts("parsed EmptyStatement");}
    ;

//ExpressionStatement:
//    Expression ';' {puts("parsed ExpressionStatement");}
//    ;
//
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
// 7.5 Identifier

Identifier:
    IDENTIFIER {puts("parsed Identifier");}
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Parser error: %s\n", s);
}
