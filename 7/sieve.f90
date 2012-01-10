! Sieve of Eratosthenes
program problem7
implicit none
integer (kind=4) :: num
parameter (num = 105000)
logical, dimension(num) :: sieve
integer (kind=4) :: c,i,j

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
    if (sieve(i).eqv..false.) then
        cycle
    endif

    do j=2*i,num,i
        sieve(j) = .false.
    enddo

enddo

! count primes
c = 0
do i=1,num,1
    if (sieve(i).eqv..true.) then
        c = c+1
        print*, "prime ",c," at ",i
    endif
enddo

print*,"Number of primes is ",c

end program

