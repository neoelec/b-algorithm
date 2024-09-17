#include <stdio.h>

#include "score.h"
#include <algorithm/binarysearch.h>
#include <algorithm/quicksort.h>

static int Compare(const void *_elem1, const void *_elem2)
{
    struct Score *elem1 = (struct Score *)_elem1;
    struct Score *elem2 = (struct Score *)_elem2;

    if (elem1->score > elem2->score)
        return 1;
    else if (elem1->score < elem2->score)
        return -1;
    else
        return 0;
}

int main(int argc, char *argv[])
{
    struct Score key = {
        .score = 671.78,
    };
    struct Score *found;
    size_t nmemb = SCORE_NrData();
    void *ptr_arr[nmemb];
    size_t i;

    for (i = 0; i < nmemb; i++)
        ptr_arr[i] = &score_data_set[i];

    QuickSort(ptr_arr, nmemb, Compare);
    found = BinarySearch(&key, ptr_arr, nmemb, Compare);

    printf("found: %u %f\n", found->number, found->score);

    return 0;
}
