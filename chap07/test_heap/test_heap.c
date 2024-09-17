#include <stdio.h>
#include <stdlib.h>

#include <container/heap.h>

struct Heap_Container {
    struct Heap *heap;
};

static int Compare(const void *_a, const void *_b)
{
    int a = *(const int *)_a;
    int b = *(const int *)_b;

    return a - b;
}

static void Heap_InsertEntry(struct Heap_Container *h, int data)
{
    int *entry = malloc(sizeof(*entry));

    *entry = data;

    h->heap = Heap_Resize(h->heap);
    Heap_Insert(h->heap, entry);
}

static int Heap_RemoveHeadEntry(struct Heap_Container *h)
{
    int *entry = Heap_RemoveHead(h->heap);
    int data = *entry;

    free(entry);
    h->heap = Heap_Resize(h->heap);

    return data;
}

static void Heap_PrintEntry(void *_entry, void *private)
{
    int *entry = _entry;

    printf("%d ", *entry);
}

static struct Heap_Container *Heap_CreateHeap(void)
{
    struct Heap_Container *h = malloc(sizeof(*h));
    struct Heap *heap = malloc(HEAP_BYTES_MIN);

    Heap_Init(heap, Compare);
    h->heap = heap;

    return h;
}

static void Heap_PrintHeap(struct Heap_Container *h)
{
    Heap_Forward(h->heap, Heap_PrintEntry, NULL);
    printf("\n");
}

static void Heap_DestroyHeap(struct Heap_Container *h)
{
    while (h->heap->used)
        Heap_RemoveHeadEntry(h);

    free(h);
}

int main(int argc, char *argv[])
{
    struct Heap_Container *h = Heap_CreateHeap();

    Heap_InsertEntry(h, 12);
    Heap_InsertEntry(h, 87);
    Heap_InsertEntry(h, 111);
    Heap_InsertEntry(h, 34);
    Heap_InsertEntry(h, 15);
    Heap_InsertEntry(h, 75);
    Heap_PrintHeap(h);

    Heap_RemoveHeadEntry(h);
    Heap_PrintHeap(h);

    Heap_RemoveHeadEntry(h);
    Heap_PrintHeap(h);

    Heap_RemoveHeadEntry(h);
    Heap_PrintHeap(h);

    Heap_RemoveHeadEntry(h);
    Heap_PrintHeap(h);

    Heap_RemoveHeadEntry(h);
    Heap_PrintHeap(h);

    Heap_DestroyHeap(h);

    return 0;
}
