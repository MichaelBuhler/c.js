%{
#include <stdio.h>
#include <stdbool.h>
#include "node.h"
#include "bison.h"
#include "string_utils.h"

static char* string_literal;

%}

%option noyywrap

%x COMMENT
%x MULTILINE_COMMENT
%x SINGLE_QUOTE_STRING_LITERAL
%x ESCAPING_SINGLE_QUOTE_STRING_LITERAL
%x DOUBLE_QUOTE_STRING_LITERAL
%x ESCAPING_DOUBLE_QUOTE_STRING_LITERAL

%%

[\x09\x0b\x0c\x20] {
    /* WhiteSpace */
    puts("lexed whitespace");
}

[\x0a\x0d] {
    /* LineTerminator */
    puts("lexed line_terminator");
}

\/\/ {
    BEGIN(COMMENT);
}
<COMMENT>. {}
<COMMENT>[\x0a\x0d] {
    puts("lexed comment");
    BEGIN(INITIAL);
}

\/\* {
    BEGIN(MULTILINE_COMMENT);
}
<MULTILINE_COMMENT>. {}
<MULTILINE_COMMENT>[\x0a\x0d] {}
<MULTILINE_COMMENT>"*/" {
    puts("lexed multiline comment");
    BEGIN(INITIAL);
}

false {
    puts("lexed false");
    return FALSE_LITERAL;
}

function {
    puts("lexed function");
    return FUNCTION;
}

null {
    puts("lexed null");
    return NULL_LITERAL;
}

this {
    puts("lexed this");
    return THIS;
}

true {
    puts("lexed true");
    return TRUE_LITERAL;
}

var {
    puts("lexed var");
    return VAR;
}

\, {
    puts("lexed ,");
    return COMMA;
}

\= {
    puts("lexed =");
    return EQUALS;
}

\{ {
    puts("lexed {");
    return LEFT_BRACE;
}

\( {
    puts("lexed (");
    return LEFT_PAREN;
}

\} {
    puts("lexed }");
    return RIGHT_BRACE;
}

\) {
    puts("lexed )");
    return RIGHT_PAREN;
}

\; {
    puts("lexed ;");
    return SEMICOLON;
}

[a-zA-Z_$][a-zA-Z0-9_$]* {
    printf("lexed identifier: %s\n", yytext);
    char* tmp = (char*) calloc(strlen(yytext), sizeof(char) * strlen(yytext));
    strcpy(tmp, yytext);
    yylval.char_array = tmp;
    return IDENTIFIER;
}

0 {
    printf("lexed number: %s\n", yytext);
    yylval.double_val = 0;
    return NUMBER_LITERAL;
}

[1-9][0-9]* {
    printf("lexed number: %s\n", yytext);
    yylval.double_val = atof(yytext);
    return NUMBER_LITERAL;
}

[0-9]*\.[0-9]* {
    printf("lexed number: %s\n", yytext);
    yylval.double_val = atof(yytext);
    return NUMBER_LITERAL;
}

\' {
    string_literal = new_string("");
    BEGIN(SINGLE_QUOTE_STRING_LITERAL);
}
<SINGLE_QUOTE_STRING_LITERAL>\\ {
    BEGIN(ESCAPING_SINGLE_QUOTE_STRING_LITERAL);
}
<SINGLE_QUOTE_STRING_LITERAL>\' {
    yylval.char_array = new_string(string_literal);
    free(string_literal);
    BEGIN(INITIAL);
    return STRING_LITERAL;
}
<SINGLE_QUOTE_STRING_LITERAL>. {
    string_literal = concat(string_literal, yytext);
}
<ESCAPING_SINGLE_QUOTE_STRING_LITERAL>. {
    char c;
    switch (*yytext) {
        case 'b': c = '\b'; break; // \b backspace
        case 'f': c = '\f'; break; // \f form feed
        case 'n': c = '\n'; break; // \n line feed (new line)
        case 'r': c = '\r'; break; // \r carriage return
        case 't': c = '\t'; break; // \t horizontal tab
        default:  c = *yytext;
    }
    string_literal = concatc(string_literal, c);
    BEGIN(SINGLE_QUOTE_STRING_LITERAL);
}

\" {
    string_literal = new_string("");
    BEGIN(DOUBLE_QUOTE_STRING_LITERAL);
}
<DOUBLE_QUOTE_STRING_LITERAL>\\ {
    BEGIN(ESCAPING_DOUBLE_QUOTE_STRING_LITERAL);
}
<DOUBLE_QUOTE_STRING_LITERAL>\" {
    yylval.char_array = new_string(string_literal);
    free(string_literal);
    BEGIN(INITIAL);
    return STRING_LITERAL;
}
<DOUBLE_QUOTE_STRING_LITERAL>. {
    string_literal = concat(string_literal, yytext);
}
<ESCAPING_DOUBLE_QUOTE_STRING_LITERAL>. {
    char c;
    switch (*yytext) {
        case 'b': c = '\b'; break; // \b backspace
        case 'f': c = '\f'; break; // \f form feed
        case 'n': c = '\n'; break; // \n line feed (new line)
        case 'r': c = '\r'; break; // \r carriage return
        case 't': c = '\t'; break; // \t horizontal tab
        default:  c = *yytext;
    }
    string_literal = concatc(string_literal, c);
    BEGIN(DOUBLE_QUOTE_STRING_LITERAL);
}

