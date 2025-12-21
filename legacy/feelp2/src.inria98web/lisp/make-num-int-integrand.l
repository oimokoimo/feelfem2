;--------------------------------------------------------------------------
;   feel p2  Finite Element Simulation Language Prototype Version 2
;            ~      ~       ~          ~
;      File:   make-num-int-integrand.l
;      Date:   1993/11/19
;   
;   Purpose:   *fem-integrand*から、数値積分用のプログラム生成補助データ作成
;              
;              
;              *fem-funcs* に関する取り扱い
;              
;              微分演算子付き (dx Q1_4)    qQ1_4_x_##p     
;              
;----------------------------------------------------------------------------
;              以下の変更はＣの処理で行う
;       
;              *fem-funcs* に関する取り扱い
;
;              そのまま        Q1_4     → qQ1_4_##(itp)   ##は数値積分番号
;
;              *quad_var* に関する取り扱い
;              
;              A1                       → qA1_##(itp)      ##は数値積分番号
;              
; Arguments: 
; Variables: 
;   Symbols:          
; functions: 
;--------------------------------------------------------------------------
(defun make-num-integrand