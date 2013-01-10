        subroutine dsum(b, a, n)
        double precision a(n), b
        b = 0.0D0
        do 100 i=1,n
            b = b+a(i)
100     continue
        end
