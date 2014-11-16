#ifndef PW_STACK_FILE

/* Enums */
typedef enum PW_TYPES {
    nil = 0,
    pw_integer  = 1,
    pw_floating = 2,
    pw_boolean  = 4,
    pw_string   = 8,
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
int pushString(char* ctring);
/* Printing */
int printInt();
int printFloat();
int printBool();
int printString();
int printTop();
int printsTop();
int putsTop();
/* Popping & Dupping */
int stackDup();
int pop();
int popInt();
double popFloat();
char* returnStringRef();
/* Arthimetic */
int stackAdd();
int stackSub();
int stackMul();
int stackDiv();
/* Boolean operators */
int stackNot();
int stackAnd();
int stackOr();
/* Comparison operators */
int stackLessThen();
int stackLessEq();
int stackMoreThen();
int stackMoreEq();
int stackEqual();
int stackInequal();
/* Stack Operations */
int stackSwap();
int stackLROT();
int stackRROT();
/* Others */
int getStackLength();
pwTypes getNextType();
int pushStackLength();

#define PW_STACK_FILE
#endif /* PW_STACK_FILE */
