#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Data values */
typedef enum PW_TYPES {
    nil = 0,
    pw_integer  = 1,
    pw_floating = 2,
    pw_boolean  = 4,
} pwTypes;

/* Data emplaced on stack */
typedef struct PW_STACK_NODE {
    void*     data;
    pwTypes   type;

    struct PW_STACK_NODE* next;
} stackNode;

/* contains pointers to tail and head */
typedef struct PW_STACK_HEAD {
    stackNode* head;
    stackNode* tail; /* Points to second last */

    size_t length;
} stackHead;

/* data size - for dup */
int memsize[pw_boolean+1];

/* The stack postward uses */
stackHead* STACK;

/* ======= Mangament functions (that the word?) ======= */
void initStack() {
    STACK       = (stackHead*)malloc(sizeof(stackHead));
    STACK->head = (stackNode*)malloc(sizeof(stackNode));

    STACK->tail       = (stackNode*)malloc(sizeof(stackNode));
    STACK->tail->next = (stackNode*)malloc(sizeof(stackNode));
    STACK->length     = 0;

    memsize[pw_integer]  = sizeof(int);
    memsize[pw_floating] = sizeof(double);
    memsize[pw_boolean]  = sizeof(int);

}

/* Sets STACK->tail to point to head */
int setTail() {
    printf("Setting Tail\n");
    STACK->tail = STACK->head;
    return 0;
}

/* ======= Basic stack operations ====== */
int pop() {
    if (STACK->length == 0) {
        printf("Stack Underflow - popping\n");
        return -1;
    }

    stackNode* temp = STACK->head;

    if (temp)
    STACK->head = temp->next;

    free(temp->data);
    free(temp);

    --STACK->length;
    return 0;
}

int stackDup() {
    if (STACK->length == 0) {printf("Emptey stack"); return -1;}

    stackNode* newNode = (stackNode*)malloc(sizeof(stackNode));
    if (!newNode) {printf("Bad_alloc\n"); return -1; }

    newNode->type = STACK->head->type;
    newNode->data = malloc(memsize[newNode->type]);

    memcpy(newNode->data, STACK->head->data, memsize[newNode->type]);

    newNode->next = STACK->head;
    STACK  ->head = newNode;

/*
    if (STACK->length == 1) STACK->tail = STACK->head;
*/
    ++STACK->length;

    return 0;
}

/* ====== Push functions ======= */
int pushInt(int n) {
    stackNode* newNode = (stackNode*)malloc(sizeof(stackNode));

    if (!newNode) {printf("Bad_alloc\n"); return -1;}

    newNode->data = malloc(sizeof(int));
    *(int*)newNode->data = n;
    newNode->type = pw_integer;

    newNode->next = STACK->head;
    STACK->head   = newNode;

    if (STACK->length == 1) STACK->tail = newNode;

    ++STACK->length;

    return 0;
}

int pushFloat(double n) {
    stackNode* newNode = (stackNode*)malloc(sizeof(stackNode));

    if (!newNode) {printf("Bad_alloc\n"); return -1;}

    newNode->data = malloc(sizeof(double));
    *(double*)newNode->data = n;
    newNode->type = pw_floating;

    newNode->next  = STACK->head;
    STACK  ->head   = newNode;


    if (STACK->length == 1) STACK->tail = newNode;

    ++STACK->length;

    return 0;
}

int pushTrue() {
    stackNode* newNode = (stackNode*)malloc(sizeof(stackNode));

    if (!newNode) {printf("Bad_alloc\n"); return -1; }

    newNode->data = malloc(sizeof(int));
    *(int*)newNode->data = 1;
    newNode->type = pw_boolean;

    newNode->next = STACK->head;
    STACK->head   = newNode;

    if (STACK->length == 1) STACK->tail = newNode;

    ++STACK->length;

    return 0;
}

int pushFalse() {
    stackNode* newNode = (stackNode*)malloc(sizeof(stackNode));

    if (!newNode) {printf("Bad_alloc\n"); return -1; }

    newNode->data = malloc(sizeof(int));
    *(int*)newNode->data = 0;
    newNode->type =  pw_boolean;

    newNode->next = STACK->head;
    STACK->head   = newNode;

    if (STACK->length == 1) STACK->tail = newNode;

    ++STACK->length;
    return 0;
}

