        program problem3
        implicit none
        integer*4 :: d,n,limit
        real :: check
        logical :: isprime

        do n=1,40,1
            if (isprime(n).eqv..true.) then
                print*,"Prime number!",n
            endif
        enddo

        end program

        logical function isprime (n)
            implicit none
            integer*4 :: n
            integer*4 :: k,c1,c2
            real :: limit
            ! Do a quick check for 2 or 3
            if ((mod(n,2).eq.0).or.(mod(n,3).eq.0)) then
                isprime=.false.
                return
            endif
            ! Check 6k +/- 1 up to limit=sqrt(n)
            limit = sqrt(real(n))
            k=1
            do while (k<limit)
                c1 = 6*k-1
                c2 = 6*k+1
                if ((mod(n,c1).eq.0).and.(c1.ne.n)) then
                    isprime=.false.
                    return
                endif
                if ((mod(n,c2).eq.0).and.(c2.ne.n)) then
                    isprime=.false.
                    return
                endif
                k = k+1
            enddo
            isprime=.true.
            return
        end function isprime
