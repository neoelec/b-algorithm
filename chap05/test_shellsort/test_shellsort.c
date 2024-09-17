#include <stdio.h>

#include <algorithm/shellsort.h>

static int Compare(const void *_a, const void *_b)
{
    int a = *(const int *)_a;
    int b = *(const int *)_b;

    return a - b;
}

int main(int argc, char *argv[])
{
    int data[] = { 6, 4, 2, 3, 1, 5 };
    void *ptr_arr[NR_ELEM(data)];
    size_t i;

    for (i = 0; i < NR_ELEM(data); i++)
        ptr_arr[i] = &data[i];

    ShellSort(ptr_arr, NR_ELEM(data), Compare);

    for (i = 0; i < NR_ELEM(data); i++)
        printf("%d ", *(int *)ptr_arr[i]);

    printf("\n");

    return 0;
}
