/*  програма після виправлення clang-tidy */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void unsafe_operations(void)
{
    char buf[64];
    snprintf(buf, sizeof(buf), "value = %d, name = %s", 42, "test");
    printf("%s\n", buf);

    const char *maybe_null = getenv("MY_VAR");
    if (maybe_null != NULL) {
        size_t len = strlen(maybe_null);
        printf("Length: %zu\n", len);
    }

    int *arr = malloc(10 * sizeof(int));
    if (arr == NULL) {
        return;
    }
    for (int i = 0; i < 10; i++)
        arr[i] = i;
    printf("arr[5] = %d\n", arr[5]);
    free(arr);
}

void redundant_code(int x)
{
    if (x > 0)
        printf("Positive\n");

    int result = x * 2 + 1;
    printf("Result: %d\n", result);
}

int main(void)
{
    unsafe_operations();
    redundant_code(10);
    return 0;
}
