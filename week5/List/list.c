#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int num;
    // This is the pointer.
    struct node *next;
}node;

int main (void)
{
    // I want to make firsy node (pointer)
    // Notice it's equal null because it is not pointing yet to any thing.
    node *list = NULL;

    // Create node in heap
    // node *n = malloc(4 + 8);
    // Notice that is n is pointing to the location in memory not equal!
    node *n = malloc(sizeof(node));
    if (n == NULL)
    {
        return 1;
    }
    // Third we put the value in the node.
    //*n.number = 1;
    // or and this is better.
    n->num = 1;
    n->next = NULL;
    list = n;
    n = malloc(sizeof(node));
    if (n == NULL)
    {
        // NOtice there is the node we asigened value to it
        free(list);
        return 1;
    }
    // Add value to the newest node.
    n->num = 2;
    n->next = NULL;
    // We need to include the new node to linked list
    // By make node(pointer(next)) pointing at the next node.
    list ->next = n;

    n = malloc(sizeof(node));
    if (n == NULL)
    {
        // Ranking here of waht the malloc free first is important
        free(list->next);
        free(list);
        return 1;
    }
    n->num = 3;
    n->next = NULL;
    list->next->next = n;

    n = malloc(sizeof(node));
    if (n != NULL)
    {
        n->num = 0;
        n->next = NULL;
        n->next = list;
        list = n;
    }
    n = malloc(sizeof(node));
    if (n != NULL)
    {
        n->num = 11;
        n->next = NULL;
        n->next = list->next;
        list->next = n;
    }
    n = malloc(sizeof(node));
    if (n != NULL)
    {
        n->num = 13;
        n->next = NULL;
        n->next = list->next->next->next->next;
        list->next->next->next->next = n;
    }

    for (node* tmp = list; tmp != NULL;tmp = tmp->next)
    {
        printf("n: %i\n", tmp->num);
    }

    // We need to free all node
    while (list != NULL)
    {
        node *tmp = list->next;
        free(list);
        list = tmp;
    }

}