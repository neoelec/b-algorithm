#include <stdio.h>
#include <stdlib.h>

#include "score.h"

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

    qsort(score_data_set, nmemb, sizeof(struct Score), Compare);
    found = bsearch(&key, score_data_set, nmemb, sizeof(struct Score), Compare);

    printf("found: %u %f\n", found->number, found->score);

    return 0;
}
