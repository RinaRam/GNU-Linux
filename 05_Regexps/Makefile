CC = cc
CFLAGS = -Wall -Wextra -pedantic
TARGET = esub
TRASH = esub res* benchmark*

all:	test

test:	$(TARGET)
	./esub 'regexp' 'substitution' 'string' > res_0
	echo 'string' | sed -E 's/regexp/substitution/' > benchmark_0

	./esub 'a test' 'another test' 'This is a test' > res_1
	echo "This is a test" | sed 's/a test/another test/' > benchmark_1

	./esub '(ic)(.*)(i)(.*)(land\s)(.*)([0-9])' '\7\2\_\\\|\/_ \3\s ~~wav\3ng~~\ s\7 \6unny \nP.S. \0' 'Alice in Wonderland f0rever' > res_2
	echo 'Alice in Wonderland f0rever' | sed -E 's/(ic)(.*)(i)(.*)(land\s)(.*)([0-9])/\7\2\_\\\|\/_ \3\s ~~wav\3ng~~\ s\7 \6unny \nP.S. \0/' > benchmark_2

	./esub '(ic)(.*)(i)(.*)(land\s)(.*)([0-9])' '\7\2\_\\\|\/_ \3\s ~~wav\3ng~~\ s\8 \6unny \nP.S. \0' 'Alice in Wonderland f0rever' > res_3
	echo 'Error: Invalid capture group reference' > benchmark_3

	diff res_0 benchmark_0
	diff res_1 benchmark_1
	diff res_2 benchmark_2
	diff res_3 benchmark_3

$(TARGET):	esub.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(TRASH)
