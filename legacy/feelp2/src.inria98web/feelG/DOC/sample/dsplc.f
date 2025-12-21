      subroutine dsplc( feel, x0, y0, x1, y1, u, v, s, fact)
c ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
c     feel p2 fort77 program
c     Copyright(C) NEC Corporation 1993
c ======================================
c ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
c Date: 1994年08月30日 (火) 11時33分45秒 JST
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
      parameter (MAX_IP    = 8)
      parameter (MAX_SOLVE = 5)
c --------------------------------------------------------------------
      real*4 feel(*)
      dimension x0(*),y0(*)
      dimension x1(*),y1(*)
      dimension u(*),v(*)
      dimension s(*)
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
      dimension IC(2)
c --------------------------------------------------------------------
      np_push = np_work
* 都合によりedatは １番目を使用
      iedat_no =1
      neelem = n_edat(iedat_no,1)
      nenode = n_edat(iedat_no,2)
      call f_alloc(np_ielem,'contour_1(ielem)',neelem * nenode,0)
      call f_alloc(np_matno,'contour_1(matno)',neelem ,0)
      iunit = iedat_no + io_edat - 1
      call get_ielem(iunit,feel(np_ielem),feel(np_matno),neelem,nenode)
      np_work=np_push
*
* Window ID
      IWD = 0
* Window Position
      IWX = 0
      IWY = 0
* Window Size
      IWW = 800
      IWH = 500
* Gray scale 0=color 1=gray
      IGRY = 0
*
      call EDATRANGE(x0,y0,feel(np_ielem),neelem,nenode,XMIN,XMAX,YMIN,
     $YMAX)
      call FEEL_XINIT(IWX,IWY,IWW,IWH,IWD,XMIN,XMAX,YMIN,YMAX,IGRY)
      call VCLW(IWD)
*
      IC(1) = 1
      IC(2) = 10
      ISL   = 1
      ICT   = 1
      IDV   = 20
      ICS   = 0
      SMIN  = 3.0
      SMAX  = 8.0
      ITP   = 1
      ICM   = 0
      ICB   = 1
      NCBX  = 10
      NCBY  = 10
      ID    = 3
*
      call FEEL_DSPLC(npmax,neelem,nenode,feel(np_ielem),
     $x0,y0,x1,y1,u,v,fact,s,
     $IC,ISL,ICT,IDV,ICS,ITP,ICM,SMIN,SMAX,
     $ICB,NCBX,NCBY,ID,IWD)
*
      call FEEL_TITLE('1 feel displacement[1]',IWD)
      call report('contour[tau] @feel:64')
*
      return
      end

