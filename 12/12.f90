program problem12
    integer (kind=8) :: triangle,numfactors
    integer (kind=8) :: NF,i,test,t,best
    ! Generate triangle numbers and print how many factors they have
    NF = 500
    test = 0
    i = 1
    do while (test<NF)
        t = triangle(i)
        i = i+1
        test = numfactors(t)
        if (test>best) then
            best = test
            print*,"Triangle",t,"factors",test
        endif
    enddo
end program

function triangle(n)
    integer (kind=8) :: triangle
    integer (kind=8) :: n,i,total
    total = 0
    do i=1,n,1
        total = total + i
    enddo
    triangle = total
    return
end function triangle

function numfactors(n)
    integer (kind=8) :: numfactors
    integer (kind=8) :: n,i,c
    c=0
    do i=1,floor(sqrt(real(n))),1
        if (mod(n,i).eq.0) then
            c=c+2
        endif
    enddo
    numfactors = c
    return
end function numfactors
