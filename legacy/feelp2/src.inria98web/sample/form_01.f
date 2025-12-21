      subroutine form_1(u,v,....)
c
      common /feel_geo/numd,numnp
      common /feel_dom/numes,numbd,nelems(MAXEG),nbonds(MAXBD)
      common /feel_io /iunit_inp,iunit_out,iunit_scr,num_files
      common /feel_dim/nloc_last,nloc_fem,nloc_elem
      data   idble / 2 /
c -----------------------------
