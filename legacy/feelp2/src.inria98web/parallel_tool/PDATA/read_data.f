      subroutine read_data (feelpara,nskai,nmatrix)
*
      implicit real*8 (a-h,o-z)
*
      parameter (MAX_FEEL=2000000)
      parameter (MAX_DOMAIN=10)
      parameter (MAX_EDATSET=38)
      parameter (MAX_NODESET=20)
      parameter (MAX_NUMSET = 20)
      parameter (MAX_EWISE  = 20)
*
*
      real*4 feelpara(*)
      character*10 word
*
      common /feel_dat/ n_edat(MAX_EDATSET,3),
     $     n_nset(MAX_NODESET,2),
     $     n_ewise(MAX_EWISE,2)
      common /feel_var/np_work,np_x,np_y,np_z,nvars_fem,
     $     nvars_ewise,
     &     np_fem,np_ewise,np_heap
      common /feel_ctl/mode_ex,mode_output,max_heap
*
      open (15,file='feel_dat')
      open (16,file='MESH.PARA')
*     
*     ---分割回数(2^nankai)を読む ---
      read (16,9001) nankai
      if ((nankai.gt.nskai).or.(nankai.lt.0)) then
         stop 'nankai error'
      end if
 9001 format(i8)
*
      call f_alloc (np_nbb,'Read nbb',(1+2**nankai),0)
*      
*++++++++++++++++++++++++++++++++
*++++++++++++以下FEELの真似 ++++++++++
      read (15,*) word
      if (word.ne.'FEEL') then
         write (7,*) 'FEEL DATA ERROR'
         stop 'NOT FEEL DATA FILE'
      end if
*-------------------------
      read (15,*) ndim,npmax,nedat,nodeset,numset,nip,nmatrix
      read (15,*) mode_ex,mode_output
      read (15,*) nvars_fem,nvars_ewise
*
      if(ndim .ne. 1 .and. ndim .ne. 2 .and. ndim .ne.3 ) then
        stop 'ndim error'
      endif
*
      if(nedat .gt. MAX_EDATSET) then
       stop 'nedat error'
      endif
*
      if(nodeset .gt. MAX_NODESET) then
        stop 'nodeset error'
      endif
*
*
      do 100 i = 1,nedat
        n_edat(i,1) = 0
* ????????
        n_edat(i,2)=0
* ????????
 100  continue
*
      do 101 i = 1,nodeset
        n_nset(i,1) = 0
        n_nset(i,2) = 0
 101  continue
*
*
      if(nvars_ewise.eq.0) goto 200
      do 150 i=1,nvars_ewise
        read(15,9005) n_ewise(i,1),n_ewise(i,2)
 9005   format(2i8)
 150  continue
 200  continue
*
*---------------------------------
*     以下各集合のデータを読み込む。
*---------------------------------
*
*     ----全体剛性行列用EDAT集合の為のメモリ取得---
      call f_alloc (np_npiem,'Read npiem',nmatrix,
     $     0)
      call f_alloc (np_npmat,'Read npmat',nmatrix,
     $     0)
      if (nmatrix.eq.0) then
         stop 'nmatrix zero error'
      end if
*     ----境界要素用EDAT集合の為のメモリ取得 ----
*     8/9修正
      call f_alloc (np_npibem,'Read npibem',nedat,
     $     0)
      call f_alloc (np_npbmat,'Read npbmat',nedat,
     $     0)
*     8/9修正
*     ----全体節点集合NSETの為のメモリ取得 -----
      if (nodeset.gt.0) then
         call f_alloc (np_npins,'Read npins',nodeset,0)
      else if (nodeset.eq.0) then
         call f_alloc (np_npins,'Read npins',1,0) 
      else if (nodeset.lt.0) then
         stop 'nodeset error'
      end if
*     
      call f_alloc (np_npilno,'Read npilno',nmatrix,0)
      call f_alloc (np_npigno,'Read npigno',nmatrix,0)
*
         call read_data2 (feelpara,feelpara(np_npiem),
     $        nmatrix,nedat,
     $        feelpara(np_npmat),feelpara(np_npibem),
     $        feelpara(np_npbmat),feelpara(np_npins),
     $        nodeset,ndim,npmax,
     $        feelpara(np_nbb),nankai,
     $        feelpara(np_npilno),feelpara(np_npigno))
*
*
*      
      return 
      end




