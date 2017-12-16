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

%token <string_val> SYMBOL
%token BREAK
%token CONTINUE
%token DELETE
%token ELSE
%token FALSE
%token FOR
%token FUNCTION
%token IF
%token IN
%token NEW
%token NULL_LITERAL
%token RETURN
%token THIS
%token TRUE
%token TYPEOF
%token VAR
%token VOID
%token WHILE
%token WITH

%nonassoc NO_ELSE
%nonassoc ELSE

%%

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 14 Program

Program:
    SourceElements {puts("parsed Program");}
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
    FUNCTION Identifier '(' ')' Block {puts("parsed FunctionDeclaration");}
    | FUNCTION Identifier '(' FormalParameterList ')' Block {puts("parsed FunctionDeclaration");}
    ;

FormalParameterList:
    Identifier {puts("parsed FormalParameterList");}
    | FormalParameterList ',' Identifier {puts("parsed FormalParameterList");}
    ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 12 Statements

Statement:
    Block {puts("parsed Statement");}
    | VariableStatement {puts("parsed Statement");}
    | EmptyStatement {puts("parsed Statement");}
    | ExpressionStatement {puts("parsed Statement");}
    | IfStatement {puts("parsed Statement");}
    | IterationStatement {puts("parsed Statement");}
    | ContinueStatement {puts("parsed Statement");}
    | BreakStatement {puts("parsed Statement");}
    | ReturnStatement {puts("parsed Statement");}
    | WithStatement {puts("parsed Statement");}
    ;

Block:
    '{' '}' {puts("parsed Block");}
    | '{' StatementList '}' {puts("parsed Block");}
    ;

StatementList:
    Statement {puts("parsed StatementList");}
    | StatementList Statement {puts("parsed StatementList");}
    ;

VariableStatement:
    VAR VariableDeclarationList ';' {puts("parsed VariableStatement");}
    ;

VariableDeclarationList :
    VariableDeclaration {puts("parsed VariableDeclarationList");}
    | VariableDeclarationList ',' VariableDeclaration {puts("parsed VariableDeclarationList");}
    ;

VariableDeclaration :
    Identifier {puts("parsed VariableDeclaration");}
    | Identifier Initializer {puts("parsed VariableDeclaration");}
    ;

Initializer :
    '=' AssignmentExpression {puts("parsed Initializer");}
    ;

EmptyStatement:
    ';' {puts("parsed EmptyStatement");}
    ;

ExpressionStatement:
    Expression ';' {puts("parsed ExpressionStatement");}
    ;

IfStatement:
    IF '(' Expression ')' Statement ELSE Statement {puts("parsed IfStatement")}
    | IF '(' Expression ')' Statement %prec NO_ELSE {puts("parsed IfStatement")}
    ;

IterationStatement:
    WHILE '(' Expression ')' {puts("parsed IterationStatement")}
    | FOR '(' ';' ';' ')' Statement {puts("parsed IterationStatement")}
    | FOR '(' ';' ';' Expression ')' Statement {puts("parsed IterationStatement")}
    | FOR '(' ';' Expression ';' ')' Statement {puts("parsed IterationStatement")}
    | FOR '(' ';' Expression ';' Expression ')' Statement {puts("parsed IterationStatement")}
    | FOR '(' Expression ';' ';' ')' Statement {puts("parsed IterationStatement")}
    | FOR '(' Expression ';' ';' Expression ')' Statement {puts("parsed IterationStatement")}
    | FOR '(' Expression ';' Expression ';' ')' Statement {puts("parsed IterationStatement")}
    | FOR '(' Expression ';' Expression ';' Expression ')' Statement {puts("parsed IterationStatement")}
    | FOR '(' VAR VariableDeclarationList ';' ';' ')' Statement {puts("parsed IterationStatement")}
    | FOR '(' VAR VariableDeclarationList ';' ';' Expression ')' Statement {puts("parsed IterationStatement")}
    | FOR '(' VAR VariableDeclarationList ';' Expression ';' ')' Statement {puts("parsed IterationStatement")}
    | FOR '(' VAR VariableDeclarationList ';' Expression ';' Expression ')' Statement {puts("parsed IterationStatement")}
    | FOR '(' LeftHandSideExpression IN Expression ')' Statement {puts("parsed IterationStatement")}
    | FOR '(' VAR Identifier IN Expression ')' Statement {puts("parsed IterationStatement")}
    | FOR '(' VAR Identifier Initializer IN Expression ')' Statement {puts("parsed IterationStatement")}
    ;

