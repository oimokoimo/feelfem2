      subroutine exvalp(kld,vdimp,kloce,vcore,vprne,vpree,kne,vfe,vke,
     $  vkgs,vkgd,vfg,vcorg,kdlnc,kneq,vres,vdle,vdlg,vmgs,vmgd,
     $  vec,vlamb,vlam1,vkss,vmss,v1,vx,neq,nss)
c=====================================================================
c     to execute block 'valp'
c     to compute eigenvalues and eigenvectors by subspace
c     iteration        exva   7
c     (if  nvalp.eq.1  inverse iteration method)
c=====================================================================
      implicit real*8 (a-h,o-z)
      common /asse/nsym,nkg,nke,ndle
      common /valp/niter,nmdiag,epslb,shift,nss1,nswm,toljac,nvalp
      common /es/m,mr,mp
      dimension kld(1),vdimp(1),kloce(1),vcore(1),vprne(1),vpree(1),
     $  kne(1),vfe(1),vke(1),vkgs(1),vkgd(1),vfg(1),vcorg(1),kdlnc(1),
     $  kneq(1),vres(1),vdle(1),vdlg(1),vmgs(1),vmgd(1),vec(neq,1),
     $  vlamb(1),vlam1(1),vkss(1),vmss(1),v1(1),vx(nss,1)
      data zero/0.0d0/,un/1.0d0/,grand/1.0D32/
      abs(x)=dabs(x)
c---------------------------------------------------------------------
c
c-------  preliminary computations
c
c-------  assemble kg and mg
      call askg(kld,

