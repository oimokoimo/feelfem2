      subroutine report( cha )
      implicit real*8 (a-h,o-z)
      character cha*(*)
*
c --------------------------------------------------------------------
      parameter (MAX_FEEL = 10000000)
      parameter (MAX_DOMAIN = 10)
      parameter (MAX_EDATSET = 38)
      parameter (MAX_NODESET = 20)
      parameter (MAX_NUMSET = 10)
      parameter (MAX_EWISE  = 20)
      parameter (MAX_IP    = 5)
      parameter (MAX_SOLVE = 1)
c --------------------------------------------------------------------
*
c --------------------------------------------------------------------
      common /feel_geo/ndim,npmax,ndomain,nedat,nnodeset,nnumdat,nip
      common /feel_ctl/mode_ex,mode_output,max_heap
      common /feel_var/np_x,np_y,np_z,nvars_fem,nvars_ewise,
     &                 np_fem,np_ewise,np_heap
      common /feel_fil/io_in,io_tmp,io_out,io_stderr,
     &                 io_edat,io_node,io_num,io_fem
      common /feel_dat/n_edat(MAX_EDATSET,3),
     &                 n_nset(MAX_NODESET,2),n_num(MAX_NUMSET),
     &                 n_ewise(MAX_EWISE,2),n_nodeno(MAX_IP)
      common /feel_sol/n_sstat(MAX_SOLVE),n_smaxp(MAX_SOLVE)
c --------------------------------------------------------------------
*
      data timlog/0.0d0/
      save timlog
c
      tim = erapstime()
      write(io_out,900) tim ,tim - timlog , cha

 900  format(1x,f11.3,1x,'   [',f11.3,'] :  ',a)
      timlog = tim
      return
      end
      subroutine rep_head
      character date*17
*
c --------------------------------------------------------------------
      parameter (MAX_FEEL = 10000000)
      parameter (MAX_DOMAIN = 10)
      parameter (MAX_EDATSET = 38)
      parameter (MAX_NODESET = 20)
      parameter (MAX_NUMSET = 10)
      parameter (MAX_EWISE  = 20)
      parameter (MAX_IP    = 5)
      parameter (MAX_SOLVE = 1)
c --------------------------------------------------------------------
*
c --------------------------------------------------------------------
      common /feel_geo/ndim,npmax,ndomain,nedat,nnodeset,nnumdat,nip
      common /feel_ctl/mode_ex,mode_output,max_heap
      common /feel_var/np_x,np_y,np_z,nvars_fem,nvars_ewise,
     &                 np_fem,np_ewise,np_heap
      common /feel_fil/io_in,io_tmp,io_out,io_stderr,
     &                 io_edat,io_node,io_num,io_fem
      common /feel_dat/n_edat(MAX_EDATSET,3),
     &                 n_nset(MAX_NODESET,2),n_num(MAX_NUMSET),
     &                 n_ewise(MAX_EWISE,2),n_nodeno(MAX_IP)
      common /feel_sol/n_sstat(MAX_SOLVE),n_smaxp(MAX_SOLVE)
