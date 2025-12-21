;-------------------------------------
; LISPプログラムの読み込み            
;-------------------------------------
(load "/usr/feel/feel_p2/src/lisp_exec/feel-package.l")
;-------------------------------------
;==================================================
; solve文 No.1
;==================================================
;---------------------
; SolveElement 1-1
;---------------------
(setq *test-funcs* '(( Q1_1 Q1_2 Q1_3 Q1_4)
) )
(setq *coff-vect* '(M1 M2 M3 M4  ) )
(setq u '(+  (* M1 Q1_1) (* M2 Q1_2) (* M3 Q1_3) (* M4 Q1_4) ) )
(setq uu '(+ (* uu_1 Q1plus_1) (* uu_2 Q1plus_2) (* uu_3 Q1plus_3) (* uu_4 Q1plus_4) (* uu_5 Q1plus_5) (* uu_6 Q1plus_6) ) )
(setq *eval-vars* '( u uu) )
(setq *fem-funcs* 
  '(Q1_1 Q1_2 Q1_3 Q1_4 
    Q1_1 Q1_2 Q1_3 Q1_4 
    Q1plus_1 Q1plus_2 Q1plus_3 Q1plus_4 Q1plus_5 Q1plus_6 
     ) )
(setq Q1_1 (minus-convert '( * ( * ( -  1  r )( -  1  s )) 0.25 ) ) )
(setq Q1_2 (minus-convert '( * ( * ( +  1  r )( -  1  s )) 0.25 ) ) )
(setq Q1_3 (minus-convert '( * ( * ( +  1  r )( +  1  s )) 0.25 ) ) )
(setq Q1_4 (minus-convert '( * ( * ( -  1  r )( +  1  s )) 0.25 ) ) )
(setq Q1_1 (minus-convert '( * ( * ( -  1  r )( -  1  s )) 0.25 ) ) )
(setq Q1_2 (minus-convert '( * ( * ( +  1  r )( -  1  s )) 0.25 ) ) )
(setq Q1_3 (minus-convert '( * ( * ( +  1  r )( +  1  s )) 0.25 ) ) )
(setq Q1_4 (minus-convert '( * ( * ( -  1  r )( +  1  s )) 0.25 ) ) )
(setq Q1plus_1 (minus-convert '( * ( * ( -  1  r )( -  1  s )) 0.25 ) ) )
(setq Q1plus_2 (minus-convert '( * ( * ( +  1  r )( -  1  s )) 0.25 ) ) )
(setq Q1plus_3 (minus-convert '( * ( * ( +  1  r )( +  1  s )) 0.25 ) ) )
(setq Q1plus_4 (minus-convert '( * ( * ( -  1  r )( +  1  s )) 0.25 ) ) )
(setq Q1plus_5 (minus-convert '( *  s  s ) ) )
(setq Q1plus_6 (minus-convert '( *  r  r ) ) )
(setq *shape-funcs* '(Q1_1 Q1_2 Q1_3 Q1_4 )  )
;----------------------
; 積分法  1-1-1
;----------------------
(setq *solve-no*    1)
(setq *elem-no*     1)
(setq *integral-no* 1)
(setq *quad-method* 'gauss2x2)
(setq *fem-weak-eq* '(( + ( - ( *  u  $ )( *  uu  $ ))( *  dt ( + ( * ( dx  u )( dx  $ ))( * ( dy  u )( dy  $ )))))
)  )
(setq *quad-vars* nil)
(setq *eval-smbl* nil)
(setq *dimension* 2)
(make-linear-weak)
(make-num-integral)
