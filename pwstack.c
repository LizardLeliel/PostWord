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
    stackNode* tail;

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

    STACK->tail   = STACK->head;
    STACK->length = 0;

    STACK->tail->data = NULL;
    STACK->tail->next = NULL;
    STACK->tail->type = nil;

    memsize[pw_integer]  = sizeof(int);
    memsize[pw_floating] = sizeof(double);

}


/* Pop anything off of the stack */
int pop() {
    if (STACK->length == 0) {
        printf("Stack Underflow - popping\n");
        return -1;
    }

    stackNode* temp = STACK->head;
    STACK->head = temp->next;

    free(temp->data);
    free(temp);

    --STACK->length;
    return 0;
}

int stackDup() {
    stackNode* newNode = (stackNode*)malloc(sizeof(stackNode));
    if (!newNode) {printf("Bad_alloc\n"); return -1; }

    newNode->type = STACK->head->type;
    newNode->data = malloc(memsize[newNode->type]);

    memcpy(newNode->data, STACK->head->data, memsize[newNode->type]);

    newNode->next = STACK->head;
    STACK  ->head = newNode;

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
    STACK->head = newNode;

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

    newNode->next = STACK->head;
    STACK->head   = newNode;

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

/* Pop and return int */

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


/* Add top two nodes */
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

/* Subtract top two nodes */


int getStackLength() {
    return STACK->length;
}

pwTypes getNextType() {
    if (!(STACK && STACK->head)) {
        printf("Something bad happened\n");
        return nil;
    }
    return STACK->head->type;
}











