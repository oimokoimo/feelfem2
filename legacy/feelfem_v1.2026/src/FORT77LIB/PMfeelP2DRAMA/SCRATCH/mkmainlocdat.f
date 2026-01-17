      subroutine mkmainlocdat(feel,myrank,nprocs,
     $                        x,y,ielem,metis,matno,
     $                        np,nelem,loc2,npmax,
     $                        mynode,myelem,xloc,yloc,enptr,con,matnoloc )
*--------------------------------------------------------
*     Make main enptr/con data.  loc2 data
*

*     ONLY ONE MESH TYPE ASSUMED NOW.  -> NUR_EINE_FLAG
*     BECAUSE THIS FUNCTION MADE FOR READING FEEL_DAT
*    (But upgrade is not so difficult, I hope.....)
*     =============================
      parameter (NUR_ONE_ETYPE = 1)
*     =============================
*-------
* INPUT
*-------
*      x(npmax),y(npmax)
*      ielem(np,nelem),matno(nelem)
*      metis(nelem)
*
*      LOC2(3,npmax)    Node information in Global Node number
*           loc(1,*)    PE id
*           loc(2,*)    Local node number
*           loc(3,*)    work area(Not used in this subroutine)
*
*-------
* OUTPUT
*-------
*     enptr(2,myelem+1)  DRAMA compatible Element data pointer (already allocated)
*     con               DRAMA compatible Double indexing      (already allocated)
*     xloc(mynode),yloc(mynode)
*     matnoloc(myelem)
*--------------------------------------------------------
*-IN--
      real*4    feel(*)
*
      integer*4 myrank,nprocs
      real*8    x(*),y(*)
      dimension ielem(np,nelem),matno(nelem)
      dimension metis(nelem)
      dimension loc2(3,npmax)

*-OUT-
      real*8 xloc(*),yloc(*)
      integer enptr(2,*)       ,matnoloc(*)
      integer con  (2,*)
*--------------------------------------------------------
      mypeid = myrank
*--------------------------------------------------------
* XLOC/YLOC/(ZLOC)
*-----------------
      iptr = 0
      do 100 i=1,npmax
         if(loc2(1,i) .eq. mypeid) then
            iptr = iptr + 1
            xloc(iptr) = x(i)
            yloc(iptr) = y(i)
            if(iptr .ne. loc2(2,i)) then
               call abortexit(myrank,'Contradiction/mkmainlocdat')
            endif
         endif
 100  continue
*-----------------
      if(mynode .ne. iptr) then
         call abortexit(myrank,'Error in mkmainlocdat/02-May-00')
      endif
*--------------------------------------------------------
* Make enptr,con
*-----------------
      ieptr = 0
      ipos  = 1
* 
* ieptr++ at the beginning, but ipos++ at the end
*
      do 200 i=1,nelem
         if(metis(i) .EQ. mypeid) then
*
            ieptr          = ieptr + 1
            enptr(1,ieptr) = ipos
            enptr(2,ieptr) = NUR_ONE_ETYPE
            matnoloc(ieptr)= matno(i)
*
            do 210 j=1,np
               con(1,ipos+j-1) = loc2(2,ielem(j,i))
               con(2,ipos+j-1) = loc2(1,ielem(j,i))
 210        continue
*
            ipos = ipos + np
         endif
 200  continue
*
      if( myelem .NE. ieptr) then
         call abortexit(myrank,'myelem .ne. ieptr(mkmainlocdat)')
      endif
*
      ieptr          = ieptr + 1
      enptr(1,ieptr) = ipos
*
      return
      end
