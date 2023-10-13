set pagination off
b range.c:6 if i % 5 == 0
command 1
        p {M,N,S,i}
        cont
end

run 1 12 > /dev/null
quit
