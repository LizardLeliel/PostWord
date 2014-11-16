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

/* Prepare the stack*/
void initStack() {
    STACK       = (stackHead*)malloc(sizeof(stackHead));
    STACK->head = (stackNode*)malloc(sizeof(stackNode));

    STACK->tail       = (stackNode*)malloc(sizeof(stackNode));
    STACK->tail->next = (stackNode*)malloc(sizeof(stackNode));
    STACK->length     = 0;

    memsize[pw_integer]  = sizeof(int);
    memsize[pw_floating] = sizeof(double);

}

/* Sets STACK->tail to point to head */
int setTail() {
    printf("Setting Tail\n");
    STACK->tail = STACK->head;
    return 0;
}

/* Pop anything off of the stack */
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

/* dups top */
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

/* push an int onto the stack */
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

/* push a double onto the stack */
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

/* print an integer and pop */
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

/* print a double and pop*/
int printFloat() {
    if (STACK->length == 0) {
        printf("Stack Underflow -- double print\n");
        return -1;
    }

    printf("%f", *(double*)STACK->head->data);

    if (pop()) {
        printf("D: in PrintFloat()\n");
    }
}

/* pop and return int */
int popInt() {
    int a = *(int*)STACK->head->data;
    pop();
    return a;
}

/* pop and return a double */
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
    stackNode* trace = STACK->head;
    STACK->head = STACK->tail->next;

    while (trace->next != STACK->tail){
        trace = trace->next;
    }

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
        printf("DEBUG invalid STACK or STACK->HEAD is false\n");
        printf("%d\n", STACK);
        return nil;
    }
    return STACK->head->type;
}











