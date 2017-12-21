#include <stdio.h>
#include <stdlib.h>
#include "node.h"

extern FILE* yyin;
extern int yyparse();
extern Program_node* root;

int main(int argc, char** argv) {
    if ( argc > 1 ) {
        yyin = fopen(argv[1], "r");
        if ( yyin == NULL ) {
            printf("file not found: %s\n", argv[1]);
            return 1;
        }
    }
    if (yyparse()) {
        fputs("An error occurred while parsing.", stderr);
        exit(1);
    }
    puts("\nparse tree:");
    puts(root->toString(root));
}