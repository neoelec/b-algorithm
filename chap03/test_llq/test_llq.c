#include <stdio.h>
#include <stdlib.h>

#include <container/llq.h>

struct LLQ_Entry {
    struct DLL_Node node;
    const char *data;
};

static struct LLQ_Entry *LLQ_EnqueueEntry(struct LLQ *queue, const char *data)
{
    struct LLQ_Entry *entry = malloc(sizeof(*entry));

    entry->data = data;
    LLQ_Enqueue(queue, &entry->node);

    return entry;
}

static struct LLQ_Entry *LLQ_DequeueEntry(struct LLQ *queue)
{
    struct DLL_Node *node = LLQ_Dequeue(queue);

    return CONTAINER_OF(node, struct LLQ_Entry, node);
}

static struct LLQ *LLQ_CreateQueue(void)
{
    struct LLQ *queue = malloc(sizeof(*queue));

    LLQ_Init(queue);

    return queue;
}

static void LLQ_DestroyQueue(struct LLQ *queue)
{
    while (!LLQ_IsEmpty(queue))
        free(LLQ_DequeueEntry(queue));

    free(queue);
}

int main(int argc, char *argv[])
{
    struct LLQ_Entry *entry;
    struct LLQ *queue = LLQ_CreateQueue();

    LLQ_EnqueueEntry(queue, "abc");
    LLQ_EnqueueEntry(queue, "def");
    LLQ_EnqueueEntry(queue, "efg");
    LLQ_EnqueueEntry(queue, "hij");

    printf("Count: %zu\n\n", queue->count);

    while (!LLQ_IsEmpty(queue)) {
        entry = LLQ_DequeueEntry(queue);
        printf("Dequeue: %s\n", entry->data);
        free(entry);
    }

    LLQ_DestroyQueue(queue);

    return 0;
}
