#include <stdio.h>
#include <stdlib.h>

#include <container/lls.h>

struct LLS_Entry {
    struct SLL_Node node;
    const char *data;
};

static struct LLS_Entry *LLS_PushEntry(struct LLS *stack, const char *data)
{
    struct LLS_Entry *entry = malloc(sizeof(*entry));

    entry->data = data;
    LLS_Push(stack, &entry->node);

    return entry;
}

static struct LLS_Entry *LLS_PopEntry(struct LLS *stack)
{
    return CONTAINER_OF(LLS_Pop(stack), struct LLS_Entry, node);
}

static struct LLS_Entry *LLS_TopEntry(struct LLS *stack)
{
    return CONTAINER_OF(LLS_Top(stack), struct LLS_Entry, node);
}

static struct LLS *LLS_CreateStack(void)
{
    struct LLS *stack = malloc(sizeof(*stack));

    LLS_Init(stack);

    return stack;
}

static void LLS_DestroyStack(struct LLS *stack)
{
    while (!LLS_IsEmpty(stack))
        free(LLS_PopEntry(stack));

    free(stack);
}

int main(int argc, char *argv[])
{
    size_t i;
    size_t count;
    struct LLS *stack = LLS_CreateStack();
    struct LLS_Entry *popped;

    LLS_PushEntry(stack, "abc");
    LLS_PushEntry(stack, "def");
    LLS_PushEntry(stack, "efg");
    LLS_PushEntry(stack, "hij");

    count = LLS_Count(stack);
    printf("Count: %zu, Top: %s\n\n", count, LLS_TopEntry(stack)->data);

    for (i = 0; i < count; i++) {
        if (LLS_IsEmpty(stack))
            break;

        popped = LLS_PopEntry(stack);
        printf("Popped: %s, ", popped->data);

        free(popped);

        if (!LLS_IsEmpty(stack)) {
            printf("Current Top: %s\n", LLS_TopEntry(stack)->data);
        } else
            printf("Stack Is Empty.\n");
    }

    LLS_DestroyStack(stack);

    return 0;
}
