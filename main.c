#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define NOLIK 0
#define NUMBER 1
#define VAR 2
#define OPERATOR 3
#define PLUS 4
#define MINUS 5
#define MULTIPLY 6
#define DIVIDE 7
#define X 8



struct Node // структура €чейки дерева
{
    int value;
    int flag;
    struct Node * left;
    struct Node * right;
};

struct Node * Create_Your_Own_Tree() //своЄ дерево
{
    struct Node * tree = malloc(sizeof(struct Node));
    /*tree -> value = NOLIK;
    tree -> flag = PLUS;
    tree -> left = calloc(1, sizeof(struct Node));
    tree -> right = calloc(1, sizeof(struct Node));
    tree -> left -> flag = NUMBER;
    tree -> left -> value = 1;
    tree -> right -> flag = VAR;
    tree -> right -> value = X;*/
    tree -> flag = MULTIPLY;
    tree -> value = NOLIK;
    tree -> left = malloc(sizeof(struct Node));
    tree -> left -> flag = PLUS;
    tree -> left -> value = NOLIK;
    tree -> left -> left = calloc(1, sizeof(struct Node));
    tree -> left -> left -> flag = NUMBER;
    tree -> left -> left -> value = 1;
    tree -> left -> right = calloc(1, sizeof(struct Node));
    tree -> left -> right -> flag = VAR;
    tree -> left -> right -> value = X;
    tree -> right = malloc(sizeof(struct Node));
    tree -> right -> flag = MINUS;
    tree -> right -> value = NOLIK;
    tree -> right -> left = calloc(1, sizeof(struct Node));
    tree -> right -> left -> flag = NUMBER;
    tree -> right -> left -> value = 1;
    tree -> right -> right = calloc(1, sizeof(struct Node));
    tree -> right -> right -> flag = VAR;
    tree -> right -> right -> value = X;

    return tree;
};

struct Node * CreateNode(int flag, int value) //создать дерево
{
    struct Node * tree = malloc(sizeof(struct Node));
    tree -> flag = flag;
    tree -> value = value;
    tree -> left = NULL;
    tree -> right = NULL;

    return tree;
};

struct Node * Copy(struct Node * tree) //создание копии поддерева
{
    struct Node * tree_copy = CreateNode(NUMBER, 0);
    tree_copy -> value = tree -> value;
    tree_copy -> flag = tree -> flag;
    if(tree -> left != NULL)
    tree_copy -> left = Copy(tree -> left);
    if(tree -> right != NULL)
    tree_copy -> right = Copy(tree -> right);
    return tree_copy;
};

struct Node * Diff(struct Node * tree) //продифференцировать дерево
{
    struct Node * tree_copy;
    switch(tree -> flag)
    {
        case NUMBER:
            {
                tree_copy = CreateNode(NUMBER, NOLIK);
                break;
            }
        case PLUS:
            {
                tree_copy = CreateNode(PLUS, NOLIK);
                tree_copy -> left = Diff(tree -> left);
                tree_copy -> right = Diff(tree -> right);
                break;
            }
        case MINUS:
            {
                tree_copy = CreateNode(MINUS, NOLIK);
                tree_copy -> left = Diff(tree -> left);
                tree_copy -> right = Diff(tree -> right);
                break;
            }
        case MULTIPLY:
            {
                tree_copy = CreateNode(PLUS, NOLIK);
                tree_copy -> left = CreateNode(MULTIPLY, NOLIK);
                tree_copy -> right = CreateNode(MULTIPLY, NOLIK);
                tree_copy -> left -> left = Diff(tree -> left);
                tree_copy -> left -> right = Copy(tree -> right);
                tree_copy -> right -> left = Copy(tree -> left);
                tree_copy -> right -> right = Diff(tree -> right);

                break;
            }
        case VAR:
            {
                tree_copy = CreateNode(NUMBER, 1);
                break;
            }
    }


    return tree_copy;
}

void PRINT_RESULT(struct Node* tree)
{
    switch(tree -> flag)
    {
        case NUMBER:
            {
                printf("%d", tree -> value);
                break;
            }
        case PLUS:
            {

                PRINT_RESULT(tree -> left);
                printf(" + ");
                PRINT_RESULT(tree -> right);
                break;
            }
        case MINUS:
            {
                PRINT_RESULT(tree -> left);
                printf(" - ");
                PRINT_RESULT(tree -> right);
                break;
            }
        case MULTIPLY:
            {
                if(tree -> left -> flag == PLUS || tree -> left -> flag == MINUS)
                {
                    printf("(");
                    PRINT_RESULT(tree -> left);
                    printf(")");
                }
                printf(" * ");
                if(tree -> right -> flag == PLUS || tree -> right -> flag == MINUS)
                {
                    printf("(");
                    PRINT_RESULT(tree -> right);
                    printf(")");
                }
                break;
            }
        case VAR:
            {
                printf("x");
                break;
            }
    }

}

void Destroy(struct Node * tree)
{
    if(tree -> left != NULL)
        Destroy(tree -> left);
    free(tree);
    if(tree -> right != NULL)
        Destroy(tree -> right);
}

int main()
{

    struct Node * tree = Create_Your_Own_Tree();
    struct Node * tree_result = CreateNode(NUMBER, NOLIK);
    tree_result = Diff(tree);
    PRINT_RESULT(tree_result);
    Destroy(tree);
    Destroy(tree_result);

    return 0;
}
