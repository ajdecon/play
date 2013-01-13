program problem14

integer (kind=8) :: do_seq,x,mchain,mstart,chain,junk
mchain=0
mstart=0

do x=2,999999
    chain=do_seq(x)
    if (chain>mchain) then
        mchain=chain
        mstart=x
    endif
    if (mod(x,10000).eq.0) then
        print*,"Currently on x = ",x,"max length is",mchain,"with start",mstart
    endif
enddo

print*,"Max chain length ",mchain,"starts at ",mstart

end program

function do_seq(n)
    integer (kind=8) :: do_seq,x,n,c,j
    x=n
    c=0
    do while (x.ne.1)
        c=c+1
        if (mod(x,2).eq.0) then
            x=x/2
        else
            x=(3*x)+1
        endif
        if (c>10000) then
            print*,"Seems to be stuck on ",n
            read*,j
        endif
    enddo
    do_seq=c
    return 
end function
