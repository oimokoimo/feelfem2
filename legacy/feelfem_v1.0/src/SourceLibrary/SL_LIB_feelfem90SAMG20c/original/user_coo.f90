!........................................................................................
!     user_coo(i,ndim,x,y,z)
!........................................................................................
!........................................................................................
!
      subroutine user_coo(i,ndim,x,y,z)

!     Purpose: Provide variable-to-coordinate mapping.

!     If no coordinates are available, just return with NDIM=0.

!     input:

!        i    - number of variable (1<=i<=nnu)

!     output:

!        ndim  - dimension of current problem (=2 or =3)
!        x,y,z - coordinates of point where variable i is located
!                (if ndim=2: z=0.0d0).

      implicit none
      integer i,ndim
      double precision x,y,z

      ndim=0      ! ndim=0 means: no coordinates defined
      return
      end subroutine