/* ======= Print functions ====== */
/* I gook a quick couple minute nap, then suddenly deja vu! */
int printInt() {
    if (STACK->length == 0) {
        printf("Stack Underflow -- int print\n");
        return -1;
    }

    printf("%d", *(int*)STACK->head->data);

    if (pop()) {
        printf("D: in printInt()\n"); return -1;
    }

    return 0;
}

int printFloat() {
    if (STACK->length == 0) {
        printf("Stack Underflow -- double print\n");
        return -1;
    }

    printf("%f", *(double*)STACK->head->data);

    if (pop()) {
        printf("D: in PrintFloat()\n");
        return -1;
    }

    return 0;
}

int printBool() {
    if (STACK->length == 0) {
        printf("Stack underflow -- bool print\n");
        return -1;
    }

    printf("%s", *(int*)STACK->head->data ? "true" : "false");
    return 0;
}

int printTop() {
    if (!STACK->length ) {
        printf("Stack underflow -- nothing to print");
        return -1;
    }
    switch (STACK->head->type) {
      case (pw_integer):
        printInt(); break;
      case (pw_floating):
        printFloat(); break;
      case (pw_boolean):
        printBool(); break;
      default:
        break;
    }

    return 0;
}

int printsTop() {
    if (printTop()) return -1;
    putchar(' '); return 0;
}

int putsTop() {
    if (printTop()) return -1;
    putchar('\n'); return 0;
}

/* ====== Return pops ====== */
int popInt() {
    int a = *(int*)STACK->head->data;
    pop();
    return a;
}

double popFloat() {
    double b = STACK->head->type & pw_floating
             ? *(double*)STACK->head->data
             : (double)*(int*)STACK->head->data;
    pop(); return b;
}

/* ====== ARTHMETIC ====== */
int stackAdd() {
    if (STACK->length < 2) { printf("Stack Underflow - add\n"); return -1; }
    if (STACK->head->type       == pw_integer &&
        STACK->head->next->type == pw_integer) {
            int a = popInt();
            int b = popInt();
            pushInt(a + b);
            return 0;
    }
    if(STACK->head->type       & (pw_integer | pw_floating) &&
       STACK->head->next->type & (pw_integer | pw_floating)) {
            double c = popFloat();
            double d = popFloat();
            pushFloat(c + d);
            return 0;
    }
    printf("Incompatible types\n");
    return -1;
}

int stackSub() {
    if (STACK->length < 2) {
        printf("Stack Underflow - subtracring\n"); return -1; }
    if (STACK->head->type       == pw_integer &&
        STACK->head->next->type == pw_integer) {
            int a = popInt();
            int b = popInt();
            pushInt(a - b);
            return 0;
        }
        if (STACK->head->type       & (pw_integer | pw_floating) &&
            STACK->head->next->type & (pw_integer | pw_floating)) {
                double c = popFloat();
                double d = popFloat();
                pushFloat(c - d);
                return 0;
        }
        printf("Incompatiable types\n");
        return -1;
}

int stackMul() {
    if (STACK->length < 2) {
        printf("Stack Underflow - multiplying\n"); return -1; }
    if (STACK->head->type       == pw_integer &&
        STACK->head->next->type == pw_integer) {
            int a = popInt();
            int b = popInt();
            pushInt(a*b);
            return 0;
    }
    if (STACK->head->type       & (pw_integer | pw_floating) &&
        STACK->head->next->type & (pw_integer | pw_floating)) {
            double c = popFloat();
            double d = popFloat();
            pushFloat(c*d);
            return 0;
    }
    printf("Invalid types"); return -1;
}

