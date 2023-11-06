#!/bin/bash

test_rhasher() {
    echo -n $1 | $2 $3 | tr -d '\n'
}

test_sum() {
    echo -n $1 | $2 | cut -d ' ' -f1
}

INPUT="teststring"
RHASHER=./rhasher_test

MD5_RESULT=$(test_rhasher "$INPUT" "$RHASHER" "MD5")
MD5_SUM=$(test_sum "$INPUT" "md5sum")

SHA1_RESULT=$(test_rhasher "$INPUT" "$RHASHER" "SHA1")
SHA1_SUM=$(test_sum "$INPUT" "sha1sum")

if [ "$MD5_RESULT" != "$MD5_SUM" ]; then
    echo "MD5 test failed"
    exit 1
fi

if [ "$SHA1_RESULT" != "$SHA1_SUM" ]; then
    echo "SHA1 test failed"
    exit 1
fi

echo "All tests passed"
exit 0