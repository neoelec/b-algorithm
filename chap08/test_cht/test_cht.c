#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <container/cht.h>

struct CHT_Entry {
    struct DLL_Node node;
    const char *key;
    const char *value;
};

static size_t KeyHash(const struct CHT *table, const struct DLL_Node *node)
{
    const struct CHT_Entry *entry = CONTAINER_OF(node, struct CHT_Entry, node);
    size_t hash = 0;
    size_t i;

    for (i = 0; i < strlen(entry->key); i++)
        hash = (hash << 3) + entry->key[i];

    return hash % table->nr_buckets;
}

static int Compare(const struct DLL_Node *_a, const struct DLL_Node *_b)
{
    const struct CHT_Entry *a = CONTAINER_OF(_a, struct CHT_Entry, node);
    const struct CHT_Entry *b = CONTAINER_OF(_b, struct CHT_Entry, node);

    return strcmp(a->key, b->key);
}

static void CHT_InsertEntry(
    struct CHT *table, const char *key, const char *value)
{
    struct CHT_Entry *entry;

    entry = malloc(sizeof(*entry));
    entry->key = key;
    entry->value = value;

    CHT_Insert(table, &entry->node);
    if (entry->node.prev != entry->node.next)
        printf("Collision occured : Key(%s), Address(%zu)\n", key,
            table->KeyHash(table, &entry->node));
}

static const char *CHT_GetEntry(struct CHT *table, const char *key)
{
    struct CHT_Entry key_entry = {
        .key = key,
    };
    struct DLL_Node *node = CHT_Get(table, &key_entry.node, Compare);

    if (node != NULL) {
        struct CHT_Entry *entry = CONTAINER_OF(node, struct CHT_Entry, node);
        return entry->value;
    }

    return "NiL";
}

static void CHT_DestroyEntry(struct DLL_Node *node, void *private)
{
    struct CHT_Entry *entry = CONTAINER_OF(node, struct CHT_Entry, node);

    DLL_Remove(node);
    free(entry);
}

static struct CHT *CHT_CreateTable(size_t nr_buckets)
{
    struct CHT *table = malloc(CHT_BYTES(nr_buckets));

    CHT_Init(table, nr_buckets, KeyHash);

    return table;
}

static void CHT_DestroyTable(struct CHT *table)
{
    size_t i;

    for (i = 0; i < table->nr_buckets; i++) {
        struct DLL_Node *head = &table->bucket[i];
        while (head->next != head)
            CHT_DestroyEntry(head->next, NULL);
    }

    free(table);
}

int main(int argc, char *argv[])
{
    struct CHT *table = CHT_CreateTable(12289);

    CHT_InsertEntry(table, "MSFT", "Microsoft Corporation");
    CHT_InsertEntry(table, "JAVA", "Sun Microsystems");
    CHT_InsertEntry(table, "REDH", "Red Hat Linux");
    CHT_InsertEntry(table, "APAC", "Apache Org");
    CHT_InsertEntry(table, "ZYMZZ", "Unisys Ops Check"); /* APAC와 충돌 */
    CHT_InsertEntry(table, "IBM", "IBM Ltd.");
    CHT_InsertEntry(table, "ORCL", "Oracle Corporation");
    CHT_InsertEntry(table, "CSCO", "Cisco Systems, Inc.");
    CHT_InsertEntry(table, "GOOG", "Google Inc.");
    CHT_InsertEntry(table, "YHOO", "Yahoo! Inc.");
    CHT_InsertEntry(table, "NOVL", "Novell, Inc.");

    printf("\n");
    printf("Key:%-6s, Value:%s\n", "MSFT", CHT_GetEntry(table, "MSFT"));
    printf("Key:%-6s, Value:%s\n", "REDH", CHT_GetEntry(table, "REDH"));
    printf("Key:%-6s, Value:%s\n", "APAC", CHT_GetEntry(table, "APAC"));
    printf("Key:%-6s, Value:%s\n", "ZYMZZ", CHT_GetEntry(table, "ZYMZZ"));
    printf("Key:%-6s, Value:%s\n", "JAVA", CHT_GetEntry(table, "JAVA"));
    printf("Key:%-6s, Value:%s\n", "IBM", CHT_GetEntry(table, "IBM"));
    printf("Key:%-6s, Value:%s\n", "ORCL", CHT_GetEntry(table, "ORCL"));
    printf("Key:%-6s, Value:%s\n", "CSCO", CHT_GetEntry(table, "CSCO"));
    printf("Key:%-6s, Value:%s\n", "GOOG", CHT_GetEntry(table, "GOOG"));
    printf("Key:%-6s, Value:%s\n", "YHOO", CHT_GetEntry(table, "YHOO"));
    printf("Key:%-6s, Value:%s\n", "NOVL", CHT_GetEntry(table, "NOVL"));

    CHT_DestroyTable(table);

    return 0;
}
