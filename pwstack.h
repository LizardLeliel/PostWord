#ifndef PW_STACK_FILE

/* Enums */
typedef enum PW_TYPES {
    nil = 0,
    pw_integer  = 1,
    pw_floating = 2,
    pw_boolean  = 4,
} pwTypes;

/* Node */
typedef struct PW_STACK_NODE {
    void*   data;
    pwTypes type;

    struct PW_STACK_NODE* next;
} stackNode;

/* Head */
typedef struct PW_STACK_HEAD {
    stackNode* head;
    stackNode* tail;

    size_t length;
} stackHead;

void initStack();
/* Pushing */
int pushInt(int n);
int pushFloat(double n);
int pushTrue();
int pushFalse();
/* Printing */
int printInt();
int printFloat();
/* Popping & Dupping */
int stackDup();
int pop();
int popInt();
double popFloat();
/* Arthimetic */
int stackAdd();
int stackSub();
int stackMul();
int stackDiv();
/* Boolean operators */
int stackNot();
int stackAnd();
int stackOr();
/* Stack Operations */
int stackSwap();
int stackLROT();
int stackRROT();
/* Others */
int getStackLength();
pwTypes getNextType();

#define PW_STACK_FILE
#endif /* PW_STACK_FILE */
