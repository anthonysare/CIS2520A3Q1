//
// Created by Anthony on 11/4/2018.
// sarea@uoguelph.ca
// Create an arithmetic tree from a postfix expression with options to convert
// to other expression forms, update variables and calculate the results
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "arithmeticTree.h"

/**
 * Creates a new node with double parameter
 * @param newData node data in double format
 * @return node that has been created
 */
treeNode_T *newNode(double newData) {
    treeNode_T *toCreate = malloc(sizeof(struct treeNode));
    toCreate->parent = toCreate;
    toCreate->left = NULL;
    toCreate->right = NULL;
    toCreate->data = newData;
    strcpy(toCreate->var, "NA");
    return toCreate;
}

/**
 * Creates a new node with with a string
 * @param newVar node data in string format
 * @return node that has been created
 */
treeNode_T *newVarNode(char newVar[3]) {
    treeNode_T *toCreate = malloc(sizeof(struct treeNode));
    toCreate->parent = toCreate;
    toCreate->left = NULL;
    toCreate->right = NULL;
    toCreate->data = 0.00;
    strcpy(toCreate->var, newVar);
    return toCreate;
}

/**
 *Checks if character is an operator
 * @param c char to be checked
 * @return 1 if operator, 0 otherwise
 */
int isOperator(char c) {
    switch (c) {
        case '+':
            return 1;
            break;
        case '-':
            return 1;
            break;
        case '*':
            return 1;
            break;
        case '/':
            return 1;
            break;
        default:
            return 0;
    }
}

/**
 * Pushes value onto stack
 * @param top pointer to top of stack
 * @param newNode node to be pushed onto stack
 */
void push(stack_t **top, treeNode_T *newNode) {
    //Creating new stack element
    stack_t *toAdd;
    toAdd = malloc(sizeof(stack_t));

    //Adding to top
    toAdd->node = newNode;
    toAdd->next = *top;
    *top = toAdd;
}

/**
 * Look at node at the top of stack without popping
 * @param top pointer to top of stack
 * @return binary Tree node at top of stack
 */
treeNode_T *peek(stack_t *top) {
    return top->node;
}

/**
 * Removes the top node on the stack returning its value
 * @param top pointer to top of stack
 * @return binary tree node at top of stack
 */
treeNode_T *pop(stack_t **top) {
    //Declare value and temp stack
    treeNode_T *newNode;
    stack_t *temp;

    //Check if stack is empty
    if (*top == NULL) {
        return NULL;
        //Move next item to top and return old tops value
    } else {
        temp = *top;
        *top = temp->next;
        newNode = temp->node;
        return newNode;
    }
}

/**
 * Creates a binary tree based on a given infix expression
 * @param expression infix expression to be added to tree
 * @return root of binary tree
 */
treeNode_T *createTree(char *expression) {
    int size = strlen(expression);
    stack_t *head;
    head = NULL;
    for (int i = 0; i < size; ++i) {
        //If char is digit, create new tree node with double data
        if (isdigit(expression[i]) != 0) {
            char tempData[5];
            tempData[0] = expression[i];
            tempData[1] = expression[i + 1];
            tempData[2] = expression[i + 2];
            tempData[3] = expression[i + 3];
            tempData[4] = '\0';
            treeNode_T *temp = newNode(atof(tempData));
            strcpy(temp->var, tempData);
            push(&head, temp);
            i += 3;
            //If char is variable, create new tree node with string data
        } else if (expression[i] == 'x') {
            char tempVar[3];
            tempVar[0] = expression[i];
            tempVar[1] = expression[i + 1];
            tempVar[2] = '\0';
            treeNode_T *temp = newVarNode(tempVar);
            push(&head, temp);
            i++;
            //If char is operator, create new tree node with string data
        } else if (isOperator(expression[i]) == 1) {
            char tempOp[2];
            tempOp[0] = expression[i];
            tempOp[1] = '\0';
            treeNode_T *temp = newVarNode(tempOp);
            push(&head, temp);
            //If closing bracket is reached, create an internal node and make it the new head
        } else if (expression[i] == ')') {
            head = createInternal(head);
        }
    }
    return head->node;
}
/**
 * Creates a tree node with right, left and head values
 * @param top pointer to top of stack
 * @return pointer to stack
 */
stack_t *createInternal(stack_t *top) {

    treeNode_T *temp = malloc(sizeof(treeNode_T));

    temp->right = peek(top);
    pop(&top);

    strcpy(temp->var, peek(top)->var);
    pop(&top);

    temp->left = peek(top);
    pop(&top);

    push(&top, temp);
    return top;
}

