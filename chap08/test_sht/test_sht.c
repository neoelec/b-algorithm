#include <stdio.h>
#include <stdlib.h>

#include <container/sht.h>

struct SHT_Container {
    struct SHT *table;
};

struct SHT_Entry {
    size_t key;
    int value;
};

static size_t KeyHash(const struct SHT *table, const void *_entry)
{
    const struct SHT_Entry *entry = _entry;

    return entry->key % table->nr_buckets;
}

static void SHT_InsertEntry(struct SHT_Container *ht, size_t key, int value)
{
    struct SHT *table = ht->table;
    struct SHT_Entry *entry;

    entry = malloc(sizeof(*entry));
    entry->key = key;
    entry->value = value;

    SHT_Insert(table, entry);
}

static int SHT_GetEntry(struct SHT_Container *ht, size_t key)
{
    struct SHT_Entry key_entry = {
        .key = key,
    };
    struct SHT_Entry *entry = SHT_Get(ht->table, &key_entry);

    if (entry != NULL)
        return entry->value;

    return 0;
}

static void SHT_DestroyEntry(struct SHT *table, void *entry)
{
    if (entry == NULL)
        return;

    SHT_Remove(table, entry);
    free(entry);
}

static struct SHT_Container *SHT_CreateTable(size_t nr_buckets)
{
    struct SHT_Container *ht;
    struct SHT *table;

    table = malloc(SHT_BYTES(nr_buckets));
    SHT_Init(table, nr_buckets, KeyHash);

    ht = malloc(sizeof(*ht));
    ht->table = table;

    return ht;
}

static void SHT_DestroyTable(struct SHT_Container *ht)
{
    struct SHT *table = ht->table;
    size_t i;

    for (i = 0; i < table->nr_buckets; i++)
        SHT_DestroyEntry(table, table->bucket[i]);

    free(table);
    free(ht);
}

int main(int argc, char *argv[])
{
    struct SHT_Container *ht = SHT_CreateTable(193);

    SHT_InsertEntry(ht, 418, 32114);
    SHT_InsertEntry(ht, 9, 514);
    SHT_InsertEntry(ht, 27, 8917);
    SHT_InsertEntry(ht, 1031, 286);

    printf("Key:%-5d, Value:%d\n", 418, SHT_GetEntry(ht, 418));
    printf("Key:%-5d, Value:%d\n", 9, SHT_GetEntry(ht, 9));
    printf("Key:%-5d, Value:%d\n", 27, SHT_GetEntry(ht, 27));
    printf("Key:%-5d, Value:%d\n", 1031, SHT_GetEntry(ht, 1031));

    SHT_DestroyTable(ht);

    return 0;
}
