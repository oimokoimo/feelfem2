      subroutine time_rep(ifunc,mesg,io_out,isum)
c
c--------------------------------------------------------------
c    Purpose : Report the execution time before MPI_INITIALIZE
c             
c      Input : ifunc
c              mesg
c              io_out : file number for 'feel_out'
c--------------------------------------------------------------
      include 'mpi.incl'
      implicit real*8 (a-h,o-z)
c
      integer iresult
      character mesg*(*)
      save  idtime,itotal
      data itotal/0/
c
      if(ifunc.eq.0) then
         call cjgettmrf (iresult)
         idtime = iresult
         return
      endif
c
      call cjgettmrf (iresult)
      idt =iresult
      itime = idt-idtime
      idtime =idt
      itotal=itotal + itime
c
      isum = itotal
c
      write(io_out,100) (dble(itotal)/1.d+3),(dble(itime)/1.d+3)
     $     ,mesg
100   format(f11.3,1x,'   [',f11.3,'] :  ',a)
      return
      end
c
      subroutine time_repcj(ifunc,p_rank,npe,mesg,io_out,isum)
c--------------------------------------------------------------
c    Purpose : Report the execution time after MPI_INITIALIZE
c             
c      Input : ifunc
c              p_rank : PE number 
c              npe    : Total number of the using PEs
c              mesg
c              io_out : file number for 'feel_out'
c--------------------------------------------------------------
      include 'mpi.incl'
      implicit real*8 (a-h,o-z)
      integer p_rank,size,status(mpi_status_size)
c     
      integer iresult
      character mesg*(*)
c
      save  idtime2,itotal2,itotal
      data itotal2/0/
c
      if(ifunc.eq.0) then
         call cjgettmrf (iresult)
         idtime2 = iresult
         return
      endif
c
      call cjgettmrf (iresult)
      idt =iresult
      itime = idt-idtime2
c
      call mpi_reduce (itime,itime,1,mpi_integer,mpi_sum,
     $        0,mpi_comm_world,ierror)
c
      idtime2=idt
c
      itotal2=itotal2+int(dble(itime)/dble(npe))
*
      if (p_rank.eq.0) then
         write (io_out,100) dble(itotal2 + isum)/1.d+3,
     $        (dble(itime)/(1.d+3*dble(npe)))
     $        ,mesg
      end if
c
c      
 100  format(f11.3,1x,'   [',f11.3,'] :  ',a)
 110  format(f11.3,1x,a)
      return
      end
c
c--------------------------------------------------------------------
c
      subroutine rep_head (io_out)
*
c --------------------------------------------------------------------
*
      write(io_out,800)
 800  format('FEEL P2 Parallel Version PROCEDURE REPORT')  

      write(io_out,*)
      write(io_out,900)
      write(io_out,910)
      write(io_out,920)
 900  format('Sum-up          Sub-Proc         Proc STATUS')
 910  format('Execution time  Execution time   REPORT     ')
 920  format('--------------  --------------   -----------')
      return
      end
c
c--------------------------------------------------------------------
c
      subroutine rep_var (npmax,io_out)
*
c --------------------------------------------------------------------
* npmax
      write(io_out,200) npmax
*
 200  format('                             :  TOTAL NODES ',i9)
      return
      end
c
c
      subroutine rep_CG(iter,zansa,io_out)
c
      implicit real*8 (a-h,o-z)
c
c --------------------------------------------------------------------
      write(io_out,200) iter 
      write(io_out,210) zansa

 200  format('                             :  ITERATION ',i8)
 210  format('                             :  RESIDUAL  ',PE15.7)
*
      return
      end
