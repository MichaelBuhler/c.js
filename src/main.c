#include <stdio.h>
#include <stdlib.h>
#include "args.h"
#include "node.h"

extern FILE* yyin;
extern int yyparse();
extern Program_node* root;

char VERBOSE_LEXER;
char VERBOSE_PARSER;

int main(int argc, char** argv) {
    args_init(argc, argv);
    if (args_flagv(2, "-h", "--help")) {
        puts("TODO"); //TODO
        exit(0);
    }
    if (args_flag("--stdin")) {
        yyin = stdin;
    } else {
        char** varargs = (char**) calloc(1, sizeof(char*));
        int num = args_varargs(varargs);
        if ( num == 0 ) {
            fprintf(stderr, "%s\n", "no input file specified");
            exit(1);
        }
        if ( num > 1 ) {
            // TODO support multiple input files?
            fprintf(stderr, "%s\n", "only one input file is supported at this time");
            exit(1);
        }
        yyin = fopen(varargs[0], "r");
        if ( yyin == NULL ) {
            printf("file not found: %s\n", varargs[0]);
            return 1;
        }
    }
    VERBOSE_LEXER  = args_flagv(4, "--debug", "--debug-lexer",  "--verbose", "--verbose-lexer");
    VERBOSE_PARSER = args_flagv(4, "--debug", "--debug-parser", "--verbose", "--verbose-parser");
    if (yyparse()) {
        fprintf(stderr, "%s\n", "an error occurred while parsing");
        exit(1);
    }
    if (args_flagv(3, "-t", "--tree", "--parse-tree")) {
        printf("%s\n", root->toString(root));
    } else {
        printf("%s\n", root->toCode(root));
    }
}