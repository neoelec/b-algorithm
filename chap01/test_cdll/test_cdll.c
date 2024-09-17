#include <stdio.h>
#include <stdlib.h>

#include <container/cdll.h>

struct CDLL_Entry {
    struct DLL_Node node;
    int data;
};

static struct CDLL_Entry *CDLL_CreateEntry(int data)
{
    struct CDLL_Entry *entry = malloc(sizeof(*entry));

    entry->data = data;

    return entry;
}

static void CDLL_DestroyEntry(void *_list, struct DLL_Node *node)
{
    struct CDLL_Entry *entry = CONTAINER_OF(node, struct CDLL_Entry, node);

    free(entry);
}

int main(int argc, char *argv[])
{
    size_t i;
    size_t count;
    struct CDLL list;
    struct DLL_Node *node;
    struct CDLL_Entry *entry;

    CDLL_Init(&list);

    /* 노드 5개 추가 */
    for (i = 0; i < 5; i++) {
        entry = CDLL_CreateEntry(i);
        CDLL_InsertTail(&list, &entry->node);
    }

    /* 리스트 출력 */
    count = CDLL_Count(&list);

    for (i = 0; i < count; i++) {
        node = CDLL_GetNode(&list, i);
        entry = CONTAINER_OF(node, struct CDLL_Entry, node);
        printf("list[%zu] : %d\n", i, entry->data);
    }

    /* 리스트의 세 번째 노드 뒤에 새 노드 삽입 */
    printf("\nInserting 3000 After [2]...\n\n");

    node = CDLL_GetNode(&list, 2);
    entry = CDLL_CreateEntry(3000);
    CDLL_InsertAfter(node, &entry->node);

    printf("\nRemoving Node at 2...\n");
    node = CDLL_GetNode(&list, 2);
    CDLL_Remove(&list, node);
    CDLL_DestroyEntry(&list, node);

    /* 리스트 출력 */
    /* (노드 수의 2배만큼 루프를 돌며 환형임을 확인한다.) */
    count = CDLL_Count(&list);
    for (i = 0; i < count * 2; i++) {
        node = CDLL_GetNode(&list, i);
        entry = CONTAINER_OF(node, struct CDLL_Entry, node);
        printf("list[%zu] : %d\n", i, entry->data);
    }

    /* 모든 노드를 메모리에서 제거 */
    printf("\nDestroyihng List...\n");
    while (list.head) {
        node = list.head;
        CDLL_Remove(&list, node);
        CDLL_DestroyEntry(&list, node);
    }

    return 0;
}
