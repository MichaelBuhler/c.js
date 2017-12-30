%{
#include <stdio.h>
#include <stdbool.h>
#include "node.h"
#include "bison.h"
#include "string_utils.h"

extern char VERBOSE_LEXER;

static char* string_literal;

static void debug(char* string) {
    if (VERBOSE_LEXER) {
        fprintf(stdout, "%s\n", string);
    }
}

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
    debug("lexed %whitespace%");
}

[\x0a\x0d] {
    /* LineTerminator */
    debug("lexed line_terminator");
}

\/\/ {
    BEGIN(COMMENT);
}
<COMMENT>. {}
<COMMENT>[\x0a\x0d] {
    debug("lexed comment");
    BEGIN(INITIAL);
}

\/\* {
    BEGIN(MULTILINE_COMMENT);
}
<MULTILINE_COMMENT>. {}
<MULTILINE_COMMENT>[\x0a\x0d] {}
<MULTILINE_COMMENT>"*/" {
    debug("lexed multiline comment");
    BEGIN(INITIAL);
}

false {
    debug("lexed false");
    return FALSE_LITERAL;
}

function {
    debug("lexed function");
    return FUNCTION;
}

null {
    debug("lexed null");
    return NULL_LITERAL;
}

this {
    debug("lexed this");
    return THIS;
}

true {
    debug("lexed true");
    return TRUE_LITERAL;
}

var {
    debug("lexed var");
    return VAR;
}

\, {
    debug("lexed ,");
    return COMMA;
}

\= {
    debug("lexed =");
    return EQUALS;
}

\{ {
    debug("lexed {");
    return LEFT_BRACE;
}

\( {
    debug("lexed (");
    return LEFT_PAREN;
}

\} {
    debug("lexed }");
    return RIGHT_BRACE;
}

\) {
    debug("lexed )");
    return RIGHT_PAREN;
}

\; {
    debug("lexed ;");
    return SEMICOLON;
}

[a-zA-Z_$][a-zA-Z0-9_$]* {
    char* tmp = (char*) calloc(strlen(yytext) + 20, sizeof(char));
    sprintf(tmp, "lexed identifier: %s", yytext);
    debug(tmp);
    free(tmp);
    yylval.char_array = new_string(yytext);
    return IDENTIFIER;
}

0 {
    debug("lexed number: 0\n");
    yylval.double_val = 0;
    return NUMBER_LITERAL;
}

[1-9][0-9]* {
    char* tmp = (char*) calloc(strlen(yytext) + 15, sizeof(char));
    sprintf(tmp, "lexed number: %s", yytext);
    debug(tmp);
    free(tmp);
    yylval.double_val = atof(yytext);
    return NUMBER_LITERAL;
}

[0-9]*\.[0-9]* {
    char* tmp = (char*) calloc(strlen(yytext) + 15, sizeof(char));
    sprintf(tmp, "lexed number: %s", yytext);
    debug(tmp);
    free(tmp);
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
    debug("lexed string");
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
    debug("lexed string");
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

. {
    fprintf(stderr, "Lexer error: unrecognized character: %s\n", yytext);
    return LEXER_ERROR;
}
