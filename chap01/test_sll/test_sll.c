#include <stdio.h>
#include <stdlib.h>

#include <container/sll.h>

struct SLL_Entry {
    struct SLL_Node node;
    int data;
};

static struct SLL_Entry *SLL_CreateEntry(int data)
{
    struct SLL_Entry *entry = malloc(sizeof(*entry));

    entry->data = data;

    return entry;
}

static void SLL_DestroyEntry(struct SLL_Node *node)
{
    struct SLL_Entry *entry = CONTAINER_OF(node, struct SLL_Entry, node);

    free(entry);
}

int main(int argc, char *argv[])
{
    size_t i;
    size_t count;
    struct SLL_Node head;
    struct SLL_Node *node;
    struct SLL_Entry *entry;

    SLL_Init(&head);

    /* 노드 5개 추가 */
    for (i = 0; i < 5; i++) {
        entry = SLL_CreateEntry(i);
        SLL_InsertTail(&head, &entry->node);
    }

    entry = SLL_CreateEntry(-1);
    SLL_InsertAfter(&head, &entry->node);

    entry = SLL_CreateEntry(-2);
    SLL_InsertAfter(&head, &entry->node);

    /* 리스트 출력 */
    count = SLL_Count(&head);

    for (i = 0; i < count; i++) {
        node = SLL_GetNode(&head, i);
        entry = CONTAINER_OF(node, struct SLL_Entry, node);
        printf("head[%zu] : %d\n", i, entry->data);
    }

    /* 리스트의 세 번째 노드 뒤에 새 노드 삽입 */
    printf("\nInserting 3000 After [2]...\n\n");

    node = SLL_GetNode(&head, 2);
    entry = SLL_CreateEntry(3000);

    SLL_InsertAfter(node, &entry->node);

    /* 리스트 출력 */
    count = SLL_Count(&head);
    for (i = 0; i < count; i++) {
        node = SLL_GetNode(&head, i);
        entry = CONTAINER_OF(node, struct SLL_Entry, node);
        printf("head[%zu] : %d\n", i, entry->data);
    }

    /* 모든 노드를 메모리에서 제거 */
    printf("\nDestroyihng List...\n");
    while (head.next) {
        node = head.next;
        SLL_Remove(&head, node);
        SLL_DestroyEntry(node);
    }

    return 0;
}
