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
            fputs("no input file specified\n", stderr);
            exit(1);
        }
        if ( num > 1 ) {
            // TODO support multiple input files?
            fputs("only one input file is supported at this time\n", stderr);
            exit(1);
        }
        yyin = fopen(varargs[0], "r");
        if ( yyin == NULL ) {
            printf("file not found: %s\n", varargs[0]);
            return 1;
        }
    }
    VERBOSE_LEXER  = args_flagv(2, "--verbose", "--verbose-lexer");
    VERBOSE_PARSER = args_flagv(2, "--verbose", "--verbose-parser");
    if (yyparse()) {
        fputs("An error occurred while parsing.\n", stderr);
        exit(1);
    }
    if (args_flag("--tree")) {
        puts(root->toString(root));
    }
}