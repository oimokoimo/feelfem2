module mod_wasblksolver
contains

  subroutine wasblksolver(n,  ia0,ja0,a0,b0,x0                &
       nbks,ibk0,nodekind0,            &
       nkinds,fillmap,updatemap,       &
       isolve,m,                       &
       iproc,iter,resid                )

    ! Washio-Block iterative solver

    ! integer n               : number of equations
    ! integer nbks            : number of blocks
    ! integer ibk0(nbks+1)    : block staring pointer
    ! integer nodekind0(nbks) : block type number
    !
    ! integer ia0(n+1)        : row separation pointer for CRS 
    ! integer ja0(nz)         : column pointer (nz=ia0(n+1) non-zero)
    !
    ! integer iproc           : ???
    ! integer isolve          : type of iteration  (0:STAB  1:GMRES)
    ! integer m               : if(isolve==1(GMRES) , m has restart number

    implicit none
    use numeric

    ! arguments
    integer                  :: n
    integer                  :: nbks
    integer                  :: nz
    integer                  :: iproc,info,isolve
    integer                  :: m
    integer                  :: nkinds
    integer                  :: ldel,udel

    integer,dimension(:)          :: ia0,ja0
    integer,dimension(:)          :: ibk0,nodekind0

    real(kind=REAL8),dimension(:) :: a0,b0,x0     ! matrix,RHS vector,solution

    integer                       :: iproc
    integer                       :: isolve       ! iteration method (0 or 1)
    integer                       :: iter
    real(kind=REAL8)              :: resid        ! solver parameters

    integer,dimension(nkinds,nkinds,nkinds) :: fillmap,updatemap

    ! auto variables
    integer                       :: i
    integer                       :: fill

    integer,dimension(:),pointer  :: uord,bord
    integer,dimension(:),pointer  :: ia,ja,ibk,nodekind

    real(kind=REAL8)                      ::rnorm,bnorm,rmax,t0,t1
    real(kind=REAL8),dimension(:),pointer ::a,diag,x,b,r
    !--------------------------------------------------------
    updatemap=1
    !---- stable-s: The following options are good for 
    !              the stability.           
    !      updatemap(1,1,2)=0
    !      updatemap(2,1,1)=0
    !---- stable-e
    !---- ssor(1,1)-s 
    !      updatemap(1,1,1)=0
    !---- ssor(1,1)-e
    ldel=0
    udel=0

    nz=ia0(n+1)-1
    allocate(ibk(nbks+1),nodekind(nbks))
    allocate(ia(n+1),ja(nz),a(nz),diag(n),b(n),x(n),r(n))
    allocate(uord(n),bord(nbks))
    !
    call matfmtopt(n,nbks,                &
         ibk0,nodekind0,ia0,ja0,a0,b0,     &
         fillmap,nkinds,                   &
         ibk,nodekind,ia,ja,a,diag,b,      &
         uord,bord)
    !
    ! initialize 
    x(1:n)=0.d0
    call Solve(iproc,n,nbks,ibk,  &
         $     nodekind,nkinds,fillmap,updatemap,ldel,udel,
    $     ia,ja,a,diag,x,b,
    $     isolve,m,iter,resid,info)

    do i=1,n
       x0(i)=x(uord(i))
    end do

    deallocate(ibk,nodekind)
    deallocate(ia,ja,a,diag,b,x,r)
    deallocate(uord,bord)

    return

  end subroutine wasblksolver
end module mod_wasblksolver
