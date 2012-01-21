! Find the sum of all ``amicable numbers'' under 10,000.
! Amicable number defined as a pair where d(b)=a and d(a)=b,
! where d(x) is the sum of proper divisors of x.

program problem21
    implicit none
    integer :: d, maxnum, a, b, total
    parameter(maxnum = 9999)
    logical, dimension(maxnum) :: sieve
    
    ! Initialize sieve to true
    do a=1,maxnum,1
        sieve(a)=.true.
    enddo

    ! Loop through all numbers up to maxnum.
    ! For each number...
    !  1) Calculate a=d(i). p
    !  2) Calculate b=d(a)
    !  3a) 
    !  3b) else, both numbers are false.
    do a=1,maxnum,1
        ! Skip numbers we've already marked
        if (sieve(a).eqv..false.) then
            cycle
        endif
        ! Mark sieve as false if the numbers aren't amicable.
        b = d(a)
        if (d(b)/=a) then
            sieve(a)=.false.
            if (b<=maxnum) then
                sieve(b)=.false.
            endif
        endif
    enddo

    total = 0
    ! Sum all amicable numbers in the sieve
    do a=1,maxnum,1
        if (sieve(a).eqv..true.) then
            total = total + a
        endif
    enddo
    print*, "Total is",total
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
