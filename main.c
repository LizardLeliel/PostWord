#include <stdio.h>
#include <stdlib.h>

#include "pwstack.h"

#include "lex.yy.c"

int main(int argc, char** argv)
{
    initStack();


    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        if (yylex()) return -1;
    }
    else {
        printf("No file!");
        return -1;
    }
    return 0;
}
