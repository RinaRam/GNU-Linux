#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <rhash.h>
#include <ctype.h>
#include <sys/stat.h>


void calculate_and_print_hash(int hash_id, const unsigned char* input, size_t length, int output_as_hex) {
    unsigned char hash[64]; // Буфер достаточный для любого типа хеша
    char output[130];

    switch (hash_id) {
        case RHASH_MD5:
            rhash_msg(hash_id, input, length, hash);
            break;
        case RHASH_SHA1:
            rhash_msg(hash_id, input, length, hash);
            break;
        case RHASH_TTH:
            rhash_msg(hash_id, input, length, hash);
            break;
        default:
            fprintf(stderr, "Unsupported hash type\n");
            exit(1);
    }

    // Вывод хеша в нужном формате
    rhash_print_bytes(output, hash, rhash_get_digest_size(hash_id), output_as_hex ? RHPR_HEX : RHPR_BASE64);
    printf("%s\n", output);
}


int is_file(const char* path) {
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISREG(path_stat.st_mode);
}

int main(int argc, char* argv[]) {
    char *line = NULL;
    size_t len = 0;
    
    while (getline(&line, &len, stdin) != -1) {
        char *hash_type = strtok(line, " ");
        char *input = strtok(NULL, "\n");

        if (hash_type == NULL || input == NULL) {
            fprintf(stderr, "Invalid command\n");
            continue;
        }

        int hash_id = 0;

        // Определение типа хеша
        if (strcasecmp(hash_type, "MD5") == 0 || strcasecmp(hash_type, "md5") == 0) {
            hash_id = RHASH_MD5;
        } else if (strcasecmp(hash_type, "SHA1") == 0 || strcasecmp(hash_type, "sha1") == 0) {
            hash_id = RHASH_SHA1;
        } else if (strcasecmp(hash_type, "TTH") == 0 || strcasecmp(hash_type, "tth") == 0) {
            hash_id = RHASH_TTH;
        } else {
            fprintf(stderr, "Unknown hash type: %s\n", hash_type);
            continue;
        }

        int output_as_hex = isupper(hash_type[0]);

        if (input[0] == '"') {
            // Строка
            input++;
            calculate_and_print_hash(hash_id, (const unsigned char*)(input), strlen(input), output_as_hex);
        } else {
            // Файл
            FILE* file = fopen(input, "rb");
            if (!file) {
                perror("Failed to open file");
                continue;
            }
            fseek(file, 0, SEEK_END);
            long length = ftell(file);
            fseek(file, 0, SEEK_SET);
            unsigned char* buffer = (unsigned char*)malloc(length);
            if (!buffer) {
                fprintf(stderr, "Failed to allocate memory\n");
                fclose(file);
                continue;
            }
            fread(buffer, 1, length, file);
            fclose(file);

            calculate_and_print_hash(hash_id, buffer, length, output_as_hex);
            free(buffer);
        }

        free(line);
        line = NULL;
        len = 0;
    }

    return 0;
}
