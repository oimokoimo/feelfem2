      subroutine elem1_2(x,y,ielem,matno,nelem,np,
     $                   fem_a,fem_b,...,ew_a,..,sc_a,... )
*
*  solve文番号1   solve_element番号2 の要素剛性プログラム
*
*
*  目的  solveXXサブルーチンから呼び出される
*        全体マトリックスに担当する部分を足し込む
*
*
*
*      elemXX_YY         
*        |
*        | ---  esetXX_YY   数値積分法に用いる変数の代入
*        |
*        || 要素に関するループ
*        ||
*        ||
*        ||- ecalXX_YY 要素小行列の計算プログラム
*        ||
*        ||  全体行列への足し込み(solverによって異なる)
*        |
*        |return
*        |
*
      implicit real*8 (a-h,o-z)

      parameter (NDF  =   15)  要素内のdegree of freedom
      
      parameter (NPGa = XXXX)  一番目の数値積分法の積分点数
      parameter (NPGb = XXXX)  二番目の数値積分法の積分点数
                    ....................

      dimension x(*),y(*)
      dimension ielem(np,nelem)   np は要素内節点数 nelem は要素数
      dimension fem_a(*),fem_b(*) fem変数
      dimension ew_ea(np_ewea,nelem),ew_xx(np_ewxx,nelem)   ewise変数(domain)
      
      integer sc_idat1      スカラー変数  整数
      real*8  sc_kdjfksj    スカラー変数  実数

      dimension     ienp(NDF)  小行列の各行(列)に対応する要素内局所節点番号
      dimension     iedp(NDF)  小行列の各行(列)の要素内局所節点番号からの
                               destination

      dimension     ikp(NDF)   対応する全体MATRIXの位置

      common /em1_2a/gx_a(NPGa),gy_a(NPGa),w_a(NPGa),    第一の積分点
     $                  ........................,
     $              q1_1a(NPGa), 積分点毎の基底関数値
     $              q1_1ax(NPGa),q1_1ay(NPGa)  などなど 
     $              q1_3ax(NPGa)

      common /em1_2/ea(NDF,NDF),eb(NDF)              要素小行列格納場所

      data   /ienp/ 1 ,2 , 3, 4
      data   /iedp/ 0 ,0 , 0, 0
...
      call est1_2a  数値積分法aに関するconstant定数の初期化領域はCOMMONで渡す
      call est1_2b  数値積分法bに関するconstant定数の初期化領域はCOMMONで渡す

      do 100 i=1,nelem
         
         call ecal1_2(x1,y1,x2,y2,x3,y3,....,fem_u_1,fem_u_2,
                      ew_a_1,ew_a_2,ew_a_3,....)

         do 200 j=1,np
           ikp(j) = IPD(ielem(ienp(j),i)) + iedp(j)
 200     continue
 
         do 300 j=1,np
            jp = ikp(j)
            do 400 k=1,j-1             /*  k < j 下三角部分*/ 
               kp = ikp(k)
               lp = KLD(jp+1)-jp+kp
               VKGI(lp) = VKGI(lp) + ea(j,k)
 400        continue

            VKGD(jp) = VKGD(jp) + ea(j,j)   対角成分

            do 500 k=j+1,np
               kp = ikp(k)
               lp = KLD(kp+1)-kp+jp
               VKGS(lp) = VKGS(lp) + ea(j,k)
 500        continue

 300     continue

 100  continue

      return
      end


         


