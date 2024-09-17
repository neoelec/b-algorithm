#include <stdio.h>
#include <stdlib.h>

#ifndef NR_ELEM
#define NR_ELEM(a) ((sizeof(a)) / (sizeof((a)[0])))
#endif

static int Compare(const void *_a, const void *_b)
{
    int a = *(const int *)_a;
    int b = *(const int *)_b;

    return a - b;
}

int main(int argc, char *argv[])
{
    int data[] = { 6, 4, 2, 3, 1, 5 };
    size_t i;

    qsort(data, NR_ELEM(data), sizeof(data[0]), Compare);

    for (i = 0; i < NR_ELEM(data); i++)
        printf("%d ", data[i]);

    printf("\n");

    return 0;
}
