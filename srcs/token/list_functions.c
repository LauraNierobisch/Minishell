#include "minishell.h"
t_node *lstnew(char *args, char **filename, char **redirections)
{
    t_node *node = (t_node *)malloc(sizeof(t_node));
    if (!node)
        return NULL;
    
    node->args = args;
    node->filename = filename;
    node->redirections = redirections;
    node->prev = NULL;
    node->next = NULL;
    return node;
}
void lstadd_back(t_node **lst, t_node *new)
{
    t_node *last;

    if (*lst == NULL)
        *lst = new;  // Wenn die Liste leer ist, wird der neue Knoten der erste Knoten
    else
    {
        last = *lst;
        // Gehe zum letzten Knoten der Liste
        while (last->next != NULL)
            last = last->next;
        
        last->next = new;   // Setze den `next`-Zeiger des letzten Knotens auf den neuen Knoten
        new->prev = last;   // Setze den `prev`-Zeiger des neuen Knotens auf den letzten Knoten
    }
}
void lstremove(t_node **lst, t_node *node)
{
    if (node->prev)
        node->prev->next = node->next;  // Setze den `next`-Zeiger des vorherigen Knotens auf den nächsten Knoten

    if (node->next)
        node->next->prev = node->prev;  // Setze den `prev`-Zeiger des nächsten Knotens auf den vorherigen Knoten

    if (*lst == node)
        *lst = node->next;  // Wenn der zu entfernende Knoten der erste Knoten ist, aktualisiere den Head

    free(node);  // Knoten freigeben
}