int stackDiv() {
    if (STACK->length < 2) {
        printf("Stack Underflow - division\n"); return -1; }
    if (STACK->head->type       == pw_integer &&
        STACK->head->next->type == pw_integer) {
            int a = popInt();
            int b = popInt();
            if (b == 0) {
                printf("Division by 0: %d/%d", a, b);
                return -1;
            }
            pushInt(a / b);
            return 0;
    }
    if (STACK->head->type       & (pw_integer | pw_floating) &&
        STACK->head->next->type & (pw_integer | pw_floating)) {
            double c = popFloat();
            double d = popFloat();
            if (d == 0.0) {
                printf("Division by 0.0: %f/%f", c, d);
                return -1;
            }
            pushFloat(c / d);
            return 0;
    }

    printf("Invalid types -- operator '/'");
    return -1;
}

/* ======= Boolean operators ====== */
int stackNot() {
    if (!STACK->length) {
        printf("Emptey stack! - bool NOT\n"); return -1; }
    if (!(STACK->head->type & (pw_boolean | pw_integer))) {
        printf("Not a bool or an integer! - bool NOT\n");
        return -1; }
    int f = popInt();
    f = !f;
    f ?  pushTrue() : pushFalse();
    return 0;
}

int stackAnd() {
    if (STACK->length < 2) {
        printf("Stack underflow! bool AND\n"); return -1; }
    if (!(STACK->head->type       & (pw_boolean | pw_integer) ||
        !(STACK->head->next->type & (pw_boolean | pw_integer)))) {
            printf("Not a bool or an integer! - bool AND\n");
            return -1;
        }
    int g = popInt();
    int h = popInt();
    g && h ? pushTrue() : pushFalse();
    return 0;
}

int stackOr() {
    if (STACK->length < 2) {
        printf("Stack underflow! bool OR\n"); return -1; }
    if (!(STACK->head->type       & (pw_boolean | pw_integer) ||
        !(STACK->head->next->type & (pw_boolean | pw_integer)))) {
            printf("Not a bool or an integer! - bool AND\n");
            return -1;
        }
    int i = popInt();
    int j = popInt();
    i || j ? pushTrue() : pushFalse();
    return 0;
}

/* ======= Comparison operators =======*/
int stackLessThen() {
    if (STACK->length < 2) {
        printf("Stack underflow! -- Comparison less then\n");
        return -1;
    }
    if (STACK->head->type       & (pw_integer | pw_boolean) &&
        STACK->head->next->type & (pw_integer | pw_boolean)) {

        int k = popInt();
        int l = popInt();
        k < l ? pushTrue() : pushFalse();
        return 0;
    }
    if (STACK->head->type       & (pw_integer | pw_boolean | pw_floating) &&
        STACK->head->next->type & (pw_integer | pw_boolean | pw_floating)) {

            double m = popFloat();
            double n = popFloat();
            m < n ? pushTrue() : pushFalse();
            return 0;
    }
    printf("Incompatable types -- Comparison less then\n");
    return -1;
}

int stackLessEq() {
    if (STACK->length < 2) {
        printf("Stack underflow! -- Comparison less then\n");
        return -1;
    }
    if (STACK->head->type       & (pw_integer | pw_boolean) &&
        STACK->head->next->type & (pw_integer | pw_boolean)) {

        int k = popInt();
        int l = popInt();
        k <= l ? pushTrue() : pushFalse();
        return 0;
    }
    if (STACK->head->type       & (pw_integer | pw_boolean | pw_floating) &&
        STACK->head->next->type & (pw_integer | pw_boolean | pw_floating)) {

            double m = popFloat();
            double n = popFloat();
            m <= n ? pushTrue() : pushFalse();
            return 0;
    }
    printf("Incompatable types -- Comparison less then\n");
    return -1;
}

int stackMoreThen() {
    if (STACK->length < 2) {
        printf("Stack underflow! -- Comparison less then\n");
        return -1;
    }
    if (STACK->head->type       & (pw_integer | pw_boolean) &&
        STACK->head->next->type & (pw_integer | pw_boolean)) {

        int k = popInt();
        int l = popInt();
        k > l ? pushTrue() : pushFalse();
        return 0;
    }
    if (STACK->head->type       & (pw_integer | pw_boolean | pw_floating) &&
        STACK->head->next->type & (pw_integer | pw_boolean | pw_floating)) {

            double m = popFloat();
            double n = popFloat();
            m > n ? pushTrue() : pushFalse();
            return 0;
    }
    printf("Incompatable types -- Comparison less then\n");
    return -1;
}

