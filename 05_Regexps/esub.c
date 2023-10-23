#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>


void print_error(const char* error_message) {
    printf("Error: %s\n", error_message);
}

int pocket_count(const char* str) {
    int pc = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '\\' && str[i+1] >= '0' && str[i+1] <= '9') {
            if ((str[i+1] - '0') > pc) {
                pc = (str[i+1] - '0');
            }
        }
    }

    return pc;
}

void esub(const char* regexp, const char* substitution, const char* string) {
    int clean_string_len = 0;

    for (int i = 0; string[i] != '\0'; i++, clean_string_len++) {
        if (string[i] == '\\' && string[i+1] == '\\') {
            i++; // пропустить следующий символ '\'
        }
    }

    char* clean_string = malloc(clean_string_len + 1);
    if (clean_string == NULL) {
        print_error("Failed to allocate memory");
        return;
    }

    for (int i = 0, j = 0; string[i] != '\0'; i++, j++) {
        if (string[i] == '\\' && string[i+1] == '\\') {
            clean_string[j] = '\\';
            i++; // пропустить следующий символ '\'
        } else {
            clean_string[j] = string[i];
        }
    }
    clean_string[clean_string_len] = '\0'; 

    regex_t regex;
    int pc = pocket_count(substitution);
    regmatch_t pmatch[pc + 1]; // Количество карманов

    // Компилируем регулярное выражение
    int ret = regcomp(&regex, regexp, REG_EXTENDED);
    if (ret != 0) {
        size_t max_error_msg_size = 256;
        char error_msg[max_error_msg_size];
        regerror(ret, &regex, error_msg, max_error_msg_size);
        print_error(error_msg);
        return;
    }

    // Ищем совпадение в строке
    ret = regexec(&regex, clean_string, pc + 1, pmatch, 0);
 
    if (ret == REG_NOMATCH) {
        printf("%s\n", clean_string);
        free(clean_string);
        regfree(&regex);
        return;
    } else if (ret != 0) {
        char error_message[100];
        regerror(ret, &regex, error_message, sizeof(error_message));
        print_error(error_message);
        free(clean_string);
        regfree(&regex);
        return;
    }

    for (int i = 0; i < pc + 1; i++) {
        if (pmatch[i].rm_so < 0) {
            print_error("Invalid capture group reference");
            free(clean_string);
            regfree(&regex);
            return;
        }
    }

    int res_len = pmatch[0].rm_so + 1;

    for (int i = 0; substitution[i] != '\0'; i++) {
        if (substitution[i] == '\\') {
            if (substitution[i+1] >= '0' && substitution[i+1] <= '9') {
                res_len += pmatch[(substitution[i+1] - '0')].rm_eo - pmatch[(substitution[i+1] - '0')].rm_so;
                i++;
            }
            else if (substitution[i+1] == '\\') {
                i++;
                res_len++;
            }
            else if (substitution[i+1] == 'n') {
                i++;
                res_len++;
            }
            
        }
        else {
            res_len++;
        }
    }

    res_len += clean_string_len - pmatch[0].rm_eo;

    char* result = malloc(res_len + 1);
    if (result == NULL) {
        print_error("Failed to allocate memory");
        free(clean_string);
        regfree(&regex);
        return;
    }
    strncpy(result, clean_string, pmatch[0].rm_so);
    int offset = pmatch[0].rm_so;

    for (int i = 0; substitution[i] != '\0'; i++) {
        if (substitution[i] == '\\') {
            if (substitution[i+1] >= '0' && substitution[i+1] <= '9') {
                strncpy(result + offset, clean_string + pmatch[(substitution[i+1] - '0')].rm_so, pmatch[(substitution[i+1] - '0')].rm_eo - pmatch[(substitution[i+1] - '0')].rm_so);
                offset += pmatch[(substitution[i+1] - '0')].rm_eo - pmatch[(substitution[i+1] - '0')].rm_so;
                i++;
            }
            else if (substitution[i+1] == '\\') {
                result[offset++] = '\\';
                i++;
            }
            else if (substitution[i+1] == 'n') {
                result[offset++] = '\n';
                i++;
            }
            
        }
        else {
            result[offset++] = substitution[i];
        }
    }



    // printf("%s\n", result);
    // printf("%s\n", clean_string + pmatch[0].rm_eo);
    // printf("%d %d\n", clean_string_len, pmatch[0].rm_eo);



    strncpy(result + offset, clean_string + pmatch[0].rm_eo, clean_string_len - pmatch[0].rm_eo);
    result[res_len] = '\0'; 

    // Выводим результирующую строку
    printf("%s\n", result);

    // Освобождаем память и никогда не забываем это делать!
    free(result);
    free(clean_string);
    regfree(&regex);
}

int main(int argc, char *argv[]) {
    if (argc < 4) {
        print_error("Not enough arguments");
        return 1;
    }

    esub(argv[1], argv[2], argv[3]);

    return 0;
}
