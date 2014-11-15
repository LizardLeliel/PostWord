#ifndef PW_STACK_FILE

typedef struct PW_STACK_NODE {
    void* data;
    int   type;

    struct PW_STACK_NODE* next;
} stackNode;

typedef struct PW_STACK_HEAD {
    stackNode* head;
    stackNode* tail;

    size_t length;
} stackHead;

void initStack();
int pushInt(int n);
int printInt();
int pop();
int getStackLength();

#define PW_STACK_FILE
#endif /* PW_STACK_FILE */
