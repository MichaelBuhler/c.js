#include <stdio.h>
#include <stdlib.h>
#include "args.h"
#include "node.h"

extern FILE* yyin;
extern int yyparse();
extern Program_node* root;

int main(int argc, char** argv) {
    args_init(argc, argv);
    if (args_either("-h", "--help")) {
        puts("TODO"); //TODO
        exit(0);
    }
    if (args_flag("--file")) {
        yyin = fopen(args_value("--file"), "r");
        if ( yyin == NULL ) {
            printf("file not found: %s\n", args_value("--file"));
            return 1;
        }
    }
    if (yyparse()) {
        fputs("An error occurred while parsing.\n", stderr);
        exit(1);
    }
    puts("\nparse tree:");
    puts(root->toString(root));
}