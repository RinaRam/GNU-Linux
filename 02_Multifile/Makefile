TRASH = *.o *.so *.a prog prog-a prog-so res* *~ o.*
PARAMETER_ONE = Alice
PARAMETERS_THREE = Mad Hatter Tweedles

all:	prog prog-a prog-so

test:	prog prog-a prog-so
	./prog > res 2> /dev/null
	./prog-a > res_a 2> /dev/null
	./prog-so > res_so 2> /dev/null
	./prog $(PARAMETER_ONE) > res_1
	./prog-a $(PARAMETER_ONE) > res_a_1
	./prog-so $(PARAMETER_ONE) > res_so_1
	./prog $(PARAMETERS_THREE) > res_3
	./prog-a $(PARAMETERS_THREE) > res_a_3
	./prog-so $(PARAMETER_ONE) > res_so_3
	cmp res res_a
	cmp res res_so
	cmp res_a res_so
	cmp res_1 res_a_1
	cmp res_1 res_so_1
	cmp res_a_1 res_so_1
	cmp res_3 res_a_3
	cmp res_3 res_so_3
	cmp res_a_3 res_so_3

prog:	const.o fun.o prog.o

prog-a:	prog.o liboutput_static.a
	cc -L. $< -loutput_static -o $@

prog-so:	prog.o liboutput.so
	cc -L. $< -loutput -o $@

liboutput_static.a:	const.o fun.o
	ar -rcs $@ $^

liboutput.so:	const.o fun.o
	ar -rcs $@ $^

fun.o:	outlib.h

clean:
	rm -f $(TRASH)
