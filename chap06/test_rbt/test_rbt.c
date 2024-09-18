#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <container/rbt.h>

struct RBT_Entry {
    struct RBT_Node node;
    int data;
};

static int Compare(const struct RBT_Node *_a, const struct RBT_Node *_b)
{
    const struct RBT_Entry *a = CONTAINER_OF(_a, struct RBT_Entry, node);
    const struct RBT_Entry *b = CONTAINER_OF(_b, struct RBT_Entry, node);

    return a->data - b->data;
}

static struct RBT_Entry *RBT_InsertEntry(struct RBT *tree, int data)
{
    struct RBT_Entry *entry = malloc(sizeof(*entry));

    entry->data = data;
    RBT_Insert(tree, &entry->node);

    return entry;
}

static struct RBT_Entry *RBT_SearchEntry(struct RBT *tree, int data)
{
    struct RBT_Entry key_entry = {
        .data = data,
    };
    struct RBT_Node *x = RBT_Search(tree, &(key_entry.node));

    if (x == tree->NiL)
        return NULL;

    return CONTAINER_OF(x, struct RBT_Entry, node);
}

static struct RBT_Entry *RBT_RemoveEntry(struct RBT *tree, int data)
{
    struct RBT_Entry *entry = RBT_SearchEntry(tree, data);

    if (entry != NULL)
        RBT_Remove(tree, &entry->node);

    return entry;
}

static void RBT_DestroyEntry(struct RBT_Entry *entry) { free(entry); }

static void RBT_PrintEntry(struct RBT_Node *node, void *private)
{
    struct RBT_Entry *entry = CONTAINER_OF(node, struct RBT_Entry, node);

    printf("%d ", entry->data);
}

static void __DisplayEntry(
    struct RBT *tree, struct RBT_Node *node, size_t depth, size_t nr_black)
{
    size_t i;
    char c = 'x';
    int data = -1;
    char cnt[100];

    if (node == tree->NiL)
        return;

    if (node->color == RBT_BLACK)
        nr_black++;

    if (node->parent != tree->NiL) {
        data = (CONTAINER_OF(node->parent, struct RBT_Entry, node))->data;

        if (node->parent->left == node)
            c = 'L';
        else
            c = 'R';
    }

    if (node->left == tree->NiL && node->right == tree->NiL)
        sprintf(cnt, "--------- %zu", nr_black);
    else
        strncpy(cnt, "", sizeof(cnt));

    for (i = 0; i < depth; i++)
        printf("  ");

    printf("%d %s [%c,%d] %s\n",
        (CONTAINER_OF(node, struct RBT_Entry, node))->data,
        (node->color == RBT_RED) ? "RED" : "BLACK", c, data, cnt);

    __DisplayEntry(tree, node->left, depth + 1, nr_black);
    __DisplayEntry(tree, node->right, depth + 1, nr_black);
}

static void RBT_DisplayTree(struct RBT *tree)
{
    __DisplayEntry(tree, tree->root, 0, 0);
}

static struct RBT *RBT_CreateTree(void)
{
    struct RBT *tree = malloc(sizeof(*tree));

    RBT_Init(tree, Compare);

    return tree;
}

static void RBT_DestroyTree(struct RBT *tree)
{
    struct RBT_Node *node;
    struct RBT_Entry *entry;

    node = RBT_Minimum(tree);
    while (node != tree->NiL) {
        entry = CONTAINER_OF(node, struct RBT_Entry, node);
        RBT_Remove(tree, node);
        RBT_DestroyEntry(entry);

        node = RBT_Minimum(tree);
    }

    free(tree);
}

int main(int argc, char *argv[])
{
    struct RBT *tree = RBT_CreateTree();

    RBT_InsertEntry(tree, 95);
    RBT_InsertEntry(tree, 87);
    RBT_InsertEntry(tree, 13);
    RBT_InsertEntry(tree, 12);
    RBT_InsertEntry(tree, 15);
    RBT_InsertEntry(tree, 14);
    RBT_InsertEntry(tree, 32);
    RBT_InsertEntry(tree, 123);
    RBT_InsertEntry(tree, 174);

    while (1) {
        unsigned int cmd;
        int data;
        struct RBT_Entry *entry;

        printf("\n\n------- RB TREE --------\n");
        printf("\n(1) Create a node");
        printf("\n(2) Remove a node");
        printf("\n(3) Search a node");
        printf("\n(4) Print Forward");
        printf("\n(5) Print Backward");
        printf("\n(6) Print Inorder");
        printf("\n(7) Print Preorder");
        printf("\n(8) Print Postorder");
        printf("\n(9) Display Tree");
        printf("\n(0) Quit");

        printf("\n\nEnter Your Choice: ");
        scanf("%u", &cmd);

        if (cmd == 0) {
            printf("\n\tProgram Terminated\n");
            break;
        } else if (cmd >= 1 && cmd <= 3) {
            printf("\nEnter data: ");
            scanf("%d", &data);
        }

        switch (cmd) {
        case 1:
            RBT_InsertEntry(tree, data);
            break;

        case 2:
            entry = RBT_RemoveEntry(tree, data);
            if (entry == NULL)
                printf("\nNot found node to delete:%d", data);
            else
                RBT_DestroyEntry(entry);

            break;

        case 3:
            entry = RBT_SearchEntry(tree, data);
            if (entry == NULL)
                printf("\nNot found node: %d", data);
            else
                printf("\nFound node: %d (color:%s)", entry->data,
                    (entry->node.color == RBT_RED) ? "RED" : "BLACK");

        case 4:
            RBT_Forward(tree, RBT_PrintEntry, NULL);
            break;

        case 5:
            RBT_Backward(tree, RBT_PrintEntry, NULL);
            break;

        case 6:
            RBT_Inorder(tree, RBT_PrintEntry, NULL);
            break;

        case 7:
            RBT_Preorder(tree, RBT_PrintEntry, NULL);
            break;

        case 8:
            RBT_Postorder(tree, RBT_PrintEntry, NULL);
            break;

        case 9:
            RBT_DisplayTree(tree);
            break;

        default:
            printf("\n\tInvalid Choice\n");
        }

        printf("\n");
    }

    RBT_DestroyTree(tree);

    return 0;
}
