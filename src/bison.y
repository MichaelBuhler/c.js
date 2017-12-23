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
    int                        token_id;
    char*                      char_array;
    Program_node*              program_node;
    SourceElements_node*       sourceElements_node;
    SourceElement_node*        sourceElement_node;
    FunctionDeclaration_node*  functionDeclaration_node;
    FormalParameterList_node*  formalParameterList_node;
    Statement_node*            statement_node;
    StatementList_node*        statementList_node;
    Block_node*                block_node;
    Identifier_node*           identifier_node;
}

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

%token <char_array> IDENTIFIER

%type <sourceElements_node>       SourceElements
%type <sourceElement_node>        SourceElement
%type <functionDeclaration_node>  FunctionDeclaration
%type <formalParameterList_node>  FormalParameterList
%type <statement_node>            Statement
%type <statementList_node>        StatementList
%type <block_node>                Block
%type <identifier_node>           Identifier

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
    Block { puts("parsed Statement"); $$ = createStatement("BlockStatement"); }
    | VariableStatement { puts("parsed Statement"); $$ = createStatement("VariableStatement"); }
    | EmptyStatement { puts("parsed Statement"); $$ = createStatement("EmptyStatement"); }
//    | ExpressionStatement {puts("parsed Statement");}
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
    IDENTIFIER { puts("parsed Identifier"); $$ = createIdentifier($1); }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Parser error: %s\n", s);
}
