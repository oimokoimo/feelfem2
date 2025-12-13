      subroutine preportinit(ioutflag)
*
      include 'mpif.h'
*
      double precision tim,tdiff,tmid,total
      character line*11
*
      common /pfeel_tim/tim,tdiff,tmid,total ,iunit,iout
*----
      line = '-----------'
      iout = ioutflag
      tim  =mpi_wtime()
      tdiff=mpi_wtime()
      tdiff=tdiff-tim
    
      tim  =mpi_wtime()
      total = 0.0d0
*----
      iunit=8
      open(unit=iunit,file='pfeel_out')
*----
      write(iunit,11) line,line,line,line,line
      write(iunit,10)
      write(iunit,11) line,line,line,line,line
*
      if(iout .NE. 0) then
         write(*,11) line,line,line,line,line
         write(*,10)
         write(*,11) line,line,line,line,line
      endif      
*---
10    format('   Total   Erapse   Comment') 
11    format('+--------+--------+',5a11,'+')
*---
      return
*
      end
*--------------- --------------
      subroutine preportnurmesg(cha)
*     ---------- --------------
      character cha*(*)      
      double precision  tim,tdiff,tmid,total
      common /pfeel_tim/tim,tdiff,tmid,total ,iunit,iout
*--
      write(iunit,10) cha
      if(iout .NE. 0 ) then
         write(*,10) cha
      endif
*--
10    format(18x,2x,a)
      return
      end
*--------------- --------------
      subroutine preport(cha)
*     ---------- ------------
*===============================================================
*     MODULE preport
*===============================================================
      include 'mpif.h'
      double precision t1,tim,tdiff,tmid,total
      double precision terapse
      character cha*(*)
      common /pfeel_tim/tim,tdiff,tmid,total ,iunit,iout
*---------------------------
      t1      = mpi_wtime()
      terapse =t1 - tim-tdiff
      total = total+terapse
*--
      write(iunit,10) total,terapse,cha

      if(iout .NE. 0 ) then
         write(*,10) total,terapse,cha
      endif
*--
10    format(f9.4,f9.4,2x,a)
      tim   = t1 
      return
      end
*--------------- --------------
      subroutine preportmodule(cha)
*     ---------- ------------
*===============================================================
*     MODULE preport
*===============================================================
      include 'mpif.h'
      double precision t1,tim,tdiff,tmid,total
      double precision terapse
      character cha*(*)
      common /pfeel_tim/tim,tdiff,tmid,total ,iunit,iout
*---------------------------
      t1      = mpi_wtime()
      terapse =t1 - tim-tdiff
      total = total+terapse
*--
      write(iunit,10) total,terapse,cha

      if(iout .NE. 0 ) then
         write(*,10) total,terapse,cha
      endif
*--
10    format(f9.4,f9.4,2x,'MODULE [',a,']')
      tim   = t1 
      return
      end
      subroutine preportfini
*-----
      include 'mpif.h'
*-----
      double precision t1,tim,tdiff,tmid,total
      double precision terapse
      character line*11
      common /pfeel_tim/tim,tdiff,tmid,total,iunit,iout
*-----
      t1      = mpi_wtime()
      terapse =t1 - tim-tdiff
      total = total+terapse
      line  = '-----------'
*--
      write(iunit,08) line,line,line,line,line
      write(iunit,10) total,terapse
      write(iunit,08) line,line,line,line,line

      if(iout .NE. 0) then
         write(*,08) line,line,line,line,line
         write(*,10) total,terapse
         write(*,08) line,line,line,line,line
      endif
*--
08    format('+--------+--------+',5a11,'+')
10    format(f9.4,f9.4,2x,'END OF REPORT')
      close(iunit)
      return
      end
      subroutine preportsilent
*===============================================================
*     MODULE preportsilent   / Pre-called module before
*                              calling individual time report routine
*
*     This is silent version of preport
*     Initialize the clock for calculating specific job
*    
*===============================================================
      include 'mpif.h'
      double precision t1,tim,tdiff,tmid,total
      double precision terapse
      character cha*(*)
      common /pfeel_tim/tim,tdiff,tmid,total ,iunit,iout
*---------------------------
      t1      = mpi_wtime()
***      terapse =t1 - tim-tdiff
***      total = total+terapse
*--
      tmid   = t1 
      return
      end
      subroutine preportfbcast(nprocs,nwords,ntimes)
*===============================================================
*     MODULE preportfbcast
*    
*     report mpi_bcast time
*===============================================================
      include 'mpif.h'
      double precision t1,tim,tdiff,tmid,total
      double precision terapse
      character cha*(*)
      common /pfeel_tim/tim,tdiff,tmid,total ,iunit,iout
*---------------------------
      t1      = mpi_wtime()
      terapse =t1 - tmid -tdiff
***      total = total+terapse
*--
      write(iunit,10) terapse,nwords,nprocs,ntimes

      if(iout .NE. 0 ) then
         write(*,10) terapse,nwords,nprocs,ntimes
      endif
