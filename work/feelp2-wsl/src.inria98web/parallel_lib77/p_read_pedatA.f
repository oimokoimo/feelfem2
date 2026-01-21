      subroutine p_read_pedatA (iunit,npesum,npmaxsub,
     $     nelemsub,np,ndisub,
     $     neusub,
     $     isubelem,nelegru,
     $     nloglo,matno,
     $     nsendlist,nrecvlist,
     $     ndikaz,ndinum,neukaz,neunum,ipe,
     $     nmatrix)
*+++++++++++++++++++++++++++++++++++++++++++++++
*     Date 1995 9/21
*+++++++++++++++++++++++++++++++++++++++++++++
      implicit real*8 (a-h,o-z)
*
      character*20 fmt
*
      dimension nloglo(npmaxsub)
      dimension nelegru(nelemsub),isubelem(np,nelemsub)
      dimension matno(nelemsub)
      dimension ndikaz(*),ndinum(*),neukaz(*),neunum(*)
      dimension nsendlist(*),nrecvlist(*)
*
*
      do 10 is=1,npmaxsub
         read (iunit,9001) nloglo(is)
 10   continue
*
*
      do 20 is=1,npesum
         read (iunit,9001) nsendlist(is)
 20   continue
*
*
      do 30 is=1,npesum
         read (iunit,9001) nrecvlist(is)
 30   continue
*     
      write (fmt,8001) np+1
 8001 format ('(',i,'i8)')
      do 31 i=1,nelemsub
         read (iunit,fmt) (isubelem(ln,i),ln=1,np),
     $        matno(i)
 31   continue
*
      do 50 j=1,nelemsub
         read (iunit,9001) nelegru(j)
 50   continue
*
      do 60 in=1,ndisub
         read (iunit,9011) ndikaz(in),ndinum(in)
 60   continue      
*
      do 70 in=1,neusub
         read (iunit,9011) neukaz(in),neunum(in)
 70   continue
*     
 9001 format(i8)
 9011 format(2i8)
      return
      end


