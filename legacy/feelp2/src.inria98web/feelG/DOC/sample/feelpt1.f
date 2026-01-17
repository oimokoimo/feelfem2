      subroutine feelpt1(feel,x,fem_u,fem_ux)
c ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
c     feel p2 fort77 program
c     Copyright(C) NEC Corporation 1993
c ======================================
c ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
c Date: 1994年05月23日 (月) 11時17分21秒 JST
c User: Naoki Okamoto (Okapy)
c ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
      implicit real*8 (a-h,o-z)
c --------------------------------------------------------------------
      parameter (MAX_FEEL = 400000)
      parameter (MAX_DOMAIN = 10)
      parameter (MAX_EDATSET = 38)
      parameter (MAX_NODESET = 20)
      parameter (MAX_NUMSET = 20)
      parameter (MAX_EWISE  = 20)
      parameter (MAX_IP    = 4)
      parameter (MAX_SOLVE = 2)
c --------------------------------------------------------------------
*
       parameter (NSETNO = 1)
*
      real*4 feel(*)
      dimension x(*)
      dimension fem_u(*)
      dimension fem_ux(*)
c --------------------------------------------------------------------
      common /feel_geo/ndim,npmax,ndomain,nedat,nnodeset,nnumdat,nip
      common /feel_ctl/mode_ex,mode_output,max_heap
      common /feel_var/np_work,np_x,np_y,np_z,nvars_fem,nvars_ewise,
     &                 np_fem,np_ewise,np_heap
      common /feel_fil/io_in,io_tmp,io_out,io_stderr,
     &                 io_edat,io_node,io_num,io_fem
      common /feel_dat/n_edat(MAX_EDATSET,3),
     &                 n_nset(MAX_NODESET,2),n_num(MAX_NUMSET),
     &                 n_ewise(MAX_EWISE,2),n_nodeno(MAX_IP)
      common /feel_sol/n_sstat(MAX_SOLVE)
c --------------------------------------------------------------------
      np_push = np_work
*
      nodes = n_nset(NSETNO,1)
      np    = n_nset(NSETNO,2)
*
      call f_alloc(np_inset,'feelpt1(INSET)',nodes*np,0)
*
      iunit = NSETNO + io_node -1
      call get_inset(iunit,feel(np_inset),nodes,np)
*
      call coplot1(io_tmp,feel(np_inset),nodes,np,x,fem_u,fem_ux)
*
      np_work = np_push
*
      return
      end
      subroutine coplot1(io_tmp,inset,nodes,np,x,fem_u,fem_ux)
c ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
c     feel p2 fort77 program
c     Copyright(C) NEC Corporation 1993
c ======================================
c ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
c Date: 1994年05月23日 (月) 11時17分21秒 JST
c User: Naoki Okamoto (Okapy)
c ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
      implicit real*8 (a-h,o-z)
      dimension inset(np,nodes)
*
      dimension x(*)
      dimension fem_u(*)
      dimension fem_ux(*)
*
      dimension PX(33,2)
      dimension PY(33,2)
*
      dimension SX(33,2)
      dimension SY(33,2)
*
      dimension PPX(33)
      dimension PPY(33)
*
      dimension NXDIV(10)
      dimension NYDIV(10)
      dimension PXMIN(10)
      dimension PXMAX(10)
      dimension PYMIN(10)
      dimension PYMAX(10)
      dimension NAXIS(10)
c 
c --------------------------------------------------------------------
c
      io_no = io_tmp + 1
      open(unit=io_no,file='temp.dat')
*
*
      do 100 i=1,nodes
       ip = inset(1,i)
*
       write(io_no,110) x(ip),fem_u(ip),fem_ux(ip)
*
100   continue
110   format(3(F12.5,1X))
*
      IWD=0
      IWX=0
      IWY=0
      IWW=600
      IWH=600
      XMIN=0.0
      YMIN=0.0
      XMAX=1.0
      YMAX=1.0
      IGRY=0
      call FEEL_XINIT(IWX,IWY,IWW,IWH,IWD,XMIN,XMAX,YMIN,YMAX,IGRY)
      call FEEL_TITLE('1 feel xy graph[1]',IWD)
*
      NLINE=2
      IRGF=0
      NSTEP=2
      PXMIN(1)=0.0
      PXMIN(2)=0.0
      PYMIN(1)=0.0
      PYMIN(2)=0.0
      PXMAX(1)=1.0
      PXMAX(2)=1.0
      PYMAX(1)=1000.0
      PYMAX(2)=1.0
      NXDIV(1)=5
      NXDIV(2)=5
      NYDIV(1)=5
      NYDIV(2)=5
      NAXIS(1)=1
      NAXIS(2)=2
      NYAS=1
*
      do 200 i=1,nodes
        ip = inset(1,i)
        PX(i,1)=x(ip)
        PY(i,1)=fem_u(ip)
        PX(i,2)=x(ip)
        PY(i,2)=fem_ux(ip)
200   continue
*
      CALL FEEL_XYGRAPH(NLINE,NODES,PX,PY,SX,SY,PPX,PPY,
     $PXMIN,PXMAX,PYMIN,PYMAX,NXDIV,NYDIV,NAXIS,NYAS,NSTEP,IRGF,IWD)
*
      return
      end
