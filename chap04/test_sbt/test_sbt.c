#include <stdio.h>
#include <stdlib.h>

#include <container/sbt.h>

struct SBT_Entry {
    struct SBT_Node node;
    char data;
};

static struct SBT_Entry *SBT_CreateEntry(char data)
{
    struct SBT_Entry *entry = malloc(sizeof(*entry));

    entry->data = data;
    entry->node.left = NULL;
    entry->node.right = NULL;

    return entry;
}

static void SBT_DestroyEntry(struct SBT_Node *node)
{
    struct SBT_Entry *entry;

    if (node == NULL)
        return;

    entry = CONTAINER_OF(node, struct SBT_Entry, node);

    SBT_DestroyEntry(node->left);
    SBT_DestroyEntry(node->right);

    free(entry);
}

static void SBT_PrintEntry(struct SBT_Node *node, void *private)
{
    struct SBT_Entry *entry = CONTAINER_OF(node, struct SBT_Entry, node);

    printf(" %c", entry->data);
}

static struct SBT *SBT_CreateTree(void)
{
    struct SBT *tree = malloc(sizeof(*tree));

    SBT_Init(tree);

    return tree;
}

static void SBT_DestroyTree(struct SBT *tree)
{
    SBT_DestroyEntry(tree->root);
    free(tree);
}

int main(int argc, char *argv[])
{
    struct SBT *tree = SBT_CreateTree();
    struct SBT_Entry *A = SBT_CreateEntry('A');
    struct SBT_Entry *B = SBT_CreateEntry('B');
    struct SBT_Entry *C = SBT_CreateEntry('C');
    struct SBT_Entry *D = SBT_CreateEntry('D');
    struct SBT_Entry *E = SBT_CreateEntry('E');
    struct SBT_Entry *F = SBT_CreateEntry('F');
    struct SBT_Entry *G = SBT_CreateEntry('G');

    tree->root = &A->node;

    A->node.left = &B->node;
    B->node.left = &C->node;
    B->node.right = &D->node;

    A->node.right = &E->node;
    E->node.left = &F->node;
    E->node.right = &G->node;

    printf("Preorder ...\n");
    SBT_Preorder(tree, SBT_PrintEntry, NULL);
    printf("\n\n");

    printf("Inorder ...\n");
    SBT_Inorder(tree, SBT_PrintEntry, NULL);
    printf("\n\n");

    printf("Postorder ...\n");
    SBT_Postorder(tree, SBT_PrintEntry, NULL);
    printf("\n\n");

    SBT_DestroyTree(tree);

    return 0;
}
