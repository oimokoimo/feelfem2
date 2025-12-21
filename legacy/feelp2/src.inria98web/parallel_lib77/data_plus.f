      subroutine data_plus (rank,neq_sub,rw,srb,
     $     nsrequ,
     $     nsendnum,nrecvnum,npesum,
     $     nsesum,nresum,nsendkaz,nrecvkaz,nsendlist,
     $     nrecvlist,nsendtable,nrecvtable)
*
c+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*     FEEL/P2/Cenju-3/MPI subprogram
*     Purpose : nsrequ(nsesum+nresum) 
*             : summation of the values on the interface for 
*               solving
*++++++++++++++++++++++++++
      implicit real*8 (a-h,o-z)
*
      include 'mpi.incl'
*
      integer rank,size,status(mpi_status_size)
*
      dimension nsendlist(npesum),nrecvlist(npesum)
      dimension nsendkaz(npesum),nrecvkaz(npesum)
      dimension nsendtable(npesum),nrecvtable(npesum)
*++++++++++++
c    Value on the nodes on the interface
c+++++++++++    
      dimension rw(neq_sub)
*     ---- send_buffer(srb(i),i=1,nsesum) & 
*     receive buffer(srb(i),i=nsesum+1,nsesum+nresum) ----
*
      dimension srb(nsesum+nresum)
* --------------------- 
c   Equation number on the interface
c ---------------------
      dimension nsrequ(nsesum+nresum)
* --------------- -----------------------
c     SEND the value to the PE whose number is minimal
c -----------------------------------------
      if (nsendlist(rank+1).eq.1) then
         nshaji=0
         do 10 i=1,nsendnum
            do 20 j=1,nsendkaz(i)
               srb(nshaji+j)=rw(nsrequ(nshaji+j))
 20         continue
            nshaji=nshaji+nsendkaz(i)
 10      continue
*    
         nshaji=1
         do 30 i=1,nsendnum
            call mpi_send (srb(nshaji),nsendkaz(i),
     $           mpi_double_precision,nsendtable(i)-1,
     $           0,mpi_comm_world,ierror)
            nshaji=nshaji+nsendkaz(i)
 30      continue
      end if
*
*    
      if (nrecvlist(rank+1).eq.1) then
         nrhaji=1
*
         do 40 i=1,nrecvnum
            call mpi_recv(srb(nsesum+nrhaji),nrecvkaz(i),
     $           mpi_double_precision,nrecvtable(i)-1,
     $           0,mpi_comm_world,status,ierror)
            nrhaji=nrhaji+nrecvkaz(i)
 40      continue
*     
*    
*     
         nrhaji=0
         do 50 i=1,nrecvnum
            do 60 j=1,nrecvkaz(i)
               rw(nsrequ(nsesum+nrhaji+j))=
     $              rw(nsrequ(nsesum+nrhaji+j))+
     $              srb(nsesum+nrhaji+j)
 60         continue
            nrhaji=nrhaji+nrecvkaz(i)
 50      continue
*
*    
         nshaji=0
         do 70 i=1,nrecvnum
            do 80 j=1,nrecvkaz(i)
               srb(nsesum+nshaji+j)=rw(nsrequ(nsesum+nshaji+j))
 80         continue
            nshaji=nshaji+nrecvkaz(i)
 70      continue
*
*     
         nshaji=1
         do 90 i=1,nrecvnum
            call mpi_send (srb(nsesum+nshaji),nrecvkaz(i),
     $           mpi_double_precision,nrecvtable(i)-1,
     $           1,mpi_comm_world,ierror)
            nshaji=nshaji+nrecvkaz(i)
 90      continue
      end if
*
*
      if (nsendlist(rank+1).eq.1) then
         nrhaji=1
         do 110 i=1,nsendnum
            call mpi_recv(srb(nrhaji),nsendkaz(i),
     $           mpi_double_precision,nsendtable(i)-1,
     $           1,mpi_comm_world,status,ierror)
            nrhaji=nrhaji+nsendkaz(i)
 110     continue
*
         nshaji=0
         do 130 i=1,nsendnum
            do 140 j=1,nsendkaz(i)
               rw(nsrequ(nshaji+j))=srb(nshaji+j)
 140        continue
            nshaji=nshaji+nsendkaz(i)
 130     continue
*
      end if
*     
      return 
      end
         

