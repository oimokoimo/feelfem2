      subroutine p_solve_pmset (npe,feel,icons,ipdat,
     $     ncont1,ncont2,
     $     ndim,npesum,npmaxsub,nelemsub,np,ndisub,neusub,
     $     neq_sub,naisum,ninsum,nsendnum,nrecvnum,nintotal,
     $     nmatrix,
     $     npp_xsub,npp_ysub,npp_isubelem,npp_nelegru,
     $     npp_nloglo,npp_nsendlist,npp_nrecvlist,npp_ndikaz,
     $     npp_ndinum,npp_neukaz,npp_neunum,npp_matno,npp_ipdsub,
     $     npp_IPFsub,npp_naieq,npp_nineq,npp_nsendtable,
     $     npp_nrecvtable,npp_nsendkaz,npp_nrecvkaz,npp_npsre,
     $     npp_ninner,npp_npsyo,npp_npins,npp_npibsub)
*
      implicit real*8 (a-h,o-z)
*
      real*4 feel(*)
      dimension icons(ncont1)
      dimension ipdat(2,ncont2)
*
      ndim     = icons(1)
      npesum   = icons(2)
      npmaxsub = icons(3)
      nelemsub = icons(4)
      np       = icons(5)
      ndisub   = icons(6)
      neusub   = icons(7)
      neq_sub  = icons(8)
      naisum   = icons(9)
      ninsum   = icons(10)
      nsendnum = icons(11)
      nrecvnum = icons(12)
      nintotal = icons(13)
      nmatrix  = icons(14)
*     
      npp_xsub = ipdat(1,1)
      npp_ysub = ipdat(1,2)
c
      if (ndim.ne.2) stop 'ndim error'
c
      npp_isubelem = ipdat(1,ndim+1)
      npp_nelegru = ipdat(1,ndim+2)
      npp_nloglo = ipdat(1,ndim+3)
      npp_nsendlist = ipdat(1,ndim+4)
      npp_nrecvlist = ipdat(1,ndim+5)
      npp_ndikaz = ipdat(1,ndim+6)
      npp_ndinum = ipdat(1,ndim+7)
      npp_neukaz = ipdat(1,ndim+8)
      npp_neunum = ipdat(1,ndim+9)
      npp_matno = ipdat(1,ndim+10)
      npp_ipdsub = ipdat(1,ndim+11)
      npp_IPFsub = ipdat(1,ndim+12)
      npp_naieq = ipdat(1,ndim+13)
      npp_nineq = ipdat(1,ndim+14)
      npp_nsendtable = ipdat(1,ndim+15)
      npp_nrecvtable = ipdat(1,ndim+16)
      npp_nsendkaz = ipdat(1,ndim+17)
      npp_nrecvkaz = ipdat(1,ndim+18)
      npp_npsre = ipdat(1,ndim+19)
      npp_ninner = ipdat(1,ndim+20)
      npp_npsyo = ipdat(1,ndim+21)
      npp_npins = ipdat(1,ndim+22)
      npp_npibsub = ipdat(1,ndim+23)
*
*     with respect to sending data and recving data
*
      call p_solve_sreqset(npe,ipdat,ndim,ndisub,
     $     neusub,nsendnum,nrecvnum,npesum,feel(npp_npsre))
*
*     with respect to Dirichlet data
      if (ndisub.gt.0) then
         call p_solve_dset (ndisub,ndim,feel(npp_ndikaz),
     $        ipdat,feel(npp_npsyo),feel(npp_npins))
      end if
*
*     with respect to Neumann data
      if (neusub.gt.0) then
         call p_solve_nset (ndisub,neusub,ndim,feel(npp_neukaz),
     $        ipdat,feel(npp_npibsub))
      end if
      return
      end
*
      subroutine p_solve_sreqset (npe,ipdat,ndim,ndisub,
     $     neusub,nsendnum,nrecvnum,npesum,npp_nsrequ)
*
*++++++++++++++++++++++++++++++
*     FEEL/P2/Cenju-3/MPI subprogram
*     Purpose : sending and receiving data
*++++++++++++++++++++++++++
*
      implicit real*8 (a-h,o-z)
*
      dimension npp_nsrequ(npesum)
      dimension ipdat(2,*)
*
*     with respect to sending data
*
      do 100 i=1,nsendnum
         npp_nsrequ(i) = ipdat(1,ndim+23+2*ndisub+neusub+i)
 100  continue
*
*     with respect to receiving data
*
      do 200 i=1,nrecvnum
         npp_nsrequ(i+nsendnum)
     $        = ipdat(1,ndim+23+2*ndisub+neusub+npe+i)
 200  continue
*
*     if using one processor,.....(nsendnum=nrecvnum=0)
*     
      if ((nsendnum.eq.0).and.(nrecvnum.eq.0)) then
         npp_nsrequ(1)=ipdat(1,ndim+23+2*ndisub+neusub+1)
      end if
*
      return
      end

*
      subroutine p_solve_dset (ndisub,ndim,ndikaz,ipdat,
     $     npp_nsyori,npp_inset)
*
*++++++++++++++++++++++++++++++
*     FEEL/P2/Cenju-3/MPI subprogram
*     Purpose : Dirichlet data
*++++++++++++++++++++++++++
*
      implicit real*8 (a-h,o-z)
*
      dimension ipdat(2,*)
      dimension ndikaz(*)
      dimension npp_nsyori(ndisub),npp_inset(ndisub)
*
      do 10 i=1,ndisub
         if (ndikaz(i).gt.0) then
            npp_inset(i)=ipdat(1,ndim+23+ndisub+i)
            npp_nsyori(i)=ipdat(1,ndim+23+i)
         end if
 10   continue
      return
      end
*
      subroutine p_solve_nset (ndisub,neusub,ndim,neukaz,
     $     ipdat,npp_ibsubelem)
*
*
*++++++++++++++++++++++++++++++
*     FEEL/P2/Cenju-3/MPI subprogram
*     Purpose :  Neumann data
*++++++++++++++++++++++++++
*
      implicit real*8 (a-h,o-z)
*      
      dimension ipdat(2,*)
      dimension neukaz(*)
      dimension npp_ibsubelem(neusub)
*
      do 10 i=1,neusub
         if (neukaz(i).gt.0) then
            npp_ibsubelem(i)=ipdat(1,ndim+23+i+2*ndisub)
         end if
 10   continue
      return
      end


