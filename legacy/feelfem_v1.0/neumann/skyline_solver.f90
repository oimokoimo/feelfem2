module mod_skyline_solver
contains
  subroutine skyline_sol(vkgs,vkgd,vkgi,vfg,kld,neq,mp,ifac,isol,nsym,energ)

    implicit none

    double precision,dimension(:),pointer   :: vkgs,vkgd,vkgi
    double precision,dimension(:),pointer   :: vfg
    integer         ,dimension(:),pointer   :: kld
    integer         ,intent(in)             :: neq,mp,ifac,isol,nsym
    double precision                        :: energ

    double precision                        :: scal

    ! auto variables
    integer                                 :: i,j
    integer                                 :: ic
    integer                                 :: j1,j2
    integer                                 :: imin,imin1
    integer                                 :: imax
    integer                                 :: ik  ,ij
    integer                                 :: jhk ,jhj ,lhk
    integer                                 :: jhk1,jhj1,lhk1
    integer                                 :: jbk ,jck
    double precision                        :: cdiag,c1,c2
    double precision                        :: zero

    data   zero/0.0d0/
    !------------------------------------------------------------

    ik = 1

    IF( VKGD(1).NE.ZERO ) GOTO 10
    WRITE(*,2000 ) IK
    STOP

10  ENERG = ZERO
    !
    !
    JHK = 1
    DO 101 IK = 2, NEQ

       JHK1 = KLD( IK + 1 )

       LHK = JHK1 - JHK
       LHK1 = LHK - 1
       !
       IMIN  = IK - LHK1
       IMIN1 = IMIN - 1
       !
       IMAX = IK - 1

       IF( LHK1.LT.0 ) GOTO 100
       IF( IFAC.NE.1 ) GOTO 90
       IF( NSYM.EQ.1 ) VKGI( JHK ) = VKGI( JHK ) / VKGD( IMIN1 )
       IF( LHK1.EQ.0 ) GOTO 40
       !
       !
       JCK = JHK + 1
       JHJ = KLD( IMIN )
       !
       DO  IJ = IMIN,IMAX         ! do 30
          JHJ1 = KLD( IJ + 1 )

          IC = MIN0( JCK - JHK , JHJ1 - JHJ )

          IF( ( IC.LE.0 ).AND.( NSYM.EQ.0 ) ) GOTO 20
          C1 = ZERO
          IF( IC.LE.0 ) GOTO 17
          J1 = JHJ1 - IC
          J2 = JCK - IC
          IF( NSYM.EQ.1 ) GOTO 15
          VKGS(JCK)=VKGS(JCK)-SCAL(VKGS(J1),VKGS(J2),IC)
          GOTO 20
15        VKGS(JCK)=VKGS(JCK)-SCAL(VKGI(J1),VKGS(J2),IC)
          C1 = SCAL( VKGS( J1 ), VKGI( J2 ), IC )
17        VKGI( JCK ) = (VKGI(JCK)-C1) / VKGD( IJ )
20        JCK = JCK + 1
          JHJ = JHJ1
       end DO                 ! 30
       !
       !
40     JCK = JHK
       CDIAG = ZERO
       DO  IJ = IMIN1,IMAX    ! 70
          C1 = VKGS( JCK )
          IF( NSYM.EQ.1 ) GOTO 50
          C2 = C1 / VKGD( IJ )
          VKGS( JCK ) = C2
          GOTO 60
          !
50        C2 = VKGI( JCK )
60        CDIAG = CDIAG + C1 * C2
          JCK = JCK + 1
       end do                                    ! 70
       VKGD( IK ) = VKGD( IK ) - CDIAG
       IF( VKGD( IK ) ) 90,80,90
       !
80     WRITE( *,2000 ) IK
2000   FORMAT(' *** ERROR,ZERO PIVOT EQUATION ',I5 )
       STOP
       !
       !
90     IF( ISOL.NE.1 ) GOTO 100
       IF( NSYM.NE.1 ) VFG( IK ) = VFG( IK ) - SCAL( VKGS( JHK ), &
                                          VFG( IMIN1 ) , LHK )

       IF( NSYM.EQ.1 ) VFG( IK ) = VFG( IK ) - SCAL( VKGI( JHK ), &
                                          VFG( IMIN1 ),LHK )
       !
100    JHK = JHK1
101 end do               ! 101( former 100)
       !
    IF( ISOL.NE.1 ) RETURN
    !
    IF( NSYM.EQ.1 ) GOTO 120
    DO 110 IK = 1,NEQ
       C1 = VKGD( IK )
       C2 = VFG( IK ) / C1
       VFG( IK ) = C2
       ENERG = ENERG + C1 * C2 * C2
110 end do
       !
       !
120 IK = NEQ + 1
    JHK1 = KLD( IK )
       !
130 IK = IK - 1
    IF( NSYM.EQ.1 ) VFG( IK ) = VFG( IK ) / VKGD( IK )
    IF( IK.EQ.1 ) RETURN
    C1 = VFG( IK )
    JHK = KLD( IK )
    JBK = JHK1 - 1
    IF( JHK.GT.JBK ) GOTO 150
    IJ = IK - JBK + JHK - 1
    DO JCK = JHK,JBK
       VFG( IJ ) = VFG( IJ ) - VKGS( JCK ) * C1
       IJ = IJ + 1
    end do
    !
150 JHK1 = JHK
    GOTO 130
    !
  end subroutine skyline_sol
end module mod_skyline_solver
