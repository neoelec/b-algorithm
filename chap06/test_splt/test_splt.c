#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>

#include <container/splt.h>

struct SPLT_Entry {
    struct SPLT_Node node;
    int data;
};

static int Compare(const struct SPLT_Node *_a, const struct SPLT_Node *_b)
{
    const struct SPLT_Entry *a = CONTAINER_OF(_a, struct SPLT_Entry, node);
    const struct SPLT_Entry *b = CONTAINER_OF(_b, struct SPLT_Entry, node);

    return a->data - b->data;
}
static struct SPLT_Entry *SPLT_SearchEntry(struct SPLT *tree, int data)
{
    struct SPLT_Entry key_entry = {
        .data = data,
    };
    struct SPLT_Node *x = SPLT_Search(tree, &(key_entry.node));

    if (x == NULL)
        return NULL;

    return CONTAINER_OF(x, struct SPLT_Entry, node);
}

static struct SPLT_Entry *SPLT_InsertEntry(struct SPLT *tree, int data)
{
    struct SPLT_Entry *entry;

    if (SPLT_SearchEntry(tree, data))
        return NULL;

    entry = malloc(sizeof(*entry));
    entry->data = data;
    SPLT_Insert(tree, &entry->node);

    return entry;
}

static struct SPLT_Entry *SPLT_RemoveEntry(struct SPLT *tree, int data)
{
    struct SPLT_Entry *entry = SPLT_SearchEntry(tree, data);

    if (entry != NULL)
        SPLT_Remove(tree, &entry->node);

    return entry;
}

static void SPLT_DestroyEntry(struct SPLT_Entry *entry) { free(entry); }

static void SPLT_PrintEntry(struct SPLT_Node *node, void *private)
{
    struct SPLT_Entry *entry = CONTAINER_OF(node, struct SPLT_Entry, node);

    printf("%d ", entry->data);
}

static struct SPLT *SPLT_CreateTree(void)
{
    struct SPLT *tree = malloc(sizeof(*tree));

    SPLT_Init(tree, Compare);

    return tree;
}

static void SPLT_DestroyTree(struct SPLT *tree)
{
    struct SPLT_Node *node;

    node = SPLT_Minimum(tree);
    while (node != NULL) {
        struct SPLT_Entry *entry = CONTAINER_OF(node, struct SPLT_Entry, node);

        SPLT_Remove(tree, node);
        SPLT_DestroyEntry(entry);

        node = SPLT_Minimum(tree);
    }

    free(tree);
}

static void SPLT_InsertEntriesRandomly(struct SPLT *tree)
{
    size_t i;

    for (i = 0; i < 100; i++) {
        if (!SPLT_InsertEntry(tree, rand() % 500))
            i--;
    }
}

static void SPLT_RemoveEntriesRandomly(struct SPLT *tree)
{
    struct SPLT_Entry *entry;

    while (!SPLT_IsEmpty(tree)) {
        entry = SPLT_RemoveEntry(tree, rand() % 500);
        if (entry)
            SPLT_DestroyEntry(entry);
    }
}

int main(int argc, char *argv[])
{
    struct SPLT *tree = SPLT_CreateTree();

    srand(time(NULL));

    while (1) {
        unsigned int cmd;
        int data;
        struct SPLT_Entry *entry;
        size_t i;

        printf("\n\n------- SPLT TREE --------\n");
        printf("\n(1) Create a node");
        printf("\n(2) Remove a node");
        printf("\n(3) Search a node");
        printf("\n(4) Print Forward");
        printf("\n(5) Print Backward");
        printf("\n(6) Print Inorder");
        printf("\n(7) Print Preorder");
        printf("\n(8) Print Postorder");
        printf("\n(10) Create 100 random nodes");
        printf("\n(11) Remove all nodes randomly");
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
            SPLT_InsertEntry(tree, data);
            break;

        case 2:
            entry = SPLT_RemoveEntry(tree, data);
            if (entry == NULL)
                printf("\nNot found node to delete:%d", data);
            else
                SPLT_DestroyEntry(entry);

        case 3:
            entry = SPLT_SearchEntry(tree, data);
            if (entry == NULL)
                printf("\nNot found node: %d", data);
            else
                printf("\nFound node: %d", entry->data);

            break;

        case 4:
            SPLT_Forward(tree, SPLT_PrintEntry, NULL);
            break;

        case 5:
            SPLT_Backward(tree, SPLT_PrintEntry, NULL);
            break;

        case 6:
            SPLT_Inorder(tree, SPLT_PrintEntry, NULL);
            break;

        case 7:
            SPLT_Preorder(tree, SPLT_PrintEntry, NULL);
            break;

        case 8:
            SPLT_Postorder(tree, SPLT_PrintEntry, NULL);
            break;

        case 10:
            SPLT_InsertEntriesRandomly(tree);
            break;

        case 11:
            SPLT_RemoveEntriesRandomly(tree);
            break;

        case 99:
            for (i = 0; i < 100; i++) {
                printf("[%.3zu]", i);
                SPLT_InsertEntriesRandomly(tree);
                printf(" - I->%s", SPLT_IsEmpty(tree) ? "FAIL" : "PASS");
                SPLT_RemoveEntriesRandomly(tree);
                printf(" / R->%s\n", !SPLT_IsEmpty(tree) ? "FAIL" : "PASS");
            }

            break;

        default:
            printf("\n\tInvalid Choice\n");
        }
    }

    SPLT_DestroyTree(tree);

    return 0;
}