c --------------------------------------------------------------------
*
      write(io_out,800)
 800  format('FEEL P2 (Ver 0.00) PROCEDURE REPORT  [NEC Corporation 1993
     $-1997]')
      call getdate(date)

      write(io_out,801) date
 801  format('                             START   ',a16)

      

      write(io_out,*)
      write(io_out,900)
      write(io_out,910)
      write(io_out,920)
 900  format('   Sum-up         Sub-Proc        Proc STATUS')
 910  format('   CPU time       CPU time        REPORT     ')
 920  format('-------------   -------------    -------------------------
     $----------')
      return
      end
      subroutine rep_var
*
c --------------------------------------------------------------------
      parameter (MAX_FEEL = 10000000)
      parameter (MAX_DOMAIN = 10)
      parameter (MAX_EDATSET = 38)
      parameter (MAX_NODESET = 20)
      parameter (MAX_NUMSET = 10)
      parameter (MAX_EWISE  = 20)
      parameter (MAX_IP    = 5)
      parameter (MAX_SOLVE = 1)
c --------------------------------------------------------------------
*
c --------------------------------------------------------------------
      common /feel_geo/ndim,npmax,ndomain,nedat,nnodeset,nnumdat,nip
      common /feel_ctl/mode_ex,mode_output,max_heap
      common /feel_var/np_x,np_y,np_z,nvars_fem,nvars_ewise,
     &                 np_fem,np_ewise,np_heap
      common /feel_fil/io_in,io_tmp,io_out,io_stderr,
     &                 io_edat,io_node,io_num,io_fem
      common /feel_dat/n_edat(MAX_EDATSET,3),
     &                 n_nset(MAX_NODESET,2),n_num(MAX_NUMSET),
     &                 n_ewise(MAX_EWISE,2),n_nodeno(MAX_IP)
      common /feel_sol/n_sstat(MAX_SOLVE),n_smaxp(MAX_SOLVE)
c --------------------------------------------------------------------
*    
* npmax
      write(io_out,200) npmax
* xyz
      write(io_out,201) ndim,np_x,np_fem-1
* fem
      if(nvars_fem .eq. 0) then
         write(io_out,202) 
      else
         write(io_out,203) nvars_fem,np_fem,np_ewise-1
      endif
* ew
      if(nvars_ewise .eq. 0) then
         write(io_out,204)
      else
         write(io_out,205) nvars_ewise,np_ewise,
     $                     np_work_get_falloc()-1
       endif
      write(io_out,206) (np_work_get_falloc()-1)*2
*
 200  format('                              :  NODES   ',i5)
 201  format('                              :  DIMENSION  ',i2,' ',i7,'-
     $',i7)
 202  format('                              :  NO FEM   VARIABLE')
 203  format('                              :  FEM VARS   ',i2,' ',i7,'-
     $',i7)
 204  format('                              :  NO EWISE VARIABLE')
 205  format('                              :  EWISE VARS ',i2,' ',i7,'-
     $',i7)
 206  format('                              :  SPACE FOR VARS',i7,'bytes
     $')
      return
      end
      subroutine rep_msize(neq,ncof)
c --------------------------------------------------------------------
      parameter (MAX_FEEL = 10000000)
      parameter (MAX_DOMAIN = 10)
      parameter (MAX_EDATSET = 38)
      parameter (MAX_NODESET = 20)
      parameter (MAX_NUMSET = 10)
      parameter (MAX_EWISE  = 20)
      parameter (MAX_IP    = 5)
      parameter (MAX_SOLVE = 1)
c --------------------------------------------------------------------
*
c --------------------------------------------------------------------
      common /feel_geo/ndim,npmax,ndomain,nedat,nnodeset,nnumdat,nip
      common /feel_ctl/mode_ex,mode_output,max_heap
      common /feel_var/np_x,np_y,np_z,nvars_fem,nvars_ewise,
     &                 np_fem,np_ewise,np_heap
      common /feel_fil/io_in,io_tmp,io_out,io_stderr,
     &                 io_edat,io_node,io_num,io_fem
      common /feel_dat/n_edat(MAX_EDATSET,3),
     &                 n_nset(MAX_NODESET,2),n_num(MAX_NUMSET),
     &                 n_ewise(MAX_EWISE,2),n_nodeno(MAX_IP)
      common /feel_sol/n_sstat(MAX_SOLVE),n_smaxp(MAX_SOLVE)
c --------------------------------------------------------------------

      write(io_out,200) neq
      write(io_out,210) ncof
      write(io_out,220) np_work_get_falloc(),
     $                  np_work_get_falloc()*4

 200  format('                              :  NEQ      ',i8)
 210  format('                              :  NCOF     ',i8)
 220  format('                              :  HEAP MAX ',i8,'(',i9,'byt
     $es)')
*
      return
      end
      subroutine rep_CG(iter,zansa)
      real*8 zansa
c --------------------------------------------------------------------
      parameter (MAX_FEEL = 10000000)
      parameter (MAX_DOMAIN = 10)
      parameter (MAX_EDATSET = 38)
      parameter (MAX_NODESET = 20)
      parameter (MAX_NUMSET = 10)
      parameter (MAX_EWISE  = 20)
      parameter (MAX_IP    = 5)
      parameter (MAX_SOLVE = 1)
c --------------------------------------------------------------------
*
c --------------------------------------------------------------------
      common /feel_geo/ndim,npmax,ndomain,nedat,nnodeset,nnumdat,nip
      common /feel_ctl/mode_ex,mode_output,max_heap
      common /feel_var/np_x,np_y,np_z,nvars_fem,nvars_ewise,
     &                 np_fem,np_ewise,np_heap
      common /feel_fil/io_in,io_tmp,io_out,io_stderr,
     &                 io_edat,io_node,io_num,io_fem
      common /feel_dat/n_edat(MAX_EDATSET,3),
     &                 n_nset(MAX_NODESET,2),n_num(MAX_NUMSET),
     &                 n_ewise(MAX_EWISE,2),n_nodeno(MAX_IP)
      common /feel_sol/n_sstat(MAX_SOLVE),n_smaxp(MAX_SOLVE)
c --------------------------------------------------------------------

      write(io_out,200) iter 
      write(io_out,210) zansa

 200  format('                              :  ITERATION ',i8)
 210  format('                              :  RESIDUAL  ',E15.7)
*
      return
      end
      subroutine rep_non(NITER)
c --------------------------------------------------------------------
      parameter (MAX_FEEL = 10000000)
      parameter (MAX_DOMAIN = 10)
      parameter (MAX_EDATSET = 38)
      parameter (MAX_NODESET = 20)
      parameter (MAX_NUMSET = 10)
      parameter (MAX_EWISE  = 20)
      parameter (MAX_IP    = 5)
      parameter (MAX_SOLVE = 1)
c --------------------------------------------------------------------
*
c --------------------------------------------------------------------
      common /feel_geo/ndim,npmax,ndomain,nedat,nnodeset,nnumdat,nip
      common /feel_ctl/mode_ex,mode_output,max_heap
      common /feel_var/np_x,np_y,np_z,nvars_fem,nvars_ewise,
     &                 np_fem,np_ewise,np_heap
      common /feel_fil/io_in,io_tmp,io_out,io_stderr,
     &                 io_edat,io_node,io_num,io_fem
      common /feel_dat/n_edat(MAX_EDATSET,3),
     &                 n_nset(MAX_NODESET,2),n_num(MAX_NUMSET),
     &                 n_ewise(MAX_EWISE,2),n_nodeno(MAX_IP)
      common /feel_sol/n_sstat(MAX_SOLVE),n_smaxp(MAX_SOLVE)
c --------------------------------------------------------------------

      write(io_out,200) NITER
 200  format('                              :  ITERATION',i8)
*
      return
      end
      subroutine rep_last
      implicit real*8 (a-h,o-z)
      character date*17
c --------------------------------------------------------------------
      parameter (MAX_FEEL = 10000000)
      parameter (MAX_DOMAIN = 10)
      parameter (MAX_EDATSET = 38)
      parameter (MAX_NODESET = 20)
      parameter (MAX_NUMSET = 10)
      parameter (MAX_EWISE  = 20)
      parameter (MAX_IP    = 5)
      parameter (MAX_SOLVE = 1)
c --------------------------------------------------------------------
*
c --------------------------------------------------------------------
      common /feel_geo/ndim,npmax,ndomain,nedat,nnodeset,nnumdat,nip
      common /feel_ctl/mode_ex,mode_output,max_heap
      common /feel_var/np_x,np_y,np_z,nvars_fem,nvars_ewise,
     &                 np_fem,np_ewise,np_heap
      common /feel_fil/io_in,io_tmp,io_out,io_stderr,
     &                 io_edat,io_node,io_num,io_fem
      common /feel_dat/n_edat(MAX_EDATSET,3),
     &                 n_nset(MAX_NODESET,2),n_num(MAX_NUMSET),
     &                 n_ewise(MAX_EWISE,2),n_nodeno(MAX_IP)
      common /feel_sol/n_sstat(MAX_SOLVE),n_smaxp(MAX_SOLVE)
c --------------------------------------------------------------------
      tim  = erapstime()
      call getdate(date)
      call f_alloc_get_info(idummy,max_heap)
*
      write(io_out,100)
      write(io_out,110) tim
      write(io_out,120) max_heap
      write(io_out,130) date
      write(io_out,100)
*
      close(unit=io_out)
*
      return
*
 100  format('==========================================================
     $==========')
 110  format(' FEEL P2 PROCESS TERMINATE    TOTAL CPU TIME  ',F11.3,' se
     $conds')
 120  format('                              MAX ARRAY SIZE  ',I11,' word
     $s')
 130  format('                              FINISH DATE      ',A16)
*
      end



