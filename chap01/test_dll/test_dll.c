#include <stdio.h>
#include <stdlib.h>

#include <container/dll.h>

struct DLL_Entry {
    struct DLL_Node node;
    int data;
};

static struct DLL_Entry *DLL_CreateEntry(int data)
{
    struct DLL_Entry *entry = malloc(sizeof(*entry));

    entry->data = data;

    return entry;
}

static void DLL_DestroyEntry(struct DLL_Node *node)
{
    struct DLL_Entry *entry = CONTAINER_OF(node, struct DLL_Entry, node);

    free(entry);
}

int main(int argc, char *argv[])
{
    size_t i;
    size_t count;
    struct DLL_Node head;
    struct DLL_Node *node;
    struct DLL_Entry *entry;

    DLL_Init(&head);

    /* 노드 5개 추가 */
    for (i = 0; i < 5; i++) {
        entry = DLL_CreateEntry(i);
        DLL_InsertTail(&head, &entry->node);
    }

    /* 리스트 출력 */
    count = DLL_Count(&head);
    for (i = 0; i < count; i++) {
        node = DLL_GetNode(&head, i);
        entry = CONTAINER_OF(node, struct DLL_Entry, node);
        printf("head[%zu] : %d\n", i, entry->data);
    }

    /* 리스트의 세 번째 노드 뒤에 새 노드 삽입 */
    printf("\nInserting 3000 After [2]...\n\n");

    node = DLL_GetNode(&head, 2);
    entry = DLL_CreateEntry(3000);
    DLL_InsertAfter(node, &entry->node);

    /* 리스트 출력 */
    count = DLL_Count(&head);
    for (i = 0; i < count; i++) {
        node = DLL_GetNode(&head, i);
        entry = CONTAINER_OF(node, struct DLL_Entry, node);
        printf("head[%zu] : %d\n", i, entry->data);
    }

    /* 모든 노드를 메모리에서 제거 */
    printf("\nDestroyihng List...\n");
    while (head.next != &head) {
        node = head.next;
        DLL_Remove(node);
        DLL_DestroyEntry(node);
    }

    return 0;
}
