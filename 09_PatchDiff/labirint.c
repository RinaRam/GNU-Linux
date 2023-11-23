#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void path_generation(int size, char (*maze)[size], int (*visited)[size], int *row, int *col, int *visited_cnt, int *step, int rooms_count, char path) {
        char directions[] = {'W', 'S', 'E', 'N'};
        int direct = rand() % 4;
        char direction = directions[direct];
        int row_step = (direction == 'N') - (direction == 'S'), col_step = (direction == 'E') - (direction == 'W');
        int n_row = *row + row_step * 2;
        int n_col = *col + col_step * 2;
        int empty_neighbours = 2;
        while (*visited_cnt < (rooms_count * rooms_count) && empty_neighbours > 0) {
            if (n_row > 0 && n_row < (size - 1) && n_col > 0 && n_col < (size - 1) && visited[n_row][n_col] == 0) {
                maze[*row + row_step][*col + col_step] = path;
                maze[n_row][n_col] = path;
                *row = n_row;
                *col = n_col;
                ++*visited_cnt;
                visited[*row][*col] = ++*step;
                direct = rand() % 4;
                direction = directions[direct];
                row_step = (direction == 'N') - (direction == 'S');
                col_step = (direction == 'E') - (direction == 'W');
                n_row = *row + row_step * 2;
                n_col = *col + col_step * 2;
                empty_neighbours = 0;
                if (*row + 2 < size) {
                    empty_neighbours += (visited[*row + 2][*col] == 0);
                }
                if (*col + 2 < size) {
                    empty_neighbours += (visited[*row][*col + 2] == 0);
                }
                if (*row - 2 > 0) {
                    empty_neighbours += (visited[*row - 2][*col] == 0);
                }
                if (*col - 2 > 0) {
                    empty_neighbours += (visited[*row][*col - 2] == 0);
                }
            }
            else {
                direction = directions[++direct % 4];
                row_step = (direction == 'N') - (direction == 'S');
                col_step = (direction == 'E') - (direction == 'W');
                n_row = *row + row_step * 2;
                n_col = *col + col_step * 2;
            }
        }
    }

void searching_for_empty_neighbour(int size, int (*visited)[size], int *row, int *col, int *step) {
        int empty_neighbours = 0;
        while (empty_neighbours == 0) {
            --*step;
            if ((*row + 2 < size) && visited[*row + 2][*col] == *step) {
                *row += 2;
            }
            if ((*row - 2 > 0) && visited[*row - 2][*col] == *step) {
                *row -= 2;
            }
            if ((*col + 2 < size) && visited[*row][*col + 2] == *step) {
                *col += 2;
            }
            if ((*col - 2 > 0) && visited[*row][*col - 2] == *step) {
                *col -= 2;
            }
            empty_neighbours = 0;
            if (*row + 2 < size) {
                empty_neighbours += (visited[*row + 2][*col] == 0);
            }
            if (*col + 2 < size) {
                empty_neighbours += (visited[*row][*col + 2] == 0);
            }
            if (*row - 2 > 0) {
                empty_neighbours += (visited[*row - 2][*col] == 0);
            }
            if (*col - 2 > 0) {
                empty_neighbours += (visited[*row][*col - 2] == 0);
            }
        }
    }


int main(int argc, char *argv[]) {
    int rooms_count = 6, size = rooms_count * 2 + 1; 

    char path = '.', wall = '#'; 

    // Initialize the maze with walls
    char maze[size][size];
    int visited[size][size];
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i % 2 == 1 && j % 2 == 1) {
                maze[i][j] = path;
            }
            else {
                maze[i][j] = wall;
            }
            visited[i][j] = 0;
        }
    }

    // Generate the maze
    srand(time(NULL));
    int row = 1;
    int col = 1;

    maze[row][col] = path;
    int visited_cnt = 1;
    visited[row][col] = 1;
    int step = 1;

    while (visited_cnt < (rooms_count * rooms_count)) {
        path_generation(size, maze, visited, &row, &col, &visited_cnt, &step, rooms_count, path);   
        if (visited_cnt < (rooms_count * rooms_count)) {
            searching_for_empty_neighbour(size, visited, &row, &col, &step);
        }
    }
    

    // Print the maze
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%c", maze[i][j]);
        }
        printf("\n");
    }

    return 0;
}
