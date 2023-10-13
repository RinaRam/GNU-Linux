#include <stdio.h>
#include <stdlib.h>

void ap_gen(long M, long N, long S) {
    for (long i = M; i < N; i += S) {
        printf("%ld\n", i);
    }
}

long str_to_long(char *num) {
	char *endptr;
	long X;
	X = strtol(num, &endptr, 10);
	if (*endptr != '\0') {
		fprintf(stderr, "Invalid argument: %s\n", num);
		return 1;
	}
	return X;
}

int main(int argc, char *argv[]) {
	long M = 0, N, S = 1;

    if (argc == 1) {
		printf("./range \t outputs help\n");
		printf("./range N \t outputs the sequence [0, 1, ... N-1] in a column\n");
		printf("./range M N \t outputs the sequence [M, M+1, ... N-1] in a column\n");
		printf("./range M N S \t outputs the sequence [M, M+S, M+2S, ... N-1] in a column\n");	
		return 0;			
	}
    else if (argc == 2) {
		N = str_to_long(argv[1]);
	}
    else if (argc >= 3) {
		M = str_to_long(argv[1]);
		N = str_to_long(argv[2]);
    }

    if (argc == 4) {
        S = str_to_long(argv[3]);
    }

	ap_gen(M, N, S);
	return 0; 
}