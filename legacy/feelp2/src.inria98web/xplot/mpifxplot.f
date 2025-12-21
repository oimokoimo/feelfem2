      subroutine mpixplotopenpl
*--------------------------------------------------------
      include 'mpifxplot.h'
      include 'mpifxplotcommon.h'
*--------------------------------------------------------
      nptint = 0
      nptdbl = 0
      ncoms  = 0
*
      return
      end
      subroutine mpixplot4d(ncommand, d1,d2,d3,d4)
*--------------------------------------------------------
      include 'mpifxplot.h'
      include 'mpifxplotcommon.h'
*--------------------------------------------------------
*-<1>-
      ncoms          = ncoms  + 1
*-<2>-
      if(nptint .EQ. MAX_INTBUF) then
         call abortexit(999,'NO SPACE FOR INTBUF FOR MPIXPLOT')
      endif
*
      nptint         = nptint + 1
      intbuf(nptint) = ncommand
*-<3>-
      if(nptdbl + 4 .GT. MAX_DBLBUF) then
         call abortexit(999,'NO SPACE FOR DBLBUF FOR MPIXPLOT')
      endif
*----
      nptdbl         = nptdbl + 1
      dblbuf(nptdbl) = d1
      nptdbl         = nptdbl + 1
      dblbuf(nptdbl) = d2
      nptdbl         = nptdbl + 1
      dblbuf(nptdbl) = d3
      nptdbl         = nptdbl + 1
      dblbuf(nptdbl) = d4
*-----
      return
      end
      subroutine mpixplot1i2d(ncommand, i1,d1,d2)
*--------------------------------------------------------
      include 'mpifxplot.h'
      include 'mpifxplotcommon.h'
*--------------------------------------------------------
*-<1>-
      ncoms          = ncoms  + 1
*-<2>-
      if(nptint+2 .GT. MAX_INTBUF) then
         call abortexit(999,'NO SPACE FOR INTBUF FOR MPIXPLOT')
      endif
*
      nptint         = nptint + 1
      intbuf(nptint) = ncommand
      nptint         = nptint + 1
      intbuf(nptint) = i1
*-<3>-
      if(nptdbl + 2 .GT. MAX_DBLBUF) then
         call abortexit(999,'NO SPACE FOR DBLBUF FOR MPIXPLOT')
      endif
*----
      nptdbl         = nptdbl + 1
      dblbuf(nptdbl) = d1
      nptdbl         = nptdbl + 1
      dblbuf(nptdbl) = d2
*-----
      return
      end
      subroutine mpixplot2i2d(ncommand, i1,i2,d1,d2)
*--------------------------------------------------------
      include 'mpifxplot.h'
      include 'mpifxplotcommon.h'
*--------------------------------------------------------
*-<1>-
      ncoms          = ncoms  + 1
*-<2>-
      if(nptint+3 .GT. MAX_INTBUF) then
         call abortexit(999,'NO SPACE FOR INTBUF FOR MPIXPLOT')
      endif
*
      nptint         = nptint + 1
      intbuf(nptint) = ncommand
      nptint         = nptint + 1
      intbuf(nptint) = i1
      nptint         = nptint + 1
      intbuf(nptint) = i2
*-<3>-
      if(nptdbl + 2 .GT. MAX_DBLBUF) then
         call abortexit(999,'NO SPACE FOR DBLBUF FOR MPIXPLOT')
      endif
*----
      nptdbl         = nptdbl + 1
      dblbuf(nptdbl) = d1
      nptdbl         = nptdbl + 1
      dblbuf(nptdbl) = d2
*-----
      return
      end
      subroutine mpixplotfspace(x1,y1,x2,y2)
*--------------------------------------------------------
      include 'mpifxplot.h'
      include 'mpifxplotcommon.h'
*--------------------------------------------------------
      call mpixplot4d(NUM_FSPACE,x1,y1,x2,y2)
      return
      end
      subroutine mpixplotfline(x1,y1,x2,y2)
*--------------------------------------------------------
      include 'mpifxplot.h'
      include 'mpifxplotcommon.h'
*--------------------------------------------------------
      call mpixplot4d(NUM_FLINE,x1,y1,x2,y2)
      return
      end
      subroutine mpixplotfnumber(inum,x,y)
