#include <stdio.h>
#include <stdlib.h>

#include <container/bst.h>

struct BST_Entry {
    struct BST_Node node;
    int data;
};

static int Compare(const struct BST_Node *_a, const struct BST_Node *_b)
{
    const struct BST_Entry *a = CONTAINER_OF(_a, struct BST_Entry, node);
    const struct BST_Entry *b = CONTAINER_OF(_b, struct BST_Entry, node);

    return a->data - b->data;
}

static struct BST_Entry *BST_InsertEntry(struct BST *tree, int data)
{
    struct BST_Entry *entry = malloc(sizeof(*entry));

    entry->data = data;
    BST_Insert(tree, &entry->node);

    return entry;
}

static struct BST_Entry *BST_SearchEntry(struct BST *tree, int data)
{
    struct BST_Entry key_entry = {
        .data = data,
    };
    struct BST_Node *x = BST_Search(tree, &(key_entry.node));

    if (x == NULL)
        return NULL;

    return CONTAINER_OF(x, struct BST_Entry, node);
}

static struct BST_Entry *BST_RemoveEntry(struct BST *tree, int data)
{
    struct BST_Entry *entry = BST_SearchEntry(tree, data);

    if (entry != NULL)
        BST_Remove(tree, &entry->node);

    return entry;
}

static void BST_DestroyEntry(struct BST_Entry *entry) { free(entry); }

static void BST_PrintEntry(struct BST_Node *node, void *private)
{
    const struct BST_Entry *entry;

    entry = CONTAINER_OF(node, struct BST_Entry, node);
    printf(" %d", entry->data);
}

static struct BST *BST_CreateTree(void)
{
    struct BST *tree = malloc(sizeof(*tree));

    BST_Init(tree, Compare);

    return tree;
}

static void BST_DestroyTree(struct BST *tree)
{
    struct BST_Node *node;
    struct BST_Entry *entry;

    node = BST_Minimum(tree);
    while (node != NULL) {
        entry = CONTAINER_OF(node, struct BST_Entry, node);
        BST_Remove(tree, node);
        BST_DestroyEntry(entry);

        node = BST_Minimum(tree);
    }

    free(tree);
}

int main(int argc, char *argv[])
{
    struct BST *tree = BST_CreateTree();
    struct BST_Entry *entry;

    /* 트리에 노드 추가 */
    BST_InsertEntry(tree, 22);
    BST_InsertEntry(tree, 9918);
    BST_InsertEntry(tree, 424);
    BST_InsertEntry(tree, 17);
    BST_InsertEntry(tree, 3);

    BST_InsertEntry(tree, 98);
    BST_InsertEntry(tree, 38);

    BST_InsertEntry(tree, 760);
    BST_InsertEntry(tree, 317);
    BST_InsertEntry(tree, 1);

    /* 트리 출력 */
    BST_Inorder(tree, BST_PrintEntry, NULL);
    printf("\n");

    /* 특정 노드 삭제 */
    printf("Removing 98...\n");

    entry = BST_RemoveEntry(tree, 98);
    BST_DestroyEntry(entry);

    BST_Inorder(tree, BST_PrintEntry, NULL);
    printf("\n");

    /* 새 노드 삽입 */
    printf("Inserting 111...\n");

    BST_InsertEntry(tree, 111);
    BST_Inorder(tree, BST_PrintEntry, NULL);
    printf("\n");

    /* 트리 소멸시키기 */
    BST_DestroyTree(tree);

    return 0;
}
