! Find the sum of all ``amicable numbers'' under 10,000.
! Amicable number defined as a pair where d(b)=a and d(a)=b,
! where d(x) is the sum of proper divisors of x.

program problem21
    implicit none
    integer :: d, maxnum, a, b, total
    integer :: ct,cf
    parameter(maxnum = 9999)
    logical, dimension(maxnum) :: sieve
    
    ! Initialize sieve to false
    do a=1,maxnum,1
        sieve(a)=.false.
    enddo

    ! Loop through all numbers up to maxnum.
    ! For each number...
    !  1) Calculate a=d(i). p
    !  2) Calculate b=d(a)
    !  3a) 
    !  3b) else, both numbers are false.
    do a=1,maxnum,1
        ! Skip numbers we've already marked
        if (sieve(a).eqv..true.) then
            cycle
        endif
        b=d(a)
        if (d(b)==a .and. b/=a) then
            sieve(a)=.true.
            if (b<=maxnum) then
                sieve(b)=.true.
            endif
        endif
    enddo

    total = 0
    ct = 0
    cf = 0
    ! Sum all amicable numbers in the sieve
    do a=1,maxnum,1
        if (sieve(a).eqv..true.) then
            total = total + a
            ct= ct+1
        else
            cf = cf+1
        endif
    enddo
    print*, "Total is",total
    print*,"Number of amicable numbers",ct
    print*,"Not amicable?",cf
end program

! Find the number of proper divisors of x
function d(x)
    implicit none
    integer :: d,x,s,i
    s = 0
    do i=1,(x-1),1
        if (mod(x,i).eq.0) then
            s = s + i
        endif
    enddo
    d = s
    return
end function 
