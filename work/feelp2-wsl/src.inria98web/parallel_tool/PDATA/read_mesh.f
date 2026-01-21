      subroutine read_mesh (ngru,nzoku,nelem,nankai)
*
      implicit real*8 (a-h,o-z)
*
      dimension ngru(nelem)
      dimension nzoku(nelem)
*
      do 10 i=1,nelem/6
         read (16,9011) (ngru(k),k=(i-1)*6+1,i*6)
 10   continue
*     
      if (((nelem/6)*6+1).le.nelem) then
         read (16,9011) (ngru(k),k=(nelem/6)*6+1,nelem)
      end if
*      
*
      do 20 i=1,nelem/6
         read (16,9011) (nzoku(k),k=(i-1)*6+1,i*6)
 20   continue
*
      if (((nelem/6)*6+1).le.nelem) then
         read (16,9011) (nzoku(k),k=(nelem/6)*6+1,nelem)
      end if
*
 9011 format(6i8)
*
      close (16)
*
      do i=1,nelem
         if (ngru(i).eq.0) then
            stop 'ngru zero error'
         end if
         if (ngru(i).gt.nelem) then
            stop 'ngru over error'
         end if
         if (nzoku(i).eq.0) then
            stop 'nzoku error'
         end if
         if (nzoku(i).gt.2**nankai) then
            stop 'nzoku over error'
         end if
      end do
      return 
      end
