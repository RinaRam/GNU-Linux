#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s infile outfile\n", argv[0]);
        return 1;
    }

    char *infile = argv[1];
    char *outfile = argv[2];
    
    FILE *in = fopen(infile, "rb");
    if (in == NULL) {
        perror("Error opening infile");
        return 2;
    }

    FILE *out = fopen(outfile, "wb");
    if (out == NULL) {
        perror("Error opening outfile");
        fclose(in);
        return 3;
    }

    char buffer[1024];
    size_t n;
    while ((n = fread(buffer, 1, sizeof(buffer), in)) > 0) {
        if (fwrite(buffer, 1, n, out) != n) {
            perror("Error writing to outfile");
            fclose(in);
            fclose(out);
            return 4;
        }
    }
    
    if (ferror(in)) {
        perror("Error reading from infile");
        // fclose(in);
        fclose(out);
        return 5;
    }

    if (fclose(in) == EOF)
    {    
        perror("Error closing infile");
        remove(argv[2]);
        return 6;
    }

    if (fclose(out) == EOF)
    {
        perror("Error closing outfile");
        remove(argv[2]);
        return 7;
    }
    
    if (remove(infile) != 0) {
        perror("Error deleting infile");
        return 8;
    }

    return 0;
}