/**
 * Prints content of stack
 * @param toPrint stack to be printed
 */
void printStack(stack_t *toPrint) {
    stack_t *current;
    current = toPrint;
    while (current != NULL) {
        printf("Data: %.2lf Val: %s | ", current->node->data, current->node->var);
        current = current->next;
    }
    printf("\n");
}

/**
 * Traverses the binary tree and prints in preorder
 * @param root root of binary tree to be printed
 */
void preOrderPrint(treeNode_T *root) {
    if (root == NULL) {
        return;
    }
    printf("%s ", root->var);
    preOrderPrint(root->left);
    preOrderPrint(root->right);
}

/**
 * Traverses the binary tree and prints in postorder
 * @param root root of binary tree to be printed
 */
void postOrderPrint(treeNode_T *root) {
    if (root == NULL) {
        return;
    }
    postOrderPrint(root->left);
    postOrderPrint(root->right);

    printf("%s ", root->var);
}

/**
 * Traverses the binary tree and prints in inorder, adding brackets
 * @param root root of binary tree to be printed
 */
void inOrderPrint(treeNode_T *root) {
    if (root == NULL) {
        return;
    }
    if (root->left != NULL || root->right != NULL) {
        printf("(");
        inOrderPrint(root->left);
    }

    printf("%s ", root->var);
    if (root->left != NULL || root->right != NULL) {
        inOrderPrint(root->right);
        printf(") ");
    }

}

/**
 * Update placeholder variables with actual values
 * @param root  root of tree to be updated
 * @param var variable to be updated
 * @param input double to replace variable
 */
void updateVariables(treeNode_T *root, char var[4], double input) {
    if (root == NULL) {
        return;
    }
    updateVariables(root->left, var, input);
    if (strcmp(root->var, var) == 0) {
        root->data = input;
        printf("Variable updated\n");
    }
    updateVariables(root->right, var, input);
}

/**
 * Checks if a tree node is external
 * @param root root of tree to check
 * @return 0 if external, -1 otherwise
 */
int isExternal(treeNode_T *root) {
    if (root->right == NULL && root->left == NULL) {
        return 0;
    } else {
        return -1;
    }
}

/**
 * Displays the binary tree
 * @param root root of tree to be displayed
 */
void display(treeNode_T *root) {
    if (root == NULL) {
        return;
    }
    //Printing external nodes(variables and values)
    if (isExternal(root) == 0) {
        if (root->var[0] == 'x') {
            printf("Head: %s:%.2lf | ", root->var, root->data);
        } else {
            printf("Head: %.2lf | ", root->data);
        }
    } else {
        //Printing operators and variables
        printf("Head: %s | ", root->var);
        if (root->left->var[0] == 'x') {
            printf("Left: %s:%.2lf | ", root->left->var, root->left->data);
        } else if (isOperator(root->left->var[0])==0) {
            printf("Left: %s | ",root->left->var );
        } else {
            printf("Left: %.2lf | ", root->left->data);
        }

        if (root->right->var[0] == 'x') {
            printf("Right: %s:%.2lf | ", root->right->var, root->right->data);
        }else if(isOperator(root->right->var[0])){
            printf("Right: %s | ",root->right->var );
        } else {
            printf("Right: %.2lf | ", root->right->data);
        }
    }
    printf("\n");
    display(root->left);
    display(root->right);
}

/**
 * Performs operations on two values based on given character
 * @param op operator to use on values
 * @param val1 value 1
 * @param val2 value 2
 * @return result of operation
 */
double operation(char op, double val1, double val2){
    double result =0 ;

    switch (op){
        case 42:
            result = val1 * val2;
            break;
        case 43:
            result = val1 + val2;
            break;
        case 45:
            result = val1-val2;
            break;
        case 47:
            if(val2!=0.0) {
                result = val1 / val2;
            }else{
                printf("Attempt to divide by zero. Program aborted.\n");
            }
            break;
        default:
            printf("Invalid operation\n");
            break;
    }
    return result;
}

/**
 * Calculate result of expression
 * @param root root of binary tree to calculate result
 * @return result of calculation
 */
double calculate(treeNode_T *root){
    if(isOperator(root->var[0])==0){
        return root->data;
    }else{
        double x = calculate(root->left);
        double y = calculate(root->right);
        return operation(root->var[0], x, y);
    }
}







