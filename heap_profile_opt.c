/* оптимізована версія для Valgrind Massif */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define NUM_RECORDS  1000

typedef struct {
    char   name[64];
    char  *description;
    double values[128];
} Record;

Record **load_records(int count)
{
    Record **records = malloc(count * sizeof(Record *));
    if (!records) return NULL;

    for (int i = 0; i < count; i++) {
        records[i] = malloc(sizeof(Record));
        if (!records[i]) return records;
        snprintf(records[i]->name, 64, "Record_%04d", i);
        

        char temp_desc[256];
        int len = snprintf(temp_desc, sizeof(temp_desc), "Description for record %d with lots of details", i);
        records[i]->description = malloc(len + 1);
        if (records[i]->description)
            strcpy(records[i]->description, temp_desc);

        for (int j = 0; j < 128; j++)
            records[i]->values[j] = (double)i * j;
    }
    return records;
}

void process_records(Record **records, int count)
{

    char *temp_buffer = malloc(count * 64);
    if (!temp_buffer) return;

    for (int i = 0; i < count; i++) {
        snprintf(temp_buffer + i * 64, 64, "Processed: %s", records[i]->name);
    }
    printf("Оброблено %d записів\n", count);
    free(temp_buffer);
}

void free_records(Record **records, int count)
{
    for (int i = 0; i < count; i++) {
        if (records[i]) {
            free(records[i]->description);
            free(records[i]);
        }
    }
    free(records);
}

int main(void)
{
    printf("Фаза 1: Завантаження %d записів (оптимізовано)...\n", NUM_RECORDS);
    Record **records = load_records(NUM_RECORDS);
    if (!records) { fprintf(stderr, "Помилка алокації\n"); return 1; }

    printf("Фаза 2: Обробка записів...\n");
    process_records(records, NUM_RECORDS);

    printf("Фаза 3: Звільнення пам'яті...\n");
    free_records(records, NUM_RECORDS);

    printf("Завершено.\n");
    return 0;
}
