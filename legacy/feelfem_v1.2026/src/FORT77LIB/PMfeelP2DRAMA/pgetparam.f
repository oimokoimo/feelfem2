      subroutine pgetparam30(myrank,nprocs,
     $                      num,   n01,n02,n03,n04,n05,n06,
     $                             n07,n08,n09,n10,n11,n12,
     $                             n13,n14,n15,n16,n17,n18,
     $                             n19,n20,n21,n22,n23,n24,
     $                             n25,n26,n27,n28,n29,n30 )
*-------------------------------------------------------------------
      include 'mpif.h'
*-------------------------------------------------------------------
      parameter (MAX=30)
      integer myrank,nprocs
      integer buf(MAX)
*-------------------------------------------------------------------
      if(num    .gt.MAX .OR. num .lt. 1) then
         call abortexit(myrank,'pgetparm0')
      endif
*-------------------------------------------------------------------
      if(myrank .eq. 0) then
         buf(01) = n01
         buf(02) = n02
         buf(03) = n03
         buf(04) = n04
         buf(05) = n05
         buf(06) = n06
         buf(07) = n07
         buf(08) = n08
         buf(09) = n09
         buf(10) = n10
         buf(11) = n11
         buf(12) = n12
         buf(13) = n13
         buf(14) = n14
         buf(15) = n15
         buf(16) = n16
         buf(17) = n17
         buf(18) = n18
         buf(19) = n19
         buf(20) = n20
         buf(21) = n21
         buf(22) = n22
         buf(23) = n23
         buf(24) = n24
         buf(25) = n25
         buf(26) = n26
         buf(27) = n27
         buf(28) = n28
         buf(29) = n29
         buf(30) = n30

      endif
*
      call mpi_bcast(buf,num,MPI_INTEGER,0,mpi_comm_world,ierr)
*
      if(myrank .ne. 0) then
         n01 =  buf(01)
         n02 =  buf(02)
         n03 =  buf(03)
         n04 =  buf(04)
         n05 =  buf(05)
         n06 =  buf(06)
         n07 =  buf(07)
         n08 =  buf(08)
         n09 =  buf(09)
         n10 =  buf(10)
         n11 =  buf(11)
         n12 =  buf(12)
         n13 =  buf(13)
         n14 =  buf(14)
         n15 =  buf(15)
         n16 =  buf(16)
         n17 =  buf(17)
         n18 =  buf(18)
         n19 =  buf(19)
         n20 =  buf(20)
         n21 =  buf(21)
         n22 =  buf(22)
         n23 =  buf(23)
         n24 =  buf(24)
         n25 =  buf(25)
         n26 =  buf(26)
         n27 =  buf(27)
         n28 =  buf(28)
         n29 =  buf(29)
         n30 =  buf(30)

      endif
*
      return
      end
      subroutine pgetparam24(myrank,nprocs,
     $                      num,   n01,n02,n03,n04,n05,n06,
     $                             n07,n08,n09,n10,n11,n12,
     $                             n13,n14,n15,n16,n17,n18,
     $                             n19,n20,n21,n22,n23,n24  )
*-------------------------------------------------------------------
      include 'mpif.h'
*-------------------------------------------------------------------
      parameter (MAX=24)
      integer myrank,nprocs
      integer buf(MAX)
*-------------------------------------------------------------------
      if(num    .gt.MAX .OR. num .lt. 1) then
         call abortexit(myrank,'pgetparm0')
      endif
*-------------------------------------------------------------------
      if(myrank .eq. 0) then
         buf(01) = n01
         buf(02) = n02
         buf(03) = n03
         buf(04) = n04
         buf(05) = n05
         buf(06) = n06
         buf(07) = n07
         buf(08) = n08
         buf(09) = n09
         buf(10) = n10
         buf(11) = n11
         buf(12) = n12
         buf(13) = n13
         buf(14) = n14
         buf(15) = n15
         buf(16) = n16
         buf(17) = n17
         buf(18) = n18
         buf(19) = n19
         buf(20) = n20
         buf(21) = n21
         buf(22) = n22
         buf(23) = n23
         buf(24) = n24
      endif
*
      call mpi_bcast(buf,num,MPI_INTEGER,0,mpi_comm_world,ierr)
*
      if(myrank .ne. 0) then
         n01 =  buf(01)
         n02 =  buf(02)
         n03 =  buf(03)
         n04 =  buf(04)
         n05 =  buf(05)
         n06 =  buf(06)
         n07 =  buf(07)
         n08 =  buf(08)
         n09 =  buf(09)
         n10 =  buf(10)
         n11 =  buf(11)
         n12 =  buf(12)
         n13 =  buf(13)
         n14 =  buf(14)
         n15 =  buf(15)
         n16 =  buf(16)
         n17 =  buf(17)
         n18 =  buf(18)
         n19 =  buf(19)
         n20 =  buf(20)
         n21 =  buf(21)
         n22 =  buf(22)
         n23 =  buf(23)
         n24 =  buf(24)

      endif
*
      return
      end
      subroutine pgetparam18(myrank,nprocs,
     $                      num,   n01,n02,n03,n04,n05,n06,
     $                             n07,n08,n09,n10,n11,n12,
     $                             n13,n14,n15,n16,n17,n18  )
*-------------------------------------------------------------------
      include 'mpif.h'
*-------------------------------------------------------------------
      parameter (MAX=18)
      integer myrank,nprocs
      integer buf(MAX)
*-------------------------------------------------------------------
      if(num    .gt.MAX .OR. num .lt. 1) then
         call abortexit(myrank,'pgetparm0')
      endif
*-------------------------------------------------------------------
      if(myrank .eq. 0) then
         buf(01) = n01
         buf(02) = n02
         buf(03) = n03
         buf(04) = n04
         buf(05) = n05
         buf(06) = n06
         buf(07) = n07
         buf(08) = n08
         buf(09) = n09
         buf(10) = n10
         buf(11) = n11
         buf(12) = n12
         buf(13) = n13
         buf(14) = n14
         buf(15) = n15
         buf(16) = n16
         buf(17) = n17
         buf(18) = n18
      endif
*
      call mpi_bcast(buf,num,MPI_INTEGER,0,mpi_comm_world,ierr)
*
      if(myrank .ne. 0) then
         n01 =  buf(01)
         n02 =  buf(02)
         n03 =  buf(03)
         n04 =  buf(04)
         n05 =  buf(05)
         n06 =  buf(06)
         n07 =  buf(07)
         n08 =  buf(08)
         n09 =  buf(09)
         n10 =  buf(10)
         n11 =  buf(11)
         n12 =  buf(12)
         n13 =  buf(13)
         n14 =  buf(14)
         n15 =  buf(15)
         n16 =  buf(16)
         n17 =  buf(17)
         n18 =  buf(18)
      endif
*
      return
      end
      subroutine pgetparam3(myrank,nprocs, n01,n02,n03 )
*-------------------------------------------------------------------
      include 'mpif.h'
*-------------------------------------------------------------------
      integer myrank,nprocs
      integer buf(3)
*-------------------------------------------------------------------
      if(myrank .eq. 0) then
         buf(01) = n01
         buf(02) = n02
         buf(03) = n03
      endif
*
      call mpi_bcast(buf,num,MPI_INTEGER,0,mpi_comm_world,ierr)
*
      if(myrank .ne. 0) then
         n01 =  buf(01)
         n02 =  buf(02)
         n03 =  buf(03)
      endif
*
      return
      end
