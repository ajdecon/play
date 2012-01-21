! Find the sum of all ``amicable numbers'' under 10,000.
! Amicable number defined as a pair where d(b)=a and d(a)=b,
! where d(x) is the sum of proper divisors of x.

program problem21
    implicit none
    integer :: d 
    if (d(220).eq.284) then
        print*,"d(x) seems to work!"
    else
        print*,"back to drawing board"
    endif
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
