      subroutine p_make_sreq (nsendnum,nsendndkaz,
     $     feel,iunit,np_nsenod,IPFsub,ipdsub,npmaxsub,
     $     np_nsrequ,nmade,nsendkaz,nrecvnum,npesum,
     $     idat,nbase,ipe,nrecvndkaz,np_nrenod,
     $     nrecvkaz,nsendlist,nrecvlist,ndisub,neusub,npe)
*++++++++++++++++++++++++++++++
*     FEEL/P2/Cenju-3/MPI subprogram
*     Purpose : change node data to equation data
*++++++++++++++++++++++++++
*
      implicit real*8 (a-h,o-z)
*
      real*4 feel(*)
*
      dimension nsendndkaz(npesum)
      dimension nsendkaz(npesum)
      dimension np_nsenod(npesum)
      dimension np_nsrequ(npesum)
      dimension IPFsub(npmaxsub),ipdsub(npmaxsub)
      dimension idat(2,*),nbase(2,*)
      dimension nrecvndkaz(npesum)
      dimension nrecvkaz(npesum),np_nrenod(npesum)
      dimension nsendlist(npesum),nrecvlist(npesum)
*-----------------------
*
      if (nsendlist(ipe).eq.1) then
         do 20 i=1,nsendnum
            nsdonum=nsendndkaz(i)
            call p_calc_neq (nsdonum,feel(np_nsenod(i)),
     $           nseqnum,IPFsub,npmaxsub)
            nsendkaz(i)=nseqnum
*
            call f_alloc (np_nsrequ(i),'Read nsrequ(i)',
     $           nseqnum,0)
*
            idat(1,nmade+23+2*ndisub+neusub+i)
     $           =np_nsrequ(i)-nbase(1,ipe)+nbase(1,1)
            idat(2,nmade+23+2*ndisub+neusub+i)
     $           =nseqnum
*
            call p_make_eqno (nsdonum,feel(np_nsenod(i)),
     $           IPFsub,ipdsub,feel(np_nsrequ(i)),
     $           nseqnum,npmaxsub)
*
 20      continue
      end if
*
*     ++++++受信用データを方程式数、方程式番号に直す。++++
      if (nrecvlist(ipe).eq.1) then
         do 21 i=1,nrecvnum
            nrdonum=nrecvndkaz(i)
            call p_calc_neq (nrdonum,feel(np_nrenod(i)),
     $           nreqnum,IPFsub,npmaxsub)
            nrecvkaz(i)=nreqnum
*
            call f_alloc (np_nsrequ(i+nsendnum),'Read nsrequ(i)',
     $           nreqnum,0)
*
            idat(1,nmade+23+2*ndisub+neusub+npe+i)
     $           =np_nsrequ(i+nsendnum)-nbase(1,ipe)+nbase(1,1)
            idat(2,nmade+23+2*ndisub+neusub+npe+i)
     $           =nreqnum
*
            call p_make_eqno (nrdonum,feel(np_nrenod(i)),
     $           IPFsub,ipdsub,feel(np_nsrequ(i+nsendnum)),
     $           nreqnum,npmaxsub)
*     
 21      continue
      end if
*
      if ((nsendlist(ipe).eq.0).and.(nrecvlist(ipe).eq.0))
     $     then
         call f_alloc (np_nsrequ(1),'Read nsrequ(1)',
     $        1,0)
         idat(1,nmade+23+2*ndisub+neusub+1)
     $        =np_nsrequ(1)-nbase(1,ipe)+nbase(1,1)
         idat(2,nmade+23+2*ndisub+neusub+1)
     $        =1
      end if
*
      return
      end      


