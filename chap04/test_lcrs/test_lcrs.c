#include <stdio.h>
#include <stdlib.h>

#include <container/lcrs.h>

struct LCRS_Entry {
    struct LCRS_Node node;
    char data;
};

static struct LCRS_Entry *LCRS_CreateEntry(char data)
{
    struct LCRS_Entry *entry = malloc(sizeof(*entry));

    LCRS_InitNode(&entry->node);
    entry->data = data;

    return entry;
}

static void LCRS_ChainEntry(struct LCRS_Entry *parent, struct LCRS_Entry *child)
{
    LCRS_Chain(&parent->node, &child->node);
}

static struct LCRS *LCRS_CreateTree(void)
{
    struct LCRS *tree = malloc(sizeof(*tree));

    LCRS_Init(tree);

    return tree;
}

static void __destroyEntry(struct LCRS_Node *node)
{
    struct LCRS_Entry *entry;

    if (node == NULL)
        return;

    entry = CONTAINER_OF(node, struct LCRS_Entry, node);

    __destroyEntry(node->left);
    __destroyEntry(node->right);

    free(entry);
}

static void LCRS_DestroyTree(struct LCRS *tree) { __destroyEntry(tree->root); }

static void __printEntry(const struct LCRS_Node *node, int depth)
{
    const struct LCRS_Entry *entry;

    if (node == NULL)
        return;

    entry = CONTAINER_OF(node, struct LCRS_Entry, node);
    printf("%*c\n", depth + 1, entry->data);
    __printEntry(node->left, depth + 1);
    __printEntry(node->right, depth);
}

static void LCRS_PrintTree(const struct LCRS *tree)
{
    __printEntry(tree->root, 0);
}

int main(int argc, char *argv[])
{
    struct LCRS *tree = LCRS_CreateTree();
    struct LCRS_Entry *A = LCRS_CreateEntry('A');
    struct LCRS_Entry *B = LCRS_CreateEntry('B');
    struct LCRS_Entry *C = LCRS_CreateEntry('C');
    struct LCRS_Entry *D = LCRS_CreateEntry('D');
    struct LCRS_Entry *E = LCRS_CreateEntry('E');
    struct LCRS_Entry *F = LCRS_CreateEntry('F');
    struct LCRS_Entry *G = LCRS_CreateEntry('G');
    struct LCRS_Entry *H = LCRS_CreateEntry('H');
    struct LCRS_Entry *I = LCRS_CreateEntry('I');
    struct LCRS_Entry *J = LCRS_CreateEntry('J');
    struct LCRS_Entry *K = LCRS_CreateEntry('K');

    tree->root = &A->node;

    LCRS_ChainEntry(A, B);
    LCRS_ChainEntry(B, C);
    LCRS_ChainEntry(B, D);
    LCRS_ChainEntry(D, E);
    LCRS_ChainEntry(D, F);
    LCRS_ChainEntry(A, G);
    LCRS_ChainEntry(G, H);
    LCRS_ChainEntry(A, I);
    LCRS_ChainEntry(I, J);
    LCRS_ChainEntry(J, K);

    LCRS_PrintTree(tree);

    LCRS_DestroyTree(tree);

    return 0;
}
