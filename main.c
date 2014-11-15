#include <stdio.h>
#include <stdlib.h>

#include "pwstack.h"

#include "lex.yy.c"

int main(int argc, char** argv)
{
    initStack();

    if (argc > 0) {
        yyin = fopen(argv[1], "r");
        yylex();
    }
    else {
        printf("No file!");
        return -1;
    }

    int m = getStackLength();
    int i;
    for (i = 0; i < m; ++i) {
        printInt();
        putchar(' ');
    } putchar('\n');

    printf("Hello world!\n");
    return 0;
}
