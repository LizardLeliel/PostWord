#include <stdio.h>
#include <stdlib.h>

#include "pwstack.h"

#include "lex.yy.c"

int main(int argc, char** argv)
{
    initStack();


    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        yylex();
    }
    else {
        printf("No file!");
        return -1;
    }

    printf("PRINTING\n");

/*
    stackAdd();
    stackAdd();
    stackAdd();
    stackAdd();
    stackAdd();
*/

    int m = getStackLength();
    int counter;
    for (counter = 0; counter < m; ++counter) {
        if (getNextType() == pw_integer) {
            printInt(); putchar(' '); }
        else if (getNextType() == pw_floating) {
            printFloat(); putchar(' ');
        }
    }

    printf("\nHello world!\n");
    return 0;
}
