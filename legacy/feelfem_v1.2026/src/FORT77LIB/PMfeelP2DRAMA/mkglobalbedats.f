      subroutine mkglobalbedats(feel,myrank,nprocs,
     $                          loc,npmax,
     $                          nbedat,inbctr,inbctr2           )
*--------------------------------------------------------
*-------
* INPUT
*-------
*      LOC(2,NPMAX)    Node information in Global Node number
*          loc(1,*)    PE id
*          loc(2,*)    Local node number
*
*      INBCTR(5,NBEDAT) Input EDATS
*           inbctr(1,*)  EDAT number (This is 2 to nbedat+1)
*           inbctr(2,*)  EDAT np
*           inbctr(3,*)  EDAT nelem
*           inbctr(4,*)  NP_  pointer for ielem
*           inbctr(5,*)  NP_  pointer for matno*
*
*-------
* OUTPUT
*-------
*
*     inbctr2(5,no_ofp_nbedat)  EDAT in DRAMA format (Mainly for Neumann cond.)
*            (1,*) no         EDAT no
*            (2,*) nelems     number of elements
*            (3,*) np_enptr   (allocate here) Pointer to np_con
*            (4,*) np_con     (allocate here) Double index ielem
*            (5,*) np_matno   (allocate here) MATNO
*     
*--------------------------------------------------------
*     =============================
      parameter (NUR_ONE_ETYPE = 1)
*     =============================

*-IN--
      real*4    feel(*)
*
      dimension loc(2,npmax)
      dimension inbctr(5,nbedat)
      
*-OUT-
      integer inbctr2(5,*)
*--------------------------------------------------------
      mypeid = myrank
*--------------------------------------------------------
*--------------------------------------------------------------
* MAKE Boundary condition related EDAT/NSET
*--------------------------------------------------------------
* BEDAT
*------
      do 300 i=1,nbedat
         no_b    = inbctr(1,i)
         np_b    = inbctr(2,i)
         nelem_b = inbctr(3,i)
         
         call f_alloc(np_enptr_b,'enptr for nbedat',(nelem_b+1)*2,0,0)
         call f_alloc(np_con_b  ,'con   for nbedat',
     $        np_b*nelem_b*2+(NUR_ONE_ETYPE-NUR_ONE_ETYPE),       0,0)
         call f_alloc(np_matno_b,'matno for nbedat',nelem_b      ,0,0)

         inbctr2(1,i) = no_b
         inbctr2(2,i) = nelem_b
         inbctr2(3,i) = np_enptr_b
         inbctr2(4,i) = np_con_b
         inbctr2(5,i) = np_matno_b

         call makelocdat_bedat(loc,npmax, np_b,nelem_b,
     $        feel(inbctr (4,i)),feel(inbctr (5,i)),
     $        feel(inbctr2(3,i)),feel(inbctr2(4,i)),feel(inbctr2(5,i)))

 300  continue
*
      return
      end
      subroutine makelocdat_bedat(loc,npmax, np,nelem,
     $     ielem,matno,
     $     enptr,con,matno2                            )
*------------------------------------------------------------
      parameter (NUR_ONE_ETYPE = 1)
*------------------------------------------------------------
      dimension loc(2,npmax)
      dimension ielem(np,nelem),matno(nelem)
      integer   enptr(2,*)
      integer   con(2,*)
      dimension matno2(*)
*
      ipos  = 1
      ieptr = 0
      do 100 i=1,nelem
         matno2(i) = matno(i)
         ieptr = ieptr + 1
         enptr(2,ieptr) = NUR_ONE_ETYPE
         enptr(1,ieptr) = ipos

         do 110 j=1,np+(NUR_ONE_ETYPE-NUR_ONE_ETYPE)
            con(1,ipos) = loc(2,ielem(j,i))
            con(2,ipos) = loc(1,ielem(j,i))
            ipos = ipos + 1
 110     continue

 100  continue 
*
      ieptr = ieptr + 1
      enptr(1,ieptr) = ipos
*
      return
      end
