
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SEED "_r <()<1-Z2[l5,^"
#define MAX_INPUT 256

void generate_key(const char *username)
{
    char result[sizeof(SEED)];
    size_t username_len = strlen(username);
    size_t seed_len = strlen(SEED);

    if (username_len < 4) {
        printf("Username must have at least 4 characters.\n");
        return;
    }

    strcpy(result, SEED);

    size_t max_len = username_len > seed_len
                   ? username_len : seed_len;

    for (size_t i = 0; i < max_len; i++) {
        unsigned char u =
            (unsigned char)username[i % username_len];

        unsigned char s =
            (unsigned char)result[i % seed_len];

        result[i % seed_len] =
            (char)(((u ^ s) % 25) + 0x41);
    }

    printf("Generated serial: ");

    for (size_t i = 0; i < strlen(result); i++) {
        if (i > 0 && i % 4 == 0)
            putchar('-');

        putchar(result[i]);
    }

    putchar('\n');
}

int main(void)
{
    char username[MAX_INPUT];

    printf("Username: ");

    if (fgets(username, sizeof(username), stdin) == NULL)
        return 1;

    username[strcspn(username, "\r\n")] = '\0';

    generate_key(username);

    printf("\nPress Enter to exit...");
    getchar();

    return 0;
}