ContinueStatement:
    CONTINUE ';' {puts("parsed ContinueStatement")}
    ;

BreakStatement:
    BREAK ';' {puts("parsed BreakStatement")}
    ;

ReturnStatement:
    RETURN ';' {puts("parsed ReturnStatement")}
    | RETURN Expression ';' {puts("parsed ReturnStatement")}
    ;

WithStatement:
    WITH '(' Expression ')' Statement {puts("parsed WithStatement")}
    ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 11 Expressions

PrimaryExpression:
    THIS {puts("parsed PrimaryExpression");}
    | Identifier {puts("parsed PrimaryExpression");}
    | Literal {puts("parsed PrimaryExpression");}
    | '(' Expression ')' {puts("parsed PrimaryExpression");}
    ;

MemberExpression:
    PrimaryExpression {puts("parsed MemberExpression");}
    | MemberExpression '[' Expression ']' {puts("parsed MemberExpression");}
    | MemberExpression '.' Identifier {puts("parsed MemberExpression");}
    | NEW MemberExpression Arguments {puts("parsed MemberExpression");}
    ;

NewExpression:
    MemberExpression {puts("parsed NewExpression");}
    | NEW NewExpression {puts("parsed NewExpression");}
    ;

CallExpression:
    MemberExpression Arguments {puts("parsed CallExpression");}
    | CallExpression Arguments {puts("parsed CallExpression");}
    | CallExpression '[' Expression ']' {puts("parsed CallExpression");}
    | CallExpression '.' Identifier {puts("parsed CallExpression");}
    ;

Arguments:
    '(' ')' {puts("parsed Arguments");}
    '(' ArgumentList ')' {puts("parsed Arguments");}
    ;

ArgumentList:
    AssignmentExpression {puts("parsed ArgumentList");}
    | ArgumentList ',' AssignmentExpression  {puts("parsed ArgumentList");}
    ;

LeftHandSideExpression:
    NewExpression {puts("parsed LeftHandSideExpression");}
    | CallExpression {puts("parsed LeftHandSideExpression");}
    ;

PostfixExpression:
    LeftHandSideExpression {puts("parsed PostfixExpression");}
    | LeftHandSideExpression '+' '+' {puts("parsed PostfixExpression");}
    | LeftHandSideExpression '-' '-' {puts("parsed PostfixExpression");}
    ;

UnaryExpression:
    PostfixExpression {puts("parsed UnaryExpression");}
    | DELETE UnaryExpression {puts("parsed UnaryExpression");}
    | VOID UnaryExpression {puts("parsed UnaryExpression");}
    | TYPEOF UnaryExpression {puts("parsed UnaryExpression");}
    | '+' '+' UnaryExpression {puts("parsed UnaryExpression");}
    | '-' '-' UnaryExpression {puts("parsed UnaryExpression");}
    | '+' UnaryExpression {puts("parsed UnaryExpression");}
    | '-' UnaryExpression {puts("parsed UnaryExpression");}
    | '~' UnaryExpression {puts("parsed UnaryExpression");}
    | '!' UnaryExpression {puts("parsed UnaryExpression");}
    ;

MultiplicativeExpression:
    UnaryExpression {puts("parsed MultiplicativeExpression");}
    | MultiplicativeExpression '*' UnaryExpression {puts("parsed MultiplicativeExpression");}
    | MultiplicativeExpression '/' UnaryExpression {puts("parsed MultiplicativeExpression");}
    | MultiplicativeExpression '%' UnaryExpression {puts("parsed MultiplicativeExpression");}
    ;

AdditiveExpression:
    MultiplicativeExpression {puts("parsed AdditiveExpression");}
    | AdditiveExpression '+' MultiplicativeExpression {puts("parsed AdditiveExpression");}
    | AdditiveExpression '-' MultiplicativeExpression {puts("parsed AdditiveExpression");}
    ;

ShiftExpression:
    AdditiveExpression {puts("parsed ShiftExpression");}
    | ShiftExpression '<' '<' AdditiveExpression {puts("parsed ShiftExpression");}
    | ShiftExpression '>' '>' AdditiveExpression {puts("parsed ShiftExpression");}
    | ShiftExpression '>' '>' '>' AdditiveExpression {puts("parsed ShiftExpression");}
    ;

