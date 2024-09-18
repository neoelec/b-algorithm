#include <stdio.h>
#include <stdlib.h>

#include <container/cq.h>

static void CQ_EnqueueEntry(struct CQ *queue, int data)
{
    int *entry = malloc(sizeof(*entry));

    *entry = data;
    CQ_Enqueue(queue, entry);
}

static int CQ_DequeueEntry(struct CQ *queue)
{
    int *entry = CQ_Dequeue(queue);
    int data = *entry;

    free(entry);

    return data;
}

static struct CQ *CQ_CreateQueue(size_t nr_entries)
{
    struct CQ *queue = malloc(CQ_BYTES(nr_entries));

    CQ_Init(queue, nr_entries);

    return queue;
}

static void CQ_DestroyQueue(struct CQ *queue)
{
    while (!CQ_IsEmpty(queue))
        CQ_DequeueEntry(queue);

    free(queue);
}

int main(int argc, char *argv[])
{
    int i;
    struct CQ *queue = CQ_CreateQueue(10);

    CQ_EnqueueEntry(queue, 1);
    CQ_EnqueueEntry(queue, 2);
    CQ_EnqueueEntry(queue, 3);
    CQ_EnqueueEntry(queue, 4);

    for (i = 0; i < 3; i++) {
        printf("Dequeue: %d, ", CQ_DequeueEntry(queue));
        printf("Front: %zu, Rear: %zu\n", queue->front, queue->rear);
    }

    i = 100;
    while (!CQ_IsFull(queue))
        CQ_EnqueueEntry(queue, i++);

    printf(
        "Capacity: %zu, Count:  %zu\n\n", queue->nr_entries, CQ_Count(queue));

    while (!CQ_IsEmpty(queue)) {
        printf("Dequeue: %d, ", CQ_DequeueEntry(queue));
        printf("Front: %zu, Rear: %zu\n", queue->front, queue->rear);
    }

    CQ_DestroyQueue(queue);

    return 0;
}
