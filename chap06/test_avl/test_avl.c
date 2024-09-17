#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#include <container/avl.h>

struct AVL_Entry {
    struct AVL_Node node;
    int data;
};

static int Compare(const struct AVL_Node *_a, const struct AVL_Node *_b)
{
    const struct AVL_Entry *a = CONTAINER_OF(_a, struct AVL_Entry, node);
    const struct AVL_Entry *b = CONTAINER_OF(_b, struct AVL_Entry, node);

    return a->data - b->data;
}

static struct AVL_Entry *AVL_InsertEntry(struct AVL *tree, int data)
{
    struct AVL_Entry *entry = malloc(sizeof(*entry));

    entry->data = data;
    AVL_Insert(tree, &entry->node);

    return entry;
}

static struct AVL_Entry *AVL_SearchEntry(struct AVL *tree, int data)
{
    struct AVL_Entry key_entry = {
        .data = data,
    };
    struct AVL_Node *x = AVL_Search(tree, &(key_entry.node));

    if (x == NULL)
        return NULL;

    return CONTAINER_OF(x, struct AVL_Entry, node);
}

static struct AVL_Entry *AVL_RemoveEntry(struct AVL *tree, int data)
{
    struct AVL_Entry *entry = AVL_SearchEntry(tree, data);

    if (entry != NULL)
        AVL_Remove(tree, &entry->node);

    return entry;
}

static void AVL_DestroyEntry(struct AVL_Entry *entry) { free(entry); }

static void AVL_PrintEntry(struct AVL_Node *node, void *private)
{
    struct AVL_Entry *entry = CONTAINER_OF(node, struct AVL_Entry, node);

    printf("%d ", entry->data);
}

static struct AVL *AVL_CreateTree(void)
{
    struct AVL *tree = malloc(sizeof(*tree));

    AVL_Init(tree, Compare);

    return tree;
}

static void AVL_DestroyTree(struct AVL *tree)
{
    struct AVL_Node *node;

    node = AVL_Minimum(tree);
    while (node != NULL) {
        struct AVL_Entry *entry = CONTAINER_OF(node, struct AVL_Entry, node);

        AVL_Remove(tree, node);
        AVL_DestroyEntry(entry);

        node = AVL_Minimum(tree);
    }

    free(tree);
}

int main(int argc, char *argv[])
{
    struct AVL *tree = AVL_CreateTree();

    AVL_InsertEntry(tree, 95);
    AVL_InsertEntry(tree, 87);
    AVL_InsertEntry(tree, 13);
    AVL_InsertEntry(tree, 12);
    AVL_InsertEntry(tree, 15);
    AVL_InsertEntry(tree, 14);
    AVL_InsertEntry(tree, 32);
    AVL_InsertEntry(tree, 123);
    AVL_InsertEntry(tree, 174);

    while (1) {
        unsigned int cmd;
        int data;
        struct AVL_Entry *entry;

        printf("\n\n------- AVL TREE --------\n");
        printf("\n(1) Create a node");
        printf("\n(2) Remove a node");
        printf("\n(3) Search a node");
        printf("\n(4) Print Forward");
        printf("\n(5) Print Reverse");
        printf("\n(6) Print Inorder");
        printf("\n(7) Print Preorder");
        printf("\n(8) Print Postorder");
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
            AVL_InsertEntry(tree, data);
            break;

        case 2:
            entry = AVL_RemoveEntry(tree, data);
            if (entry == NULL)
                printf("\nNot found node to delete:%d", data);
            else
                AVL_DestroyEntry(entry);

        case 3:
            entry = AVL_SearchEntry(tree, data);
            if (entry == NULL)
                printf("\nNot found node: %d", data);
            else
                printf("\nFound node: %d", entry->data);

            break;

        case 4:
            AVL_Forward(tree, AVL_PrintEntry, NULL);
            break;

        case 5:
            AVL_Reverse(tree, AVL_PrintEntry, NULL);
            break;

        case 6:
            AVL_Inorder(tree, AVL_PrintEntry, NULL);
            break;

        case 7:
            AVL_Preorder(tree, AVL_PrintEntry, NULL);
            break;

        case 8:
            AVL_Postorder(tree, AVL_PrintEntry, NULL);
            break;

        default:
            printf("\n\tInvalid Choice\n");
        }
    }

    AVL_DestroyTree(tree);

    return 0;
}
