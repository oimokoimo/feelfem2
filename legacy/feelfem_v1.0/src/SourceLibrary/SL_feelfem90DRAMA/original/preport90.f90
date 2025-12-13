module preport90


! F90,F95/MPI module to make a report

double precision  , private :: t1,tim,tdiff,total,terapse
integer, private :: outputLevel

integer, private,parameter :: iunit = 8


private  title
private  drawline
private  calctime

contains

subroutine preport90init( output_level )
implicit none
include 'mpif.h'

integer , intent(in)  :: output_level  ! output level


outputLevel = output_level  ! 0 no output
                            ! 1 minimum output
                            ! 2 medium
                            ! 3 maximum

if(outputLevel < 0 .or. outputLevel > 3) then
  write(*,*) 'Argument for preport90init invalid. (set to 1)'
  outputLevel = 1
endif

tim         = MPI_WTIME()
tdiff       = MPI_WTIME()
tdiff       = tdiff - tim

tim         = MPI_WTIME()
total       = 0.0d0


if( outputLevel == 0 ) return

open(iunit,file='preport.txt',action='write')

  call drawline
  call title
  call drawline


end subroutine preport90init

!---------------------------------------
subroutine calctime
implicit none
include 'mpif.h'
t1      = MPI_WTIME()
terapse = t1 - tim - tdiff
total   = total+terapse
tim     = t1
end subroutine calctime
!---------------------------------------

subroutine preport(cha)
character*(*) cha

call calctime

if( outputLevel == 0 ) return

write(iunit,'(f9.4,f9.4,2x,a)') total,terapse,cha

if( outputLevel == 3 )then
write(*,'(f9.4,f9.4,2x,a)') total,terapse,cha
endif

end subroutine preport
subroutine preportmodule(cha)
character*(*) cha

call calctime

if( outputLevel == 0 ) return

write(iunit,'(f9.4,f9.4,2x,a)') total,terapse,cha

if( outputLevel == 3 )then
write(*,'(f9.4,f9.4,2x,a)') total,terapse,cha
endif

end subroutine preportmodule


subroutine preport90FundamentalVars(ndim,npmax,nedat,nnset,nnum,nip)
integer, intent(in)  :: ndim,npmax,nedat,nnset,nnum,nip 

if(outputLevel == 0) return


write(iunit,9000)
write(iunit,9001) ndim
write(iunit,9002) npmax
write(iunit,9003) nedat
write(iunit,9004) nnset
write(iunit,9005) nnum 
write(iunit,9006) nip
write(iunit,9000)

if(outputLevel == 3 ) then
  write(*,9000)
  write(*,9001) ndim
  write(*,9002) npmax
  write(*,9003) nedat
  write(*,9004) nnset
  write(*,9005) nnum 
  write(*,9006) nip
  write(*,9000)
endif
9000 format('                    ----------------------------------')
9001 format('                    ','Space dimension          :',i8)
9002 format('                    ','Total number of nodes    :',i8)
9003 format('                    ','Number of EDAT data sets :',i8)
9004 format('                    ','Number of NSET data sets :',i8)
9005 format('                    ','Number of NNUM data sets :',i8)
9006 format('                    ','Number of IP points      :',i8)

end subroutine preport90FundamentalVars

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
! Frequently used routines
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
subroutine drawline
  if(outputLevel == 3) then
    write(*,*)  '-------------------------------------------------------------'
  endif
  write(iunit,*)'-------------------------------------------------------------'
end subroutine drawline 

subroutine title 
  if(outputLevel == 3) then
    write(*,*)   ' feelfem90 Program'
  endif
  write(iunit,*) ' feelfem90 Program'
end subroutine title 
  
!---------------------------------------------------------
end module preport90
