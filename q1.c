#include <stdio.h>
#include "arithmeticTree.c"
#include "arithmeticTree.h"

//(((x1+5.12)*(x2-7.68))/x3)
int main(int argc, char *argv[]) {
    //User input variables
    int input = 0;
    char varName[3];
    double varValue;
    double result;
    int inputTest;
    //Declaring and initializing bianry tree with command line input
    treeNode_T *userTree;
    userTree = createTree(argv[1]);

    //Initial User I/O
    printf("Welcome to the arithmetic tree simulator!\n"
           "Please choose an option:\n"
           "1. Display\n"
           "2. Preorder\n"
           "3. Inorder\n"
           "4. Postorder\n"
           "5. Update\n"
           "6. Calculate\n"
           "7. Exit\n");
    //I/O loop
    while (input != 7) {
        scanf("%d", &input);
        switch (input) {
            case 1: //Display binary tree
                display(userTree);
                break;
            case 2://Print preorder of expression
                printf("Preorder:\n");
                preOrderPrint(userTree);
                printf("\n");
                break;
            case 3://Print inorder of expression
                printf("Inorder:\n");
                inOrderPrint(userTree);
                printf("\n");
                break;
            case 4://Print postorder of expression
                printf("Postorder:\n");
                postOrderPrint(userTree);
                printf("\n");
                break;
            case 5://Allow user to set variables of expression
                printf("Please enter the variable name(Ex. x1): ");
                scanf("%s", varName);
                if (varName[0] == 'x' && varName[1] >= 48 && varName[1] <= 57) {
                    printf("Please enter the variable value(Ex. 2.50): ");
                    scanf("%lf", &varValue);
                    updateVariables(userTree, varName, varValue);
                }else{
                    printf("Invalid variable name. Variable must be in format x# with # being 0-9\n");
                }
                break;
            case 6: //Print result of expression
                result = calculate(userTree);
                printf("Result: %.2lf\n", result);
                calculate(userTree);
                break;
            case 7: //Exit program
                printf("Goodbye!\n");
                break;
            default: //Invalid input catch
                printf("Please enter valid input (1-7)\n");
        }
        if (input != 7) {
            printf("Please enter another option:\n");
        }
    }


    return 0;
}