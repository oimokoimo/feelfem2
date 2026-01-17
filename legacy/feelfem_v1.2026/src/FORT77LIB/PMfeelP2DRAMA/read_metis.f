      subroutine read_metis(metis,m2f,nelem_g,ndiv)
c ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
c     feelfem/P2DRAMA program model system subroutine
c     Copyright NEC Corporation 2000    
c     
c     2000/04/12 Programmed by Hidehiro FUJIO    
c     
c     MODULE READ_METIS read metis output data
c
c     UNIT NUMBER 7 used
c
c     EXTERNAL ROUTINE   abortexit
c
c
c     DATA FILE:
c       metis.bamg   element partition data (0 to nPE-1) element no is bamg 
c       metis.feel   element ordering correspondance between metis(bamg) and 
c                    feel
c     INPUT
c       integer*4    nelem_g   total number of elements
c
c     OUTPUT
c       integer*4    metis(*)  element partition information
c       integer*4    m2f(*)    work array to convert metis ordering to feel ord.
c       integer*4    ndiv      number of partitions (compare nprocs in main)
c ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

      dimension metis(nelem_g)
      dimension m2f  (nelem_g)
*
      ndiv = -1
*
      open(unit=7,file='metis.bamg',status='old',err=9998)
      do 100 i=1,nelem_g
         read(7,*,END=9900) m2f(i)
         if(ndiv .LT. m2f(i)) ndiv = m2f(i)
 100  continue
      close(7)

      open(unit=7,file='metis.feel',status='old',err=9999)
*
      do 200 i=1,nelem_g
         read(7,*,END=9905) iptr
         metis(iptr) = m2f(i)
 200  continue
*
      close(unit=7)
*
      ndiv = ndiv+1
      return
*
 9900 call abortexit(0, 'end of file encountered (metis.bamg)')
 9905 call abortexit(0, 'end of file encountered (metis.feel)')
 9998 call abortexit(0, 'cannot open metis.bamg')
 9999 call abortexit(0, 'cannot open metis.feel')
*
      end
