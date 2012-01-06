        program problem3
        implicit none
        integer :: x,m
        logical :: isprime
        print*, "Enter the maximum"
        read (*,*), m
        do x = 1,m,1
            if (isprime(x).eqv..false.) then
                print*,"not prime",x
            else
                print*,"prime",x
            endif
        enddo

        end program

        logical function isprime (n)
            implicit none
            integer :: n
            integer :: i,half
            half = n/2
            do i = 2, half, 1
                if (mod(n,i).eq.0) then
                    isprime = .false.
                    return
                endif
            enddo
            isprime = .true.
            return
        end function isprime
