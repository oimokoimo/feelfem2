      subroutine timeinit
*--------------------------------------------------------------------
* FEEL Fortran77 System subroutine
*  
* File    : cputime.f 
* Date    : 98/03/19
* Purpose : measure cputime for Fortran PowerStation for MS Windows
* 
*--------------------------------------------------------------------
      real*8 tm_total
      real*4 timebuf(2),dtime,ret
*
      common /fem_tim/tm_total,timebuf
*
      ret      = dtime(timebuf)
      tm_total = 0.0d0
*
      return
      end
      subroutine cputime(total,erapse)
      real*8 total,erapse
      real*8 tm_total
      real*4 timebuf(2),dtime,ret
*
      common /fem_tim/tm_total,timebuf
*
      ret      = dtime(timebuf)
      erapse   = dble(ret)
      tm_total = dble(ret)+tm_total
      total    = tm_total
*  	
      return
      end
      real*8 function erapstime()
      implicit real*8 (a-h,o-z)
      call cputime(total,erapse)        
      erapstime=total
      return
      end
      subroutine getdate( date16 )
      character*16 date16
      character*8  DATE,DATESTR
      character*8  CLOCK,CLOCKSTR
*
      DATESTR = DATE()
      read(DATESTR,100) IMONTH,IDAY,IYEAR
100   format(i2,1x,i2,1x,i2)
      if(IYEAR .GT. 50) then
        IYEAR = IYEAR+1900
      else
        IYEAR = IYEAR+2000
      endif
*
      CLOCKSTR=CLOCK()
      read(CLOCKSTR,200) IHOUR,IMINUTE
200   format(i2,1x,i2)
*
      write(date16,300) IYEAR,IMONTH,IDAY,IHOUR,IMINUTE
300   format(i4,'/',i2,'/',i2,' ',i2,':',i2)
*
      if(date16(6:6)   .EQ. ' ') date16(6:6)  ='0'
      if(date16(9:9)   .EQ. ' ') date16(9:9)  ='0'
      if(date16(12:12) .EQ. ' ') date16(12:12)='0'
      if(date16(15:15) .EQ. ' ') date16(15:15)='0'
*
      return
      end


