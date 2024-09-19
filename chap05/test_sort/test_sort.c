#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <algorithm/bubblesort.h>
#include <algorithm/heapsort.h>
#include <algorithm/insertionsort.h>
#include <algorithm/mergesort.h>
#include <algorithm/quicksort.h>
#include <algorithm/radixsort.h>
#include <algorithm/selectionsort.h>
#include <algorithm/shellsort.h>

#define MAX_ELEM 10000

static int random_data[MAX_ELEM];
static int ref_data[MAX_ELEM];
static int data[MAX_ELEM];

static int Compare(const void *_a, const void *_b)
{
    int a = *(const int *)_a;
    int b = *(const int *)_b;

    return a - b;
}

static void __prepareRandomData(void)
{
    size_t i;

    for (i = 0; i < NR_ELEM(random_data); i++)
        random_data[i] = rand() % NR_ELEM(random_data);

    memcpy(ref_data, random_data, sizeof(random_data));
    qsort(ref_data, NR_ELEM(ref_data), sizeof(ref_data[0]), Compare);
}

static void ____benchmarkSortFunction(const char *name,
    void (*sort)(void *, size_t, size_t, int (*)(const void *, const void *)))
{
    clock_t start, end, time, seconds;
    bool result;

    memcpy(data, random_data, sizeof(data));

    start = clock();
    sort(data, NR_ELEM(data), sizeof(data[0]), Compare);
    end = clock();

    time = end - start;
    seconds = time / CLOCKS_PER_SEC;

    result = !memcmp(data, ref_data, sizeof(data));

    printf("[%s] %s sort took %ld processor time. (%ld seconds)\n",
        result ? "PASS" : "FAIL", name, time, seconds);
}

static void ____benchmarkSortFunctionAlt(const char *name,
    unsigned long long order,
    void (*sort)(void *, size_t, size_t, unsigned long long))
{
    clock_t start, end, time, seconds;
    bool result;

    memcpy(data, random_data, sizeof(data));

    start = clock();
    sort(data, NR_ELEM(data), sizeof(data[0]), order);
    end = clock();

    time = end - start;
    seconds = time / CLOCKS_PER_SEC;

    result = !memcmp(data, ref_data, sizeof(data));

    printf("[%s] %s (%llu) sort took %ld processor time. (%ld seconds)\n",
        result ? "PASS" : "FAIL", name, order, time, seconds);
}

#define __benchmarkSortFunction(sort) ____benchmarkSortFunction(#sort, sort)
#define __benchmarkSortFunctionAlt(sort, order)                                \
    ____benchmarkSortFunctionAlt(#sort, order, sort)

int main(int argc, char *argv[])
{
    srand(time(NULL));

    __prepareRandomData();

    __benchmarkSortFunction(BubbleSort);
    __benchmarkSortFunction(HeapSort);
    __benchmarkSortFunction(InsertionSort);
    __benchmarkSortFunction(MergeSort);
    __benchmarkSortFunction(SelectionSort);
    __benchmarkSortFunction(ShellSort);
    __benchmarkSortFunction(QuickSort);
    __benchmarkSortFunctionAlt(RadixSort, 1);
    __benchmarkSortFunctionAlt(RadixSort, 2);
    __benchmarkSortFunctionAlt(RadixSort, 3);
    __benchmarkSortFunctionAlt(RadixSort, 4);
    __benchmarkSortFunctionAlt(RadixSort, 5);

    __benchmarkSortFunction(qsort);

    return 0;
}
