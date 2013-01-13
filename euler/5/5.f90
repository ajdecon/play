program problem5
implicit none

integer (kind=4) :: x
logical :: check
x = 20*19
do while (check(x).eqv..false.)
    x=x+20
enddo
print*,"Final answer is",x

end program

logical function check (n)
  implicit none
  integer (kind=4) :: n,d
  do d=1,20,1
      if (mod(n,d).ne.0) then
          check = .false.
          return
      endif
  enddo
  check = .true.
  return
end function check

