      subroutine edatrange(x,y,ielem,ne,np,XMIN,XMAX,YMIN,YMAX)
*-------------------------------------------------------------------
*  FEEL P2 System Subroutine
*-------------------------------------------------------------------
*  Purpose: Calculate the range of edat nodes
*  
*  Caution: This routine is for CONTOUR
*
*-------------------------------------------------------------------
      implicit real*8 (a-h,o-z)
      dimension x(*),y(*)
      dimension ielem(np,ne)
c
      XMIN =  1.0d72
      YMIN =  1.0d72
      XMAX = -1.0d72
      YMAX = -1.0d72
      
      do 100 i=1,ne
         do 110 j=1,np
            in = ielem(j,i)
            xmin = min(xmin,x(in))
            ymin = min(ymin,y(in))
            xmax = max(xmax,x(in))
            ymax = max(ymax,y(in))
 110     continue
 100  continue

      return
      end
