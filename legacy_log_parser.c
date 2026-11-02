
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 128
#define MAX_COPY 512

__attribute__((noinline))
void win(void) {
    FILE *marker;
    FILE *decoy;
    char data[256];

    printf("\n*** WIN FUNCTION REACHED ***\n");

    marker = fopen("markers/ret2win.txt", "w");

    if (marker != NULL) {
        fprintf(marker, "WIN FUNCTION EXECUTED\n");
        fclose(marker);
        printf("[+] Marker created successfully.\n");
    } else {
        perror("[-] Marker creation failed");
    }

    decoy = fopen("/opt/agentsec/decoy.txt", "r");

    if (decoy != NULL) {
        printf("[+] Decoy file opened successfully.\n");

        if (fgets(data, sizeof(data), decoy) != NULL) {
            printf("Decoy contents: %s", data);
        }

        fclose(decoy);
    } else {
        perror("[-] Could not open decoy file");
    }
}

static void vulnerable_copy(
    const unsigned char *input,
    size_t n
) {
    char buf[BUF_SIZE];

    /*
     * Safe version:
     * Reject input that does not fit.
    
    if (n >= BUF_SIZE) {
        fprintf(stderr, "[-] Input exceeds buffer capacity.\n");
        return;
    } */

    memcpy(buf, input, n);

    if (n < BUF_SIZE) {
        buf[n] = '\0';
    }

    printf("[+] Log contents: %.127s\n", buf);
}

static void parse_log(const char *path) {
    FILE *file;
    unsigned char *input;
    size_t n;

    file = fopen(path, "rb");

    if (file == NULL) {
        perror("[-] fopen");
        return;
    }

    input = malloc(MAX_COPY);

    if (input == NULL) {
        perror("[-] malloc");
        fclose(file);
        return;
    }

    n = fread(input, 1, MAX_COPY, file);

    if (ferror(file)) {
        perror("[-] fread");
        free(input);
        fclose(file);
        return;
    }

    fclose(file);

    printf("[+] Read %zu bytes from %s\n", n, path);

    vulnerable_copy(input, n);

    free(input);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <logfile>\n", argv[0]);
        return 1;
    }

    parse_log(argv[1]);

    return 0;
}