RelationalExpression:
    ShiftExpression {puts("parsed RelationalExpression");}
    | RelationalExpression '<' ShiftExpression {puts("parsed RelationalExpression");}
    | RelationalExpression '>' ShiftExpression {puts("parsed RelationalExpression");}
    | RelationalExpression '<' '=' ShiftExpression {puts("parsed RelationalExpression");}
    | RelationalExpression '>' '=' ShiftExpression {puts("parsed RelationalExpression");}
    ;

EqualityExpression:
    RelationalExpression {puts("parsed EqualityExpression");}
    | EqualityExpression '=' '=' RelationalExpression {puts("parsed EqualityExpression");}
    | EqualityExpression '!' '=' RelationalExpression {puts("parsed EqualityExpression");}
    ;

BitwiseANDExpression:
    EqualityExpression {puts("parsed BitwiseANDExpression");}
    | BitwiseANDExpression '&' EqualityExpression {puts("parsed BitwiseANDExpression");}
    ;

BitwiseXORExpression:
    BitwiseANDExpression {puts("parsed BitwiseXORExpression");}
    | BitwiseXORExpression '^' BitwiseANDExpression {puts("parsed BitwiseXORExpression");}
    ;

BitwiseORExpression:
    BitwiseXORExpression {puts("parsed BitwiseORExpression");}
    | BitwiseORExpression '|' BitwiseXORExpression {puts("parsed BitwiseORExpression");}
    ;

LogicalANDExpression:
    BitwiseORExpression {puts("parsed LogicalANDExpression");}
    | LogicalANDExpression '&' '&' BitwiseORExpression {puts("parsed LogicalANDExpression");}
    ;

LogicalORExpression:
    LogicalANDExpression {puts("parsed LogicalORExpression");}
    | LogicalORExpression '|' '|' LogicalANDExpression {puts("parsed LogicalORExpression");}
    ;

ConditionalExpression :
    LogicalORExpression {puts("parsed ConditionalExpression");}
    | LogicalORExpression '?' AssignmentExpression ':' AssignmentExpression {puts("parsed ConditionalExpression");}
    ;

AssignmentExpression:
    ConditionalExpression {puts("parsed AssignmentExpression");}
    | LeftHandSideExpression AssignmentOperator AssignmentExpression {puts("parsed AssignmentExpression");}
    ;

AssignmentOperator:
    '=' {puts("parsed AssignmentOperator");}
    | '*' '=' {puts("parsed AssignmentOperator");}
    | '/' '=' {puts("parsed AssignmentOperator");}
    | '%' '=' {puts("parsed AssignmentOperator");}
    | '+' '=' {puts("parsed AssignmentOperator");}
    | '-' '=' {puts("parsed AssignmentOperator");}
    | '<' '<' '=' {puts("parsed AssignmentOperator");}
    | '>' '>' '=' {puts("parsed AssignmentOperator");}
    | '>' '>' '>' '='  {puts("parsed AssignmentOperator");}
    | '&' '=' {puts("parsed AssignmentOperator");}
    | '^' '=' {puts("parsed AssignmentOperator");}
    | '|' '=' {puts("parsed AssignmentOperator");}
    ;

Expression:
    AssignmentExpression {puts("parsed Expression");}
    | Expression ',' AssignmentExpression {puts("parsed Expression");}
    ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 7 Literals

Literal:
    NullLiteral {puts("parsed Literal");}
    | BooleanLiteral {puts("parsed Literal");}
//    | NumericLiteral {puts("parsed Literal");}
//    | StringLiteral {puts("parsed Literal");}
    ;

NullLiteral:
    NULL_LITERAL {puts("parsed NullLiteral");}
    ;

BooleanLiteral:
    TRUE {puts("parsed BooleanLiteral");}
    | FALSE {puts("parsed BooleanLiteral");}
    ;

// INCOMPLETE




///////////////////////////////////////////////////////////
// TEMPORARY PLACEHOLDERS


Identifier:
    SYMBOL {puts("parsed placeholder Identifier");}
    ;

%%

int main(int argc, char** argv) {
    if ( argc > 1 ) {
        yyin = fopen(argv[1], "r");
        if ( yyin == NULL ) {
            printf("file not found: %s\n", argv[1]);
            exit(1);
       }
    }
    return yyparse();
}

void yyerror(const char *s) {
    fprintf(stderr, "Parser error: %s\n", s);
}
