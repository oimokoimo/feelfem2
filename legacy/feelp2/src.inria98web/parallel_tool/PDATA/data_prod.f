      subroutine data_prod (npmax,npesum,nreadrv,
     $     nrecvlist,ninner,icheck)
*
      implicit real*8 (a-h,o-z)
*
      dimension ninner(npmax)
      dimension icheck(npmax)
      dimension nreadrv(npesum),nrecvlist(npesum)
*     --- 各部分領域でのインターフェース上の節点番号
*        の数の初期化。--------------
*         
      do 10 iq=1,npesum
         inread=0
         do 2 i=1,npmax
            icheck(i)=0
            ninner(i)=0
 2       continue
         if (nrecvlist(iq).eq.1) then
*
            rewind (14+iq+3*npesum)
*     
            do 11 i=1,nreadrv(iq)
               read (14+iq+3*npesum) ndummy,naiseki,ndummy
               if (icheck(naiseki).eq.0) then
                  inread=inread+1
                  ninner(inread)=naiseki
                  icheck(naiseki)=1
               end if
 11         continue
*
*     +++++++++++++++++++++++++++++
*     ベクトルの内積に必要なデータをファイルに落す
*     ++++++++++++++++++++++++++++++
            write (14+iq+5*npesum,9001) inread
            do 20 i=1,inread
               write (14+iq+5*npesum,9001) ninner(i)
 20         continue
*
         end if
 10   continue
*
 9001 format(i8)
      return 
      end




