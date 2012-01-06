        program problem2
        implicit none
        integer :: a, b, c, total, m
        a = 1
        b = 2
        m = 4000000
        total = 0
        do while (b<m)
            if (mod(b,2).eq.0) then
                total = total + b
            endif
            c = b+a
            a=b
            b=c
        enddo
        print*, "total = ", total

        end program
