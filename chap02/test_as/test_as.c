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

static struct AS *AS_CreateStack(size_t nr_entries)
{
    struct AS *stack = malloc(AS_BYTES(nr_entries));

    AS_Init(stack, nr_entries);

    return stack;
}

static void AS_DestroyStack(struct AS *stack)
{
    while (!AS_IsEmpty(stack))
        free(AS_Pop(stack));

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
        AS_Count(stack), *(int *)AS_Top(stack));

    for (i = 0; i < 4; i++) {
        if (AS_IsEmpty(stack))
            break;

        printf("Popped: %d, ", *(int *)AS_Pop(stack));

        if (!AS_IsEmpty(stack))
            printf("Current Top: %d\n", *(int *)AS_Top(stack));
        else
            printf("Stack Is Empty.\n");
    }

    AS_DestroyStack(stack);

    return 0;
}
