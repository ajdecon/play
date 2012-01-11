! Sieve of Eratosthenes
program problem7
implicit none
integer (kind=8) :: num
parameter (num = 2000000)
logical, dimension(num) :: sieve
integer (kind=8) :: c,i,j,total

! Initialize sieve to true
do i=1,num,1
    sieve(i) = .true.
enddo

! 1 isn't prime
sieve(1) = .false.

! Neither are multiples of 2
do i=4,num,2
    sieve(i) = .false.
enddo

! Cycle through possible primes, mark their multiples as non-prime
do i=3,num,2
    ! Already marked? skip it
    if (sieve(i).eqv..false.) then
        cycle
    endif

    ! Mark multiples as non-prime
    do j=2*i,num,i
        sieve(j) = .false.
    enddo

enddo

! sum all primes
total = 0
do i=1,num,1
    if (sieve(i).eqv..true.) then
        total = total + i
    endif
enddo

print*,"Total of primes below 2,000,000 is ",total

end program

