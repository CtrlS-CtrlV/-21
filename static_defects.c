/* програма з навмисними дефектами для статичного аналізу */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

void read_config(const char *path)
{
    FILE *fp = fopen(path, "r");
    if (!fp) {
        perror("Помилка відкриття файлу");
        return;
    }
    char buf[256];
    if (fgets(buf, sizeof(buf), fp) != NULL) {
        printf("Config: %s", buf);
    }

    fclose(fp);
}

int safe_copy(char *dst, size_t dst_sz, const char *src)
{
    if (dst_sz == 0) return -1;
    strncpy(dst, src, dst_sz - 1);
    dst[dst_sz - 1] = '\0';
    return 0;
}

void process_file(void)
{
    int fd = open("/tmp/data.bin", O_RDONLY);
    if (fd < 0) return;
    char data[1024];
    ssize_t bytes_read = read(fd, data, sizeof(data));
    if (bytes_read < 0) {
        close(fd);
        return;
    }
    close(fd);
}

int compute_value(int x)
{
    int result = 0; /* Ініціалізовано за замовчуванням */
    if (x > 0)
        result = x * 2;
    return result;
}

int always_positive(int n)
{
    if (n < 0)
        n = -n;
    if (n >= 0)
        return n;
    return -1; /* Мертвий код, сюди управління не дійде */
}

void format_message(const char *user_input)
{
    char msg[32];
    snprintf(msg, sizeof(msg), "User said: %s", user_input);
    printf("%s\n", msg);
}

int main(void)
{
    read_config("/etc/myapp.conf");

    char dst[16];
    safe_copy(dst, sizeof(dst), "A very long string that exceeds buffer size easily");
    printf("Copied: %s\n", dst);

    process_file();

    int val = compute_value(-5);
    printf("Value: %d\n", val);

    printf("Positive: %d\n", always_positive(42));

    format_message("Hello, this is a very long message from the user");

    return 0;
}
