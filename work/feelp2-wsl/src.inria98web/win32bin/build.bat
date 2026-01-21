cl /c o.c
cl /c yywrap.c
cl /c debug_start.c
cl /c dospending.c
cd ..\yacc           
nmake -f yacc.mk
cd ..\element        
nmake -f element.mk
cd ..\mesh_comp      
nmake -f mesh_comp.mk
cd ..\var_comp       
nmake -f var_comp.mk
cd ..\system         
nmake -f system.mk
cd ..\main           
nmake -f main.mk
cd ..\makefort77     
nmake -f makefort77.mk
cd ..\parallel       
nmake -f parallel.mk
cd ..\check          
nmake -f check.mk
cd ..\fort77lib      
nmake -f fort77lib.mk
cd ..\scheme_comp    
nmake -f scheme_comp.mk
cd ..\solve_comp     
nmake -f solve_comp.mk
cd ..\solve_fort77   
nmake -f solve_fort77.mk
cd ..\lisp_util      
nmake -f lisp_util.mk
cd ..\lisp_c         
nmake -f lisp_c.mk
cd ..\mesh_exec      
nmake -f mesh_exec.mk
cd ..\mesh_bamg_exec 
nmake -f mesh_bamg_exec.mk
cd ..\mesh_exec_1D   
nmake -f mesh_exec_1D.mk
cd ..\quadrature     
nmake -f quadrature.mk
cd ..\lisp_lib       
nmake -f lisp_lib.mk
cd ..\let            
nmake -f let.mk
cd ..\geom2d         
nmake -f geom2d.mk
cd ..\parallel_lib   
nmake -f parallel_lib.mk
cd ..\win32bin


