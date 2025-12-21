      subroutine data_dcond0 (inset,number,npesub,npenum,
     $     npmax,npesum,ndikaz,nodes,np)
*++++++++++++++
*     Dirichlet条件の必要な並列化データを作る。
*     概要：number番目のDirichlet条件が課されている節点数の
*     各部分領域毎のデータを求める。
*+++++++++++++
      implicit real*8 (a-h,o-z)
*
      dimension inset(np,nodes)
      dimension npesub(0:npmax)
      dimension npenum(npmax*npesum)
*
      dimension ndikaz(npesum)
*
*----各部分領域iwでの節点集合number(feel_datでの番号)NSET集合
*     (Dirichlet条件) ndikaz(iw)のゼロクリア ---
      do 3 iw=1,npesum
         ndikaz(iw)=0
 3    continue
*
*
*     number番目のNSET集合の各領域に課せられている節点数
      do 10 jd=1,nodes
* ++++ Dirichlet条件が課されている全体節点番号kd ++++
         kd=inset(1,jd)
         do 13 md=npesub(kd-1),npesub(kd)-1
            ndikaz(npenum(md))=ndikaz(npenum(md))+1
 13      continue
 10   continue
*
      return
      end 
*
*
*+++++++++++++++++++++++++++++++++++++++++++++
*
*
      subroutine data_dcond1 (inset,number,npesub,npenum,
     $     npeloc,npmax,npesum,nodes,np)
*++++++++++++++
*     Dirichlet条件の必要な並列化データを作る。
*     概要：Dirichlet条件が課されている節点を
*     各部分領域に部分節点番号に振り分けて
*     ファイルに落す。
*+++++++++++++
      implicit real*8 (a-h,o-z)
*
      dimension inset(np,nodes)
      dimension npesub(0:npmax)
      dimension npenum(npmax*npesum)
      dimension npeloc(npmax*npesum)
*
*
      do 20 jd=1,nodes
*/Dirichlet条件が課されている全体節点番号kd*/
         kd=inset(1,jd)
*
*
*     複数の領域 に属す節点なら、
         if (npesub(kd)-npesub(kd-1).ge.2) then
            minryo=npenum(npesub(kd-1))
            minb=npesub(kd-1)
            do 35 m2=npesub(kd-1)+1,npesub(kd)-1
               minryo=min0(minryo,npenum(m2))
                  if (minryo.eq.npenum(m2)) then
                     minb=m2
                  end if
 35            continue
            else 
               minryo=npenum(npesub(kd-1))
               minb=npesub(kd-1)
            end if
*
            do 40 md=npesub(kd-1),npesub(kd)-1
*
               if (md.eq.minb) then
                  write (14+5*npesum+npenum(md),9001) number
                  write (14+5*npesum+npenum(md),9011) 1,
     $                 npeloc(md),inset(2,jd),kd
               else if (md.ne.minb) then
                  write (14+5*npesum+npenum(md),9001) number
                  write (14+5*npesum+npenum(md),9011) -1,
     $                 npeloc(md),inset(2,jd),kd
               end if
 40         continue
*   
 20      continue
*     
 10   continue
*     
 9001 format(i8)
 9011 format(4i8)
      return
      end

         




