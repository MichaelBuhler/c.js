%{
#include <stdio.h>
#include <stdlib.h>
#include "bison.h"
%}

%option noyywrap

%%

[\.\(\)\{\}\;\=\,\+\-\~\!\*\/\%\<\>\&\^\|\:] {
    printf("lexed %s\n", yytext);
    return *yytext;
}

[\x09\x0b\x0c\x20] {
    /* WhiteSpace */
}

[\x0a\x0d] {
    /* LineTerminator */
}

break {
    puts("lexed break");
    return BREAK;
}

continue {
    puts("lexed continue");
    return CONTINUE;
}

delete {
    puts("lexed delete");
    return DELETE;
}

else {
    puts("lexed else");
    return ELSE;
}

false {
    puts("lexed false");
    return FALSE;
}

for {
    puts("lexed for");
    return FOR;
}

function {
    puts("lexed function");
    return FUNCTION;
}

if {
    puts("lexed if");
    return IF;
}

in {
    puts("lexed in");
    return IN;
}

new {
    puts("lexed new");
    return NEW;
}

null {
    puts("lexed null");
    return NULL_LITERAL;
}

return {
    puts("lexed return");
    return RETURN;
}

this {
    puts("lexed this");
    return THIS;
}

true {
    puts("lexed true");
    return TRUE;
}

typeof {
    puts("lexed typeof");
    return TYPEOF;
}

var {
    puts("lexed var");
    return VAR;
}

void {
    puts("lexed void");
    return VOID;
}

while {
    puts("lexed while");
    return WHILE;
}

with {
    puts("lexed with");
    return WITH;
}

[a-zA-Z0-9]+ {
    printf("lexed symbol: %s\n", yytext);
    char* str = (char*) calloc(strlen(yytext), sizeof(char));
    strcpy(str, yytext);
    yylval.string_val = str;
    return SYMBOL;
}

%%