*--------------------------------------------------------
      include 'mpifxplot.h'
      include 'mpifxplotcommon.h'
*--------------------------------------------------------
      call mpixplot1i2d(NUM_FNUMBER,inum,x,y)
      return
      end
      subroutine mpixplotDRAMAindex(ind,ipe,x,y)
*--------------------------------------------------------
      include 'mpifxplot.h'
      include 'mpifxplotcommon.h'
*--------------------------------------------------------
      call mpixplot2i2d(NUM_DRAMAINDEX,ind,ipe,x,y)
      return
      end
      subroutine mpixplotdraw(feel,myrank,nprocs)
*--------------------------------------------------------
      include 'mpifxplot.h'
*
      real*4   feel(*)
*
      include 'mpifxplotcommon.h'
*--------------------------------------------------------
      call feelgatherv(myrank,nprocs,feel,nptint,intbuf,
     $                 np_ibuf,np_intcounts,np_intdispls       )
*
      call feelgathervdbl(myrank,nprocs,feel,nptdbl,dblbuf,
     $                 np_dbuf,np_dblcounts,np_dbldispls       )

      if(myrank.eq.0) then
         call mpifxplotdrawnow(nprocs,
     $                         feel(np_ibuf),feel(np_intcounts),
     $                         feel(np_intdispls),
     $                         feel(np_dbuf),feel(np_dblcounts),
     $                         feel(np_dbldispls) )
      endif
      return
      end
      subroutine mpifxplotdrawnow(nprocs,
     $                            ibuf,icounts,idispls,
     $                            dbuf,dcounts,ddispls )
*-----------------------------------------------------------
      include 'mpifxplot.h'
*
      integer*4 ibuf(*)
      integer*4 icounts(*),idispls(*)
      real*8    dbuf(*)
      integer*4 dcounts(*),ddispls(*)
*
      character mesg*38
*-----------------------------------------------------------
      call openpl
*
      do 100 i=1,nprocs
*         
         ncts = icounts(i)
         if(ncts .eq. 0) goto 100
*         
         nbase_int = idispls(i)
         nbase_dbl = ddispls(i)
         
         nptr_int  = 0
         nptr_dbl  = 0
*
*<LOOP>
 101     continue
*
         if(nptr_int .ge. ncts) then
            if(nptr_int .ne. ncts) write(*,*) 'something strange...'
            goto 100
         endif
*-----
         nptr_int = nptr_int + 1
         ncom = ibuf(nbase_int + nptr_int)
*-------------------------FSPACE--------------------
         if(ncom .EQ. NUM_FSPACE) then
            call fspace(dbuf(nbase_dbl+nptr_dbl+1),
     $                  dbuf(nbase_dbl+nptr_dbl+2),
     $                  dbuf(nbase_dbl+nptr_dbl+3),
     $                  dbuf(nbase_dbl+nptr_dbl+4))
            nptr_dbl = nptr_dbl + 4
*
            goto 101
         endif
*-------------------------FSPACE--------------------


*-------------------------FLINE---------------------
         if(ncom .EQ. NUM_FLINE) then
            call fline(dbuf(nbase_dbl+nptr_dbl+1),
     $                 dbuf(nbase_dbl+nptr_dbl+2),
     $                 dbuf(nbase_dbl+nptr_dbl+3),
     $                 dbuf(nbase_dbl+nptr_dbl+4))
            nptr_dbl = nptr_dbl + 4
*
            goto 101
         endif
*-------------------------FLINE---------------------

*-------------------------FNUMBER-------------------
         if(ncom .EQ. NUM_FNUMBER) then
            call fnumber(dbuf(nbase_dbl+nptr_dbl+1),
     $                   dbuf(nbase_dbl+nptr_dbl+2),
     $                   ibuf(nbase_int+nptr_int+1) )
            nptr_dbl = nptr_dbl + 2
            nptr_int = nptr_int + 1
*
            goto 101
         endif
*-------------------------FNUMBER-------------------
         
         write(*,*) 'UNKNOWN COMMAND'
         call abortexit(0,'mpifxplot.f')
*
 100  continue
*
      call xwait
      return
      end

         