*--
10    format(9x,f9.4,2x,'FEELBCAST ',i8,' words ',
     $     i3,' Procs ',i3,' times')

*      tim   = t1 
      return
      end
      subroutine preportfgatherbcast(nprocs,nwords)
*===============================================================
*     MODULE preportfbcast
*    
*     report mpi_bcast time
*===============================================================
      include 'mpif.h'
      double precision t1,tim,tdiff,tmid,total
      double precision terapse
      character cha*(*)
      common /pfeel_tim/tim,tdiff,tmid,total ,iunit,iout
*---------------------------
      t1      = mpi_wtime()
      terapse =t1 - tim-tdiff
***      total = total+terapse
*--
      write(iunit,10) terapse,nwords,nprocs

      if(iout .NE. 0 ) then
         write(*,10) terapse,nwords,nprocs
      endif
*--
10    format(9x,f9.4,2x,'FEELGATHERBCAST ',i8,' words ',
     $       i3,' Procs')
*
***      tim   = t1 
      return
      end
      subroutine preportfgather(nprocs,nwords)
*===============================================================
*     MODULE preportfbcast
*    
*     report mpi_bcast time
*===============================================================
      include 'mpif.h'
      double precision t1,tim,tdiff,tmid,total
      double precision terapse
      character cha*(*)
      common /pfeel_tim/tim,tdiff,tmid,total ,iunit,iout
*---------------------------
      t1      = mpi_wtime()
      terapse =t1 - tim-tdiff
***      total = total+terapse
*--
      write(iunit,10) terapse,nwords,nprocs

      if(iout .NE. 0 ) then
         write(*,10) terapse,nwords,nprocs
      endif
*--
10    format(9x,f9.4,2x,'FEELGATHER      ',i8,' words ',
     $       i3,' Procs')
*
***      tim   = t1 
      return
      end
      subroutine preportmem
*===============================================================
*     MODULE preportmem
*    
*     report memory allocation information
*===============================================================
      include 'mpif.h'
      double precision  tim,tdiff,tmid,total
      common /pfeel_tim/tim,tdiff,tmid,total ,iunit,iout      
*---------------------------------------------------------------
      call f_alloc_get_info(np_work,max_heap)
*
      write(iunit,10) np_work

      if(iout .NE. 0 ) then
         write(*,10) np_work
      endif
*--
 10   format(18x,2x,'MEMORY ALLOCATION ',i8,' words (np_work)')
      return
      end
      subroutine preportallmem(myrank,nprocs)
      parameter (MAX_PROCS = 256)
      include 'mpif.h'
*
      integer procbuf1(MAX_PROCS)
      integer procbuf2(MAX_PROCS)
*      
      double precision tim,tdiff,tmid,total
      common /pfeel_tim/tim,tdiff,tmid,total ,iunit,iout      
*---------------------------------------------------
      if(procs .GT.MAX_PROCS) then
         call abortexit(myrank,'TOO MANY PROCS in preportallmem')
      endif
*
      if(myrank.eq.0) call preport('goto report np_work')
      call f_alloc_get_info(np_work,max_heap)
*---
      call mpi_gather(np_work ,1,MPI_INTEGER,
     $                procbuf1,1,MPI_INTEGER,0,mpi_comm_world,ierr)
      call mpi_gather(max_heap,1,MPI_INTEGER,
     $                procbuf2,1,MPI_INTEGER,0,mpi_comm_world,ierr)
*---
      if(myrank.eq.0) then
         call preport('2 mpi_gather callsfor preportallmem')
      endif
*
      if(myrank .ne.0 ) return
      
*--------------------
      write(iunit,10) 
      do 100 i=1,nprocs
         if(i.LT.11) then
            write(iunit,11) i-1,procbuf1(i),procbuf2(i)
         else
            if(i .LT. 101) then
               write(iunit,12) i-1,procbuf1(i),procbuf2(i)
            else
               write(iunit,13) i-1,procbuf1(i),procbuf2(i)
            endif
         endif
 100  continue
*--------------------------
      if(iout .NE. 0 ) then
         write(*,10) 
         do 200 i=1,nprocs
            if(i.LT.11) then
               write(*,11) i-1,procbuf1(i),procbuf2(i)
            else
               if(i .LT. 101) then
                  write(*,12) i-1,procbuf1(i),procbuf2(i)
               else
                  write(*,13) i-1,procbuf1(i),procbuf2(i)
               endif
            endif
               
 200     continue
      endif
*--
 10   format(18x,2x,'MEMORY ALLOCATION REPORT')
 11   format(18x,2x,'------ PE',i1,2x,'  ',i8,'/max ',i8,' words')
 12   format(18x,2x,'------ PE',i2,1x,'  ',i8,'/max ',i8,' words')
 13   format(18x,2x,'------ PE',i3,   '  ',i8,'/max ',i8,' words')
*--
      return
      end

      








