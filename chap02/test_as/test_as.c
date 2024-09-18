#include <stdio.h>
#include <stdlib.h>

#include <container/as.h>

static int *AS_PushEntry(struct AS *stack, int data)
{
    int *entry = malloc(sizeof(*entry));

    *entry = data;
    AS_Push(stack, entry);

    return entry;
}

static int AS_PopEntry(struct AS *stack)
{
    int *entry = AS_Pop(stack);
    int data = *entry;

    free(entry);

    return data;
}

static int AS_TopEntry(struct AS *stack) { return *(int *)AS_Top(stack); }

static struct AS *AS_CreateStack(size_t nr_entries)
{
    struct AS *stack = malloc(AS_BYTES(nr_entries));

    AS_Init(stack, nr_entries);

    return stack;
}

static void AS_DestroyStack(struct AS *stack)
{
    while (!AS_IsEmpty(stack))
        AS_PopEntry(stack);

    free(stack);
}

int main(int argc, char *argv[])
{
    size_t i;
    struct AS *stack = AS_CreateStack(10);

    AS_PushEntry(stack, 3);
    AS_PushEntry(stack, 37);
    AS_PushEntry(stack, 11);
    AS_PushEntry(stack, 12);

    printf("Capacity: %zu, Count: %zu, Top: %d\n\n", stack->nr_entries,
        AS_Count(stack), AS_TopEntry(stack));

    for (i = 0; i < 4; i++) {
        if (AS_IsEmpty(stack))
            break;

        printf("Popped: %d, ", AS_PopEntry(stack));

        if (!AS_IsEmpty(stack))
            printf("Current Top: %d\n", AS_TopEntry(stack));
        else
            printf("Stack Is Empty.\n");
    }

    AS_DestroyStack(stack);

    return 0;
}
