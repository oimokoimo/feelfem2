      SUBROUTINE SOL(VKGS,VKGD,VKGI,VFG,KLD,NEQ,MP,IFAC,ISOL,NSYM,ENERG)
     $
C***********************************************************
C     SUBROUTINE SOL(VKGS,VKGD,VKGI,VFG,KLD,NEQ,MP,IFAC,ISOL,NSYM,ENERG)
C
C                                               sol.f
C
C     input      VKGS,VKGD,VKGI
C                VFG
C                KLD
C                NEQ
C                MP
C                IFAC
C                ISOL
C                NSYM
C     output     VKGS,VKGI,VKGD
C                VFG
C                ENERG
*
*
*
*
C************************************************************
      IMPLICIT REAL*8(A-H,O-Z)
      DIMENSION VKGS(1),VKGD(1),VKGI(1),VFG(1),KLD(1)
      DATA ZERO/0.0D0/
C
      IK = 1
      IF( VKGD(1).NE.ZERO ) GOTO 10
      WRITE( MP,2000 ) IK
      STOP
 10   ENERG = ZERO
C
C---
C
      JHK = 1
      DO 100 IK = 2, NEQ

         JHK1 = KLD( IK + 1 )

         LHK = JHK1 - JHK
         LHK1 = LHK - 1
C
         IMIN  = IK - LHK1
         IMIN1 = IMIN - 1
C
         IMAX = IK - 1

         IF( LHK1.LT.0 ) GOTO 100
         IF( IFAC.NE.1 ) GOTO 90
         IF( NSYM.EQ.1 ) VKGI( JHK ) = VKGI( JHK ) / VKGD( IMIN1 )
         IF( LHK1.EQ.0 ) GOTO 40
C
C
         JCK = JHK + 1
         JHJ = KLD( IMIN )
C
         DO 30 IJ = IMIN,IMAX
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
 15         VKGS(JCK)=VKGS(JCK)-SCAL(VKGI(J1),VKGS(J2),IC)
            C1 = SCAL( VKGS( J1 ), VKGI( J2 ), IC )
 17         VKGI( JCK ) = (VKGI(JCK)-C1) / VKGD( IJ )
 20         JCK = JCK + 1
 30      JHJ = JHJ1
C
C
 40      JCK = JHK
         CDIAG = ZERO
         DO 70 IJ = IMIN1,IMAX
            C1 = VKGS( JCK )
            IF( NSYM.EQ.1 ) GOTO 50
            C2 = C1 / VKGD( IJ )
            VKGS( JCK ) = C2
            GOTO 60
C
 50         C2 = VKGI( JCK )
 60         CDIAG = CDIAG + C1 * C2
 70      JCK = JCK + 1
         VKGD( IK ) = VKGD( IK ) - CDIAG
         IF( VKGD( IK ) ) 90,80,90
C
 80      WRITE( MP,2000 ) IK
 2000    FORMAT(' *** ERROR,ZERO PIVOT EQUATION ',I5 )
         STOP
C
C
 90      IF( ISOL.NE.1 ) GOTO 100
         IF( NSYM.NE.1 ) VFG( IK ) = VFG( IK ) - SCAL( VKGS( JHK ),
     $                                  VFG( IMIN1 ) , LHK )
         IF( NSYM.EQ.1 ) VFG( IK ) = VFG( IK ) - SCAL( VKGI( JHK ),
     $                                  VFG( IMIN1 ),LHK )
C
 100  JHK = JHK1
C
      IF( ISOL.NE.1 ) RETURN
C
      IF( NSYM.EQ.1 ) GOTO 120
      DO 110 IK = 1,NEQ
         C1 = VKGD( IK )
         C2 = VFG( IK ) / C1
         VFG( IK ) = C2
         ENERG = ENERG + C1 * C2 * C2
 110  CONTINUE
C
C
 120  IK = NEQ + 1
      JHK1 = KLD( IK )
C
 130  IK = IK - 1
      IF( NSYM.EQ.1 ) VFG( IK ) = VFG( IK ) / VKGD( IK )
      IF( IK.EQ.1 ) RETURN
      C1 = VFG( IK )
      JHK = KLD( IK )
      JBK = JHK1 - 1
      IF( JHK.GT.JBK ) GOTO 150
      IJ = IK - JBK + JHK - 1
      DO 140 JCK = JHK,JBK
         VFG( IJ ) = VFG( IJ ) - VKGS( JCK ) * C1
 140     IJ = IJ + 1
C
 150  JHK1 = JHK
      GOTO 130
C
      END
