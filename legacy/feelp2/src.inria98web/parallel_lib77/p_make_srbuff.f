      subroutine p_make_srbuff (p_rank,nsendnum,nrecvnum,npesum,
     $     nsendkaz,nrecvkaz,nsendlist,nrecvlist,nsesum,nresum)
*      
      implicit real*8 (a-h,o-z)
*
      integer p_rank
      dimension nsendkaz(npesum),nrecvkaz(npesum)
      dimension nsendlist(npesum),nrecvlist(npesum)
*
*-------------------------------------
*     initialization of nsesum,nresum
*-------------------------------------
*
      nsesum=0
      nresum=0
*
*-------------------------------------------
*  nsesum : number of the total sending data 
*           in each sending subdomain 
*-------------------------------------------
*
      if (nsendlist(p_rank+1).eq.1) then
         do 100 i=1,nsendnum
            nsesum=nsesum+nsendkaz(i)
 100     continue
      end if
*---------------------------------------------
*  nresum : number of the total receiving data 
*           in each receiving subdomain 
*---------------------------------------------
*
*
      if (nrecvlist(p_rank+1).eq.1) then 
         do 110 i=1,nrecvnum
            nresum=nresum+nrecvkaz(i)
 110     continue
      end if
      return
      end

