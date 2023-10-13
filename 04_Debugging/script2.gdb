set pagination off
set $count = 0
b range.c:6 if $count++ >= 27 && $count <= 35
command 1
        p {M,N,S,i}
        cont
end

run -100 100 3 > /dev/null
quit
