      subroutine est1_2(
*
*  solve文番号 1   solve element番号 2 の数値積分初期化ルーチン
*
      common //
      
      parameter (NPG1 = XXXX)  一番目の数値積分法の積分点数
      parameter (NPG2 = XXXX)  二番目の数値積分法の積分点数

      parameter (co_pm = 

      dimension ielem(np,nelem)   np は要素内節点数 nelem は要素数
      dimension fem_a(*),fem_b(*) fem変数
      dimension ew_ea(np_ewea,nelem),ew_xx(np_ewxx,nelem)   ewise変数(domain)
     
      parameter (NPGa = XXXX)  一番目の数値積分法の積分点数
      parameter (NPGb = XXXX)  二番目の数値積分法の積分点数
                    ....................

      dimension x(*),y(*)
      dimension ielem(np,nelem)   np は要素内節点数 nelem は要素数
      dimension fem_a(*),fem_b(*) fem変数
      dimension ew_ea(np_ewea,nelem),ew_xx(np_ewxx,nelem)   ewise変数(domain)
      
      dimension     ikp(NDF)   対応する全体MATRIXの位置

      common /em1_2a/gx_a(NPGa),gy_a(NPGa),w_a(NPGa),    第一の積分点
     $                  ........................,
     $              q1_a(NPGa), 積分点毎の基底関数値
     $              q1_ax(NPGa),q1_ay(NPGa)  などなど 
     $              q1_bx(NPGa),coa_XXX  constクラスの値

      common /em1_2b/gx_b(NPGb),gy_b(NPGb) ...


数値積分法aに対して必要な値の設定

      基底関数、形状変換関数の各積分点での必要な値の代入
      x微分、y微分など
      
      の設定

      const変数、積分点座標はここで

      ■LISPプログラムの出力 
      q1_3a(1) = .....
      
      基底関数名 q1の 局所要素節点番号に対応する節点番号が3の
      この数値積分法が定める1番目の積分点での値の代入

数値積分法bに対して必要な値の設定

      基底関数、形状変換関数の各積分点座標、そこでの必要な値の代入
      x微分、y微分など
      
      の設定
      constant 設定の計算
      q1_1a(1) = gx_a(1)  * .....

      ■LISPプログラムの出力
      
      return
      end
