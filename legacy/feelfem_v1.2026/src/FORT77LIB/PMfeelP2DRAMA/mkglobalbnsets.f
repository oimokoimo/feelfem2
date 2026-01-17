      subroutine mkglobalbnsets(feel,myrank,nprocs,
     $                          loc,npmax,
     $                          nbnset,idbctr,idbctr2            )
*--------------------------------------------------------
*-------
* INPUT
*-------
*      LOC2(2,NPMAX)    Node information in Global Node number
*           loc(1,*)    PE id
*           loc(2,*)    Local node number
*
*      IDBCTR(4,nbedat)
*           idbctr(1,*)  NSET number (This is 1 to nnset)
*           idbctr(2,*)  NSET np
*           idbctr(3,*)  NSET nodes
*           idbctr(4,*)  NSET NP_ pointer for inset
*
*-------
* OUTPUT
*-------
*
*     idbctr2(5,no_of_nbnset) NSET in DRAMA like format(double index)
*            (1,*) no         NSET No. 
*            (2,*) nodes      number of nodes
*            (3,*) np         number of additional information
*            (4,*) np_con     (allocate here) Double index node set information
*            (5,*) np_info    (allocate here) nodes*np array for node inform.
*--------------------------------------------------------
*     =============================
      parameter (NUR_ONE_ETYPE = 1)
*     =============================

*-IN--
      real*4    feel(*)
*
      dimension loc(2,npmax)
      dimension idbctr(4,nbnset)
      
*-OUT-
      integer idbctr2(5,*)
*--------------------------------------------------------
      mypeid = myrank
*--------------------------------------------------------
* MAKE Boundary condition related NSET(globally held)
*--------------------------------------------------------------
*------
* BNSET
*------
      do 400 i=1,nbnset

         no_b    = idbctr(1,i)
         np_b    = idbctr(2,i)
         nodes_b = idbctr(3,i)

         call f_alloc(np_con_b,'con for nbnset',nodes_b*2,0,0)
         if(np_b .GT. 1) then
*
*  The first data is node number, so np_b-1 applied.
*  The second (now it exists in feel_dat) is increment for node set
*
            call f_alloc(np_info_b,'con for info',nodes_b*(np_b-1),0,0)
         else
            np_info_b=1
         endif
         
         idbctr2(1,i) = no_b
         idbctr2(2,i) = nodes_b
         idbctr2(3,i) = np_b -1 
         idbctr2(4,i) = np_con_b
         idbctr2(5,i) = np_info_b

         call makelocdat_bnset(loc,npmax, np_b,nodes_b,
     $                         feel(idbctr (4,i)),
     $                         feel(idbctr2(4,i)),feel(idbctr2(5,i)))

 400  continue
*
      return
      end
      subroutine makelocdat_bnset(loc,npmax,np,nodes,
     $                            nset,
     $                            con , info          )
*--------------------------------------------------------
*   MAKE DOUBLE INDEX DATA FOR NSET
*--------------------------------------------------------
      dimension loc(2,npmax)
      dimension nset(np,nodes)
      integer   con(2,nodes)
      integer   info(np-1,nodes)
*
      do 100 i=1,nodes
         con(1,i) = loc(2,nset(1,i))
         con(2,i) = loc(1,nset(1,i))
 100  continue
*
      if(np .gt. 1) then

         do 200 i=1,nodes
            do 220 j=2,np
               info(j-1,i) = nset(j,i)
 220        continue
 200     continue
      endif
      return
      end
