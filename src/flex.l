%{
#include <stdio.h>
#include <stdbool.h>
#include "node.h"
#include "bison.h"
%}

%option noyywrap

%x COMMENT
%x MULTILINE_COMMENT

%%

[\x09\x0b\x0c\x20] {
    /* WhiteSpace */
    puts("lexed whitespace");
}

[\x0a\x0d] {
    /* LineTerminator */
    puts("lexed line_terminator");
}

"//" {
    BEGIN(COMMENT);
}
<COMMENT>. {}
<COMMENT>[\x0a\x0d] {
    puts("lexed comment");
    BEGIN(INITIAL);
}

"/*" {
    BEGIN(MULTILINE_COMMENT);
}
<MULTILINE_COMMENT>. {}
<MULTILINE_COMMENT>[\x0a\x0d] {}
<MULTILINE_COMMENT>"*/" {
    puts("lexed multiline comment");
    BEGIN(INITIAL);
}

function {
    puts("lexed function");
    return FUNCTION;
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
    char* str = (char*) calloc(strlen(yytext), sizeof(char));
    strcpy(str, yytext);
    yylval.char_array = str;
    return IDENTIFIER;
}
