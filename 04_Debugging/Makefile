TRASH = range res*

all:	test

test:	range
	gdb -x script1.gdb ./range --batch --quiet | grep -o '{.*}' > res_1.txt
	gdb -x script2.gdb ./range --batch --quiet | grep -o '{.*}' > res_2.txt
	cmp res_1.txt benchmark_1.txt
	cmp res_2.txt benchmark_2.txt

range:	range.c
	cc -O0 -g $< -o $@

clean:
	rm -f $(TRASH)
