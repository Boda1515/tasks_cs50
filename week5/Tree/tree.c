#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int num;
    struct node* left;
    struct node* right;

}node;

void printroot(node *root);
int search (node *tree, int num);

int main (void)
{
    node *root = NULL;
    node *n = malloc(sizeof(node));
    if (n == NULL)
    {
        return 1;
    }
    n -> num = 2;
    n -> left = NULL;
    n -> right = NULL;
    root = n;
    // Once we assignment n to tree n become free we can use it in new node.
    n = malloc(sizeof(node));
    if (n == NULL)
    {
        return 1;
    }
    n -> num = 1;
    n -> left = NULL;
    n -> right = NULL;
    root->left = n;
    // Once we assignment n to tree n become free we can use it in new node.
    n = malloc(sizeof(node));
    if (n == NULL)
    {
        return 1;
    }
    n -> num = 3;
    n -> left = NULL;
    n -> right = NULL;
    root->right = n;

    printroot(root);
    search (root, 1);
}

void printroot(node *root)
{
    if (root == NULL)
    {
        return;
    }

    printroot(root->left);

    printf("%i\n", root->num);

    printroot(root->right);

    free(root);
}

int search (node *tree, int num)
{
    if (tree == NULL)
    {
        printf("The num : %i not found\n", num);
        return 1;
    }
    else if (num > tree->num)
    {
        // GO_RIGHT
        printf("GO_RIGHT\n");
        return search (tree->right, num);
    }
    else if (num < tree->num)
    {
        // GO_LEFT
        printf("GO_LEFT\n");
        return search (tree->left, num);
    }
    else
    {
        printf("The num : %i found\n", num);
        return 0;
    }
}