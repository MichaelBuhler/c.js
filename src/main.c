#include <stdio.h>

extern FILE* yyin;
extern int yyparse();

int main(int argc, char** argv) {
    if ( argc > 1 ) {
        yyin = fopen(argv[1], "r");
        if ( yyin == NULL ) {
            printf("file not found: %s\n", argv[1]);
            return 1;
        }
    }
    return yyparse();
}