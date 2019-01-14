//
// Created by Anthony on 11/5/2018.
//

#ifndef ASSIGNMENT3_ARITHMETICTREE_H
#define ASSIGNMENT3_ARITHMETICTREE_H
typedef struct treeNode {
    struct treeNode *parent;
    struct treeNode *left;
    struct treeNode *right;
    double data;
    char var[3];
} treeNode_T;

typedef struct Stack {
    treeNode_T *node;
    struct stack *next;
} stack_t;


treeNode_T *newNode(double newData);

treeNode_T *newVarNode(char newVar[3]);

int isOperator(char c);

void push(stack_t **top, treeNode_T *newNode);

treeNode_T *peek(stack_t *top);

treeNode_T *pop(stack_t **top);

treeNode_T *createTree(char *expression);

stack_t *createInternal(stack_t *top);

void printStack(stack_t *toPrint);

void preOrderPrint(treeNode_T *root);

void postOrderPrint(treeNode_T *root);

void inOrderPrint(treeNode_T *root);

void updateVariables(treeNode_T *root, char var[3], double input);

int isExternal(treeNode_T *root);

void display(treeNode_T *root);

double operation(char op, double val1, double val2);

double calculate(treeNode_T *root);



#endif //ASSIGNMENT3_ARITHMETICTREE_H
