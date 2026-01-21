/*
 *  プロセスシミュレーションテスト
 *
 *  
 *
 */ 

(setq *fem-weak-eq* 
      '(
	( (+ (* e  (dx p)(dx $)) (* e (dy p)(dy $))
	     (* ni (exp (* -1 q T p)))
	     (* ni (exp (*  q T p)))))
	)
      )
