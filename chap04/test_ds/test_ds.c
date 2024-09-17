#include <stdio.h>

#include <container/ds.h>

struct DS_Entry {
    struct DS_Head node;
    int data;
};

int main(int argc, char *argv[])
{
    struct DS_Entry set0 = { .node = { NULL }, .data = 0 };
    struct DS_Entry set1 = { .node = { NULL }, .data = 1 };
    struct DS_Entry set2 = { .node = { NULL }, .data = 2 };
    struct DS_Entry set3 = { .node = { NULL }, .data = 3 };

    printf("set0 = set1 : %s\n",
        DS_Search(&set0.node) == DS_Search(&set1.node) ? "TRUE" : "FALSE");

    DS_Union(&set0.node, &set2.node);
    printf("set0 = set2 : %s\n",
        DS_Search(&set0.node) == DS_Search(&set2.node) ? "TRUE" : "FALSE");

    DS_Union(&set2.node, &set3.node);
    printf("set2 = set3 : %s\n",
        DS_Search(&set2.node) == DS_Search(&set3.node) ? "TRUE" : "FALSE");

    printf("set0 = set4 : %s\n",
        DS_Search(&set0.node) == DS_Search(&set3.node) ? "TRUE" : "FALSE");

    return 0;
}
