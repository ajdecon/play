        program problem3
        implicit none
        real :: check
        integer(kind=8) :: n,d
        logical :: isprime

        n = 600851475143_8
        print*,"n = ",n
        d=floor(sqrt(real(n)))
        if (mod(d,2).eq.0) then
            d = d-1
        endif
        do while (d>2)
            if (mod(n,d).eq.0) then
                print*,"n,d,div = ",n,d,n/real(d)
                if (isprime(real(d)).eqv..true.) then
                    print*, "largest prime factor = ",d
                    stop
                endif
            endif
            d = d-2
            if (mod(d,2000).eq.0) then
                print*,"d = ",d
            endif
        enddo

        end program

        logical function isprime (n)
            implicit none
            real :: n,k,c1,c2
            real :: limit
            ! Do a quick check for 2 or 3
            if ((mod(n,2.).eq.0).or.(mod(n,3.).eq.0)) then
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