int stackMoreEq() {
    if (STACK->length < 2) {
        printf("Stack underflow! -- Comparison less then\n");
        return -1;
    }
    if (STACK->head->type       & (pw_integer | pw_boolean) &&
        STACK->head->next->type & (pw_integer | pw_boolean)) {

        int k = popInt();
        int l = popInt();
        k >= l ? pushTrue() : pushFalse();
        return 0;
    }
    if (STACK->head->type       & (pw_integer | pw_boolean | pw_floating) &&
        STACK->head->next->type & (pw_integer | pw_boolean | pw_floating)) {

            double m = popFloat();
            double n = popFloat();
            m >= n ? pushTrue() : pushFalse();
            return 0;
    }
    printf("Incompatable types -- Comparison less then\n");
    return -1;
}

int stackEqual() {
    if (STACK->length < 2) {
        printf("Stack underflow! -- Comparison less then\n");
        return -1;
    }
    if (STACK->head->type       & (pw_integer | pw_boolean) &&
        STACK->head->next->type & (pw_integer | pw_boolean)) {

        int k = popInt();
        int l = popInt();
        k == l ? pushTrue() : pushFalse();
        return 0;
    }
    if (STACK->head->type       & (pw_integer | pw_boolean | pw_floating) &&
        STACK->head->next->type & (pw_integer | pw_boolean | pw_floating)) {

            double m = popFloat();
            double n = popFloat();
            m == n ? pushTrue() : pushFalse();
            return 0;
    }
    printf("Incompatable types -- Comparison less then\n");
    return -1;

}

int stackInequal() {
    if (STACK->length < 2) {
        printf("Stack underflow! -- Comparison less then\n");
        return -1;
    }
    if (STACK->head->type       & (pw_integer | pw_boolean) &&
        STACK->head->next->type & (pw_integer | pw_boolean)) {

        int k = popInt();
        int l = popInt();
        k != l ? pushTrue() : pushFalse();
        return 0;
    }
    if (STACK->head->type       & (pw_integer | pw_boolean | pw_floating) &&
        STACK->head->next->type & (pw_integer | pw_boolean | pw_floating)) {

            double m = popFloat();
            double n = popFloat();
            m != n ? pushTrue() : pushFalse();
            return 0;
    }
    printf("Incompatable types -- Comparison less then\n");
    return -1;

}

/* ======= Stack Operators ====== */
int stackSwap() {
    if (STACK->length < 2) {
        printf("Operation <-> reqiores a minimal of two values pushed\n");
        return -1;
    }
    stackNode* temp;
    temp              = STACK->head->next;
    STACK->head->next = temp ->next;
    temp ->next       = STACK->head;
    STACK->head       = temp;
    return 0;
}

int stackLROT() {
    if (STACK->length < 2) {
        printf("Operation <- requires a minimal of two values pushed\n");
        return -1;
    }

    STACK->tail->next->next = STACK->head;
    stackNode* trace        = STACK->head;
    STACK->head             = STACK->tail->next;

    while (trace->next != STACK->tail){
        trace = trace->next;
    }

    /* Pointing to the left  <(^.^<) *\
    \* Pointing to the right (>^.^)> */

    STACK->tail = trace;
    STACK->tail->next->next = NULL;

    return 0;
}

int stackRROT() {
    if (STACK->length < 2) {
        printf("Operation -> requires a minimal of two values pushed\n");
        return -1;
    }
    /* DO NOT TOUCH */
    stackNode* temp  = STACK->tail->next;
    temp->next       = STACK->head;
    STACK->head      = STACK->head->next;
    STACK->tail      = temp;
    temp->next->next = NULL;

    return 0;
}

/* ======= Other ======= */

int getStackLength() {
    return STACK->length;
}

pwTypes getNextType() {
    if (!(STACK && STACK->head)) {
        printf("DEBUG invalid STACK or STACK->HEAD is false -- getNextType()");
        return nil;
    }
    return STACK->head->type;
}

int pushStackLength() {
    if (pushInt(getStackLength())) return -1;
    return 0;
}










