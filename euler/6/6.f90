program problem6
implicit none
integer (kind=4) :: ssq,sqs,diff,i

ssq=0
sqs=0

do i=1,100,1
    ssq = ssq + (i**2)
    sqs = sqs + i
enddo
sqs=(sqs**2)

diff=sqs-ssq
print*,"Differece is ",diff

end program
