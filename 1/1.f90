        program problem1
        integer :: total, n
        total = 0
        ! Loop to 999. If 1000, Fortran will include the last value.
        do n = 1, 999, 1
            if ((mod(n,3).eq.0).or.(mod(n,5).eq.0)) then
                total = total + n
            endif
        enddo
        print*, "total = ", total
        end program
