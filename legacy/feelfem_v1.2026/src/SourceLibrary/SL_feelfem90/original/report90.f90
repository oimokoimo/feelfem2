module report90


! F90,F95 module to make a report
! use system_clock to count time

double precision  , private :: t1,tim,total,terapse
integer           , private :: clock_tim,clock_2,clock_3
integer, private :: outputLevel

integer, private,parameter :: iunit = 8


private  title
private  drawline
private  calctime

contains

subroutine report90init( output_level )
implicit none

integer , intent(in)  :: output_level  ! output level


outputLevel = output_level  ! 0 no output
                            ! 1 minimum output
                            ! 2 medium
                            ! 3 maximum

if(outputLevel < 0 .or. outputLevel > 3) then
  write(*,*) 'Argument for report90init invalid. (set to 1)'
  outputLevel = 1
endif

call system_clock(clock_tim,clock_2,clock_3)
tim         = dble(clock_tim)/dble(clock_2)
total       = 0.0d0


if( outputLevel == 0 ) return

open(iunit,file='report.txt',action='write')

  call drawline
  call title
  call drawline


end subroutine report90init

!---------------------------------------
subroutine calctime
implicit none
call system_clock(clock_tim,clock_2,clock_3)
t1      = dble(clock_tim)/dble(clock_2)
terapse = t1 - tim
total   = total+terapse
tim     = t1
end subroutine calctime
!---------------------------------------

subroutine report(cha)
character(len=*)   ::  cha

call calctime

if( outputLevel == 0 ) return

write(iunit,'(f9.4,f9.4,2x,a)') total,terapse,cha

if( outputLevel == 3 )then
write(*,'(f9.4,f9.4,2x,a)') total,terapse,cha
endif

end subroutine report
subroutine reportmodule(cha)
character(len=*)   ::  cha

call calctime

if( outputLevel == 0 ) return

write(iunit,'(f9.4,f9.4,2x,a)') total,terapse,cha

if( outputLevel == 3 )then
write(*,'(f9.4,f9.4,2x,a)') total,terapse,cha
endif

end subroutine reportmodule


subroutine report90FundamentalVars(ndim,npmax,nedat,nnset,nnum,nip)
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

end subroutine report90FundamentalVars

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
end module report90
