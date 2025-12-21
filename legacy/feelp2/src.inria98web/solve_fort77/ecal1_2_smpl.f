      subroutine ecal1_2(x1,y1,x2,y2,x3,y3,... fem_u_1,fem_u_2,fem_u_3,
     $                   fem_u_4,... ,ew_a_1,ew_a_2,.... )

      implicit real*8 (a-h,o-z)
      paramter        (NDF=xx)
      ....
     
      dimension rj(2,2)   三次元は3x3マトリックス
      dimension rji(2,2)  三次元は3x3

      common /em1_2/ ea(NDF,NDF) , eb(NDF)

      common /em1_2_1/ gx_1(NPG1)   , gy_1(NPG
      /* 以下、形状変換関数が指定されていて、ヤコビアンを計算する
         必要がある場合
       */
c
c     要素小行列式の記憶領域のクリア
c
       do 100 i=1,NDF
          do 110 j=1,NDF
             ea(i,j) = 0.0d0
 110      continue
          eb(i)=0.0d0
 100   continue
c
c  各積分法毎に ea,eb配列に足し込む

       第一の積分法の展開

       do 1100 intp = 1,NPGa
          
       rj(1,1)=0.0d0     /* 各点毎のヤコビアン計算
       rj(1,2)=0.0d0        定数の場合は  別途考慮！
       rj(2,1)=0.0d0
       rj(2,2)=0.0d0
        
       積分点 intp でのJacobian の計算
       
       rj(1,1) = qx1a(intp)*x1+qs(intp)*x2+qshape_3ax(intp)*x3 +
     &           qx4a(intp)*x4 ...
       rj(1,2) = qshap_1x(1)*y1 + qshape_1x(2)*y2 + qshape_1x(...
     &          .........

       rj(2,1) = qshape_1ay(1)*y1 + 
                       ^^^     ^^^

       det = rj(1,1)*rj(2,2)-rj(1,2)*rj(2,1)
       rji(1,1) =  ri(2,2)/det
       rji(1,2) = -ri(1,2)/det
       rji(2,1) = -ri(2,1)/det
       rji(2,2) =  ri(1,1)/det

       計算時に必要な導関数の計算(積分点itpでの)

       q1_1_xp = q1_1_x(itp) *  rji(1,1) * ..... 

       q1_1_yp = 

       q1_2_xp = q1_2_x(itp) * 
       
       weight  = det * w_1(itp)
       
       ea(1,1) = ea(1,1) + 
       ( q1_1_xp * ...  .. ... ... .... ... ...) * weight
       ea(1,2) = ea(1,2) + 
       ( qkk ..............                    ) * weight
       ....

       q1_1  (dx q1_1)

       eb(1) = eb(1) + ( .................  ) * weight

       eb(n) = eb(n) + ( .................  ) * weight
       
 1010  continue


       /* 第二の積分法に対する小行列計算 */

       ..............


       /* 第三の積分法に対する小行列計算 */

       return
       end

