      program feel
c-------------------------------------------------
c  FEEL P2.0 Finite Element Equation Language
c            Copyright(C) 1992 NEC Corporation
c
c  Creater   Hidehiro Fujio
c  Date      Thu Jun 10 11:30:46 JST 1993
c-------------------------------------------------
      implicit real*8 (a-h,o-z)
c
c------------------------ [label oimo           ( 34)]
 100     continue
c
c------------------------ [FEM let sentence     ( 35)]
      do 1000 ip=1,np
      p_(ip) = a_*(px(ip))
1000  continue
c
c------------------------ [let sentence         ( 36)]
      b_ = c_*b_
c
c------------------------ [goto oimo            ( 37)]
      goto 100
c
c------------------------ [goto kkk             ( 38)]
      goto 9999
c
      end
