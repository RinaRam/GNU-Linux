AM_CFLAGS = -O0

bin_PROGRAMS = rhasher

rhasher_SOURCES = rhasher.c

TESTS = sha1_test.sh md5_test.sh

sha1_test.sh:
	echo "test `echo -n test | sha1sum | sed 's/ .*//'` = `echo 'SHA1 "test' | ./rhasher`" > $@
	chmod +x $@

md5_test.sh:
	echo "test `echo -n test | md5sum | sed 's/ .*//'` = `echo 'MD5 "test' | ./rhasher`" > $@
	chmod +x $@

clean:
	git clean -fd