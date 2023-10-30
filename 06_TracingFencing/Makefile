CC = cc
CFLAGS = -Wall -Wextra -pedantic
TARGET = move
TRASH = move res* benchmark* output* *.so
CHECK_EXIT_CODE = tail -n1 res.txt | grep -Eo '[0-9]{1,4}' > exit_code.txt; rm res.txt; diff test_exit_code.txt exit_code.txt; rm test_exit_code.txt exit_code.txt
COMPARE = diff benchmark.txt res_input_file.txt; rm benchmark.txt res_input_file.txt

all:	move lib_remove.so

$(TARGET):	move.c
	$(CC) $(CFLAGS) $< -o $@

lib_remove.so:	protectfile.c
	$(CC) -shared -fPIC -o $@ $< -ldl

.PHONY:	all_tests
all_tests:	testPass testMissing testFailOpen testFailRead testFailClose

protect_test:	move lib_remove.so
	LD_PRELOAD=$(shell pwd)/lib_remove.so ./move preload_PROTECT_test.txt output.txt
	find ./ preload_PROTECT_test.txt
	cmp preload_PROTECT_test.txt output.txt

testPass:	move
	echo "Delete Me" > input.txt
	strace ./move input.txt output.txt 2> res.txt 
	echo 0 > test_exit_code.txt; $(CHECK_EXIT_CODE)
	echo "find: ‘input.txt’: No such file or directory" 2> benchmark.txt
	find input.txt > res_input_file.txt; $(COMPARE)
	rm output.txt

testMissing:	move
	echo "Won't Delete Me" > output_test_2.txt
	-strace ./move output_test_2.txt 2> res.txt
	echo 1 > test_exit_code.txt; $(CHECK_EXIT_CODE)
	echo "output_test_2.txt" > benchmark.txt 
	find output_test_2.txt > res_input_file.txt; $(COMPARE)
	echo "find: ‘output.txt’: No such file or directory" 2> benchmark.txt 
	find output.txt > res_input_file.txt; $(COMPARE)
	rm output_test_2.txt

testFailOpen: move
	echo "Won't Delete Me" > output_test_3.txt
	-strace -P output.txt -eopenat -efault=openat:error=EPERM ./move output_test_3.txt output.txt 2> res.txt 
	echo 3 > test_exit_code.txt; $(CHECK_EXIT_CODE)
	
	echo "output_test_3.txt" > benchmark.txt 
	find output_test_3.txt > res_input_file.txt; $(DIFF)
	
	echo "find: ‘output.txt’: No such file or directory" > benchmark.txt
	find output.txt 2> res_input_file.txt; $(DIFF)
	rm output_test_3.txt

testFailRead: move
	echo "Won't Delete Me" > output_test_4.txt
	-strace -P output_test_4.txt -eread -efault=read:error=EPERM ./move output_test_4.txt output.txt 2> res.txt 
	echo 5 > test_exit_code.txt ; $(FIND_RESULT_CODE)

	echo "output_test_4.txt" > benchmark.txt
	find output_test_4.txt > res_input_file.txt; $(DIFF)
	
	echo "find: output.txt’: No such file or directory" > benchmark.txt 
	find output.txt 2> res_input_file.txt; $(DIFF)
	rm output_test_4.txt

testFailClose: move
	echo "Won't Delete Me" > output_test_5.txt
	-strace -eclose -efault=close:error=EPERM:when=4 ./move output_test_5.txt output.txt 2> res.txt 
	echo 7 > test_exit_code.txt ; $(FIND_RESULT_CODE)

	echo "output_test_5.txt" > benchmark.txt
	find output_test_5.txt > res_input_file.txt; $(DIFF)
	
	echo "find: output.txt’: No such file or directory" > benchmark.txt 
	find output.txt 2> res_input_file.txt; $(DIFF)
	rm output_test_5.txt

clean:
	rm -f $(TRASH)
	