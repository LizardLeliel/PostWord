#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Data emplaced on stack */
typedef struct PW_STACK_NODE {
    void* data;
    int   type;

    struct PW_STACK_NODE* next;
} stackNode;

/* contains pointers to tail and head */
typedef struct PW_STACK_HEAD {
    stackNode* head;
    stackNode* tail;

    size_t length;
} stackHead;

/* The stack postward uses */
stackHead* pwSTACK;

/* Prepare the stack*/
void initStack() {
    pwSTACK       = (stackHead*)malloc(sizeof(stackHead));
    pwSTACK->head = (stackNode*)malloc(sizeof(stackNode));

    pwSTACK->tail   = pwSTACK->head;
    pwSTACK->length = 0;

    pwSTACK->tail->data = NULL;
    pwSTACK->tail->next = NULL;
    pwSTACK->tail->type = 0;

}

/* Pop anything off of the stack */
int pop() {
    if (pwSTACK->length == 0) {
        printf("Stack Underflow - popping\n");
        return -1;
    }

    stackNode* temp = pwSTACK->head;
    pwSTACK->head = temp->next;

    free(temp->data);
    free(temp);

    --pwSTACK->length;
    return 0;
}

/* push an int onto the stack */
int pushInt(int n) {
    stackNode* newNode = (stackNode*)malloc(sizeof(stackNode));

    if (!newNode) {printf("Bad_alloc\n"); return -1;}

    newNode->data = malloc(sizeof(int));
    *(int*)newNode->data = n;
    newNode->type = 1;

    newNode->next = pwSTACK->head;
    pwSTACK->head = newNode;

    ++pwSTACK->length;

    return 0;
}

/* print an integer and pop */
int printInt() {
    if (pwSTACK->length == 0) {
        printf("Stack Underflow -- int print\n");
        return -1;
    }

    printf("%d", *(int*)pwSTACK->head->data);

    if (pop()) {
        printf("in printInt\n"); return -1;
    }

    return 0;
}

int getStackLength() {
    return pwSTACK->length;
}












