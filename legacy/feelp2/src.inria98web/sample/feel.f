      program sample_main
c ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
c     feel p2 fort77 program                OOOOO  OOOOO  OOOOO  O
c     Copyright(C) NEC Corporation 1993     O      O      O      O
c ======================================    OOOOO  OOOO   OOOO   O
c                                           O      O      O      O
c Purpose :                                 O      OOOOO  OOOOO  OOOOO
c ---------                                 --------------------------
c     Sample Program
c
c Parameters of Entrance
c ------------------------
c
c ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
c Date :   1993/02/11  14:29
c ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
      implicit real*8 (a-h,o-z)
c -----------------------------
      parameter (MAX   = 100000)
      parameter (MAXEG = 20    )
      parameter (MAXBD = 20    )
c -----------------------------
      real*4   feel
c -----------------------------
      common feel(MAX)
c -----------------------------
      common /feel_geo/numd,numnp
      common /feel_dom/nume,numbd,nelems(MAXEG),nbonds(MAXBD)
      common /feel_io /iunit_inp,iunit_out,iunit_scr,num_files
      common /feel_dim/nloc_last,nloc_fem,nloc_elem
      data   idble / 2 /
c -----------------------------
c  //////////////////////////////////////////////////////////////////
c     read data file
c  --------------------------
      call fileset
      call inpdat
c------------------------------
c  //////////////////////////////////////////////////////////////////
c     allocate FEM variables                                         
c  --------------------------
c
c     FEM variables
c     -------------
      NV_v = nloc_last
      nloc_last = nloc_last + numd * idble
      NV_u = nloc_last
      nloc_last = nloc_last + numd * idble
      NV_p = nloc_last
      nloc_last = nloc_last + numd * idble
c
c     Element wise variables
c     ----------------------
      NV_myu = nloc_last
      nloc_last = nlock_last + 
c
c  //////////////////////////////////////////////////////////////////
c     Scheme 
c  ----------
 1    continue
c  //////////////////////////////////////////////////////////////////
c     
c  --------------------------
      stop
      end





