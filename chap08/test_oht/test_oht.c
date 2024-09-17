#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <container/oht.h>

struct OHT_Container {
    struct OHT *table;
};

struct OHT_Entry {
    const char *key;
    const char *value;
};

static size_t KeyHash(const struct OHT *table, const void *_entry)
{
    const struct OHT_Entry *entry = _entry;
    size_t hash = 0;
    size_t i;

    for (i = 0; i < strlen(entry->key); i++)
        hash = (hash << 3) + entry->key[i];

    return hash % table->nr_buckets;
}

static size_t StepHash(const struct OHT *table, const void *_entry)
{
    const struct OHT_Entry *entry = _entry;
    size_t hash = 0;
    size_t i;

    for (i = 0; i < strlen(entry->key); i++)
        hash = (hash << 2) + entry->key[i];

    return (hash % (table->nr_buckets - 3)) + 1;
}

static int Compare(const void *_a, const void *_b)
{
    const struct OHT_Entry *a = _a;
    const struct OHT_Entry *b = _b;

    return (int)strcmp(a->key, b->key);
}

static void OHT_InsertEntry(
    struct OHT_Container *ht, const char *key, const char *value)
{
    struct OHT *table = ht->table;
    size_t nr_bucket = table->nr_buckets;
    struct OHT_Entry *entry = malloc(sizeof(*entry));

    entry->key = key;
    entry->value = value;

    table = OHT_Expand(table, 50);
    if (nr_bucket < table->nr_buckets)
        printf("\nRehashed. New table size is : %zu\n\n", table->nr_buckets);

    printf("Key(%-6s) ->\n", entry->key);
    OHT_Insert(table, entry);

    ht->table = table;
}

static const char *OHT_GetEntry(struct OHT_Container *ht, const char *key)
{
    struct OHT_Entry key_entry = {
        .key = key,
    };
    struct OHT_Entry *entry = OHT_Get(ht->table, &key_entry, Compare);

    if (entry != NULL)
        return entry->value;

    return "NiL";
}

static void OHT_DestroyEntry(struct OHT *table, void *entry)
{
    if (entry == NULL)
        return;

    OHT_Remove(table, entry);
    free(entry);
}

static struct OHT_Container *OHT_CreateTable(size_t nr_buckets)
{
    struct OHT_Container *ht = malloc(sizeof(*ht));
    struct OHT *table = malloc(OHT_BYTES(nr_buckets));

    OHT_Init(table, nr_buckets, KeyHash, StepHash);
    ht->table = table;

    return ht;
}

static void OHT_DestroyTable(struct OHT_Container *ht)
{
    struct OHT *table = ht->table;
    size_t i;

    for (i = 0; i < table->nr_buckets; i++)
        OHT_DestroyEntry(table, table->bucket[i]);

    free(table);
    free(ht);
}

int main(int argc, char *argv[])
{
    struct OHT_Container *ht = OHT_CreateTable(11);

    OHT_InsertEntry(ht, "MSFT", "Microsoft Corporation");
    OHT_InsertEntry(ht, "JAVA", "Sun Microsystems");
    OHT_InsertEntry(ht, "REDH", "Red Hat Linux");
    OHT_InsertEntry(ht, "APAC", "Apache Org");
    OHT_InsertEntry(ht, "ZYMZZ", "Unisys Ops Check"); /* APAC와 충돌 */
    OHT_InsertEntry(ht, "IBM", "IBM Ltd.");
    OHT_InsertEntry(ht, "ORCL", "Oracle Corporation");
    OHT_InsertEntry(ht, "CSCO", "Cisco Systems, Inc.");
    OHT_InsertEntry(ht, "GOOG", "Google Inc.");
    OHT_InsertEntry(ht, "YHOO", "Yahoo! Inc.");
    OHT_InsertEntry(ht, "NOVL", "Novell, Inc.");

    printf("\n");
    printf("Key:%-6s, Value:%s\n", "MSFT", OHT_GetEntry(ht, "MSFT"));
    printf("Key:%-6s, Value:%s\n", "REDH", OHT_GetEntry(ht, "REDH"));
    printf("Key:%-6s, Value:%s\n", "APAC", OHT_GetEntry(ht, "APAC"));
    printf("Key:%-6s, Value:%s\n", "ZYMZZ", OHT_GetEntry(ht, "ZYMZZ"));
    printf("Key:%-6s, Value:%s\n", "JAVA", OHT_GetEntry(ht, "JAVA"));
    printf("Key:%-6s, Value:%s\n", "IBM", OHT_GetEntry(ht, "IBM"));
    printf("Key:%-6s, Value:%s\n", "ORCL", OHT_GetEntry(ht, "ORCL"));
    printf("Key:%-6s, Value:%s\n", "CSCO", OHT_GetEntry(ht, "CSCO"));
    printf("Key:%-6s, Value:%s\n", "GOOG", OHT_GetEntry(ht, "GOOG"));
    printf("Key:%-6s, Value:%s\n", "YHOO", OHT_GetEntry(ht, "YHOO"));
    printf("Key:%-6s, Value:%s\n", "NOVL", OHT_GetEntry(ht, "NOVL"));

    OHT_DestroyTable(ht);

    return 0;
}
