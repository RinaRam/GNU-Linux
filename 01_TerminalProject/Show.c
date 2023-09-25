#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

#define DX 3

typedef struct LineNode {
    char *line;
    struct LineNode *next;
} LineNode;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    LineNode *head = NULL, *tail = NULL;
    char *line = NULL;
    size_t len = 0;
    size_t read;
    while ((read = getline(&line, &len, file)) != -1) {
        LineNode *node = malloc(sizeof(LineNode));
        node->line = strdup(line);
        node->next = NULL;

        if (!head) head = tail = node;
        else {
            tail->next = node;
            tail = node;
        }
    }
    free(line);
    fclose(file);

    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);

    WINDOW *win = newwin(LINES - 2*DX, COLS - 2*DX, DX, DX);
    keypad(win, TRUE);
    scrollok(win, TRUE);
    box(win, 0, 0);
    
    LineNode *current = head;
    int ch;
    int space_count = 0; // счетчик нажатий пробела
    while ((ch = wgetch(win)) != 27) {
        werase(win);
        box(win, 0, 0);
        mvwprintw(win, 0, 1, "%s", argv[1]);

        LineNode *temp = current;
        for (int i = 1; i < LINES - DX * 2 && temp; i++, temp = temp->next) {
            mvwprintw(win, i, 1, "%.*s", COLS - DX * 2 - 2, temp->line);
        }

        if (ch == ' ') space_count++;
        if (space_count == 3 && temp) { // Переместите строку вниз на каждое третье нажатие пробела
            current = temp;
            space_count = 0;
        }

        wrefresh(win);
    }

    LineNode *temp = head;
    while (temp) {
        LineNode *next = temp->next;
        free(temp->line);
        free(temp);
        temp = next;
    }

    delwin(win);
    endwin();
    return EXIT_SUCCESS;
}