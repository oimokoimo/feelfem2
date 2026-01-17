      subroutine f_alloc_init(max_feel)
*-------------------------------------------------------------------
*  feelfem P2 Program model System Subroutine f_alloc_init
*
*  2000/05/30 (feelfem_stokes version)
*
*-------------------------------------------------------------------
      parameter (MAX_PUSH=32)
c --------------------------------------------------------------------
      common /pfeel_alc/np_work,iptr,np_push(MAX_PUSH),np_heap,max_heap
c --------------------------------------------------------------------
      if(max_feel .LT. 1 ) call abortexit(0,'ERR f_alloc_init')
      np_work  = 1
      max_heap = 1
      np_heap  = max_feel
*
      return
*
      end
      integer*4 function np_work_get_falloc()
*-------------------------------------------------------------------
*  feelfem P2 Program model System function np_work_get_falloc
*-------------------------------------------------------------------
      parameter (MAX_PUSH=32)
c --------------------------------------------------------------------
      common /pfeel_alc/np_work,iptr,np_push(MAX_PUSH),np_heap,max_heap
c --------------------------------------------------------------------

      np_work_get_falloc = np_work
      
      return
*
      end
      subroutinef_alloc_get_info(np_work_ret,max_heap_ret)
*-------------------------------------------------------------------
*  feelfem P2 Program model System function np_work_set_falloc
*-------------------------------------------------------------------
      parameter (MAX_PUSH=32)
      integer*4 np_work_ret,max_heap_ret
c --------------------------------------------------------------------
      common /pfeel_alc/np_work,iptr,np_push(MAX_PUSH),np_heap,max_heap
c --------------------------------------------------------------------
      np_work_ret  = np_work
      max_heap_ret = max_heap
* 
      return
      end
      subroutine np_work_set_falloc(np)
*-------------------------------------------------------------------
*  feelfem P2 Program model System function np_work_set_falloc
*-------------------------------------------------------------------
      parameter (MAX_PUSH=32)
c --------------------------------------------------------------------
      common /pfeel_alc/np_work,iptr,np_push(MAX_PUSH),np_heap,max_heap
c --------------------------------------------------------------------
      if(np .GT. np_heap .OR. np .LT. 1) then
         call abortexit(-1,'np_work_set_err')
      endif
*
      np_work = np
      if(max_heap .LT. np_work) max_heap = np_work
*
      return
      end
      subroutine f_alloc(nptr , cha, n , itype, imode)
*-------------------------------------------------------------------
*  feelfem P2 Program model System Subroutine f_alloc
*-------------------------------------------------------------------
*  Purpose:  Allocate memory
*
*   nptr  :out   : allocated address in real*4 feel(*)
*   cha   :in    : comment for allocation
*   n     :in    : size (as Fortran array, not word)
*   itype :in    : 0 4-byte(integer)  1 8-byte(double precision)
*   imode :in/out: [in] = 0 when error ABORT
*                       =-1 when error return anyway
*                  [out]=0 no error
*                       >0 size of shortage in words
*-------------------------------------------------------------------
      parameter (MAX_PUSH=32)
      character cha*(*)
c --------------------------------------------------------------------
      common /pfeel_alc/np_work,iptr,np_push(MAX_PUSH),np_heap,max_heap
c --------------------------------------------------------------------
*
      nn = 0
      if(itype .eq. 1) then
        if((np_work / 2) * 2 .eq. np_work) np_work = np_work+1
	nn = n * 2
      endif
      if(itype .eq. 0) then
	nn = n
      endif

      if(nn .eq. 0) then
	write(*,*) 'in allocate ',cha
	write(*,*) 'n = ',n,' itype = ',itype
        call abortexit(-1,'f_alloc itype error')
      endif
  
      np = np_work + nn
      if(np . gt . np_heap) then
        if(imode .eq. 0) then
          write(*,*) 'Cannot allocate array for ',cha 
          write(*,*) 'No space for ',np-np_heap ,' word'
          call abortexit(-1,'feel: memory allocation')
        else
          write(*,*) 'Cannot allocate array for ',cha 
          if(imode .ne. -1) then
             call abortexit(-1,'and imode error in f_alloc')
          endif
          imode = np-np_heap
        endif
      endif
*
      nptr    = np_work
      np_work = np
*
      if(np_work.gt.max_heap) max_heap = np_work
      if(imode.eq. -1) imode   = 0
*
      return
*
      end
      subroutine f_alloc_push
*-------------------------------------------------------------------
*  feelfem P2 Program model System Subroutine f_alloc_push
*-------------------------------------------------------------------
      parameter (MAX_PUSH=32)
c --------------------------------------------------------------------
      common /pfeel_alc/np_work,iptr,np_push(MAX_PUSH),np_heap,max_heap
c --------------------------------------------------------------------
      data    iptr/0/
      iptr = iptr + 1
      if(iptr.GT.MAX_PUSH) then
         call abortexit(-1,'TOO MANY F_ALLOC PUSH called')
      endif
      np_push(iptr) = np_work
      return
      end
      subroutine f_alloc_pop
*-------------------------------------------------------------------
*  feelfem P2 Program model System Subroutine f_alloc_pop
*-------------------------------------------------------------------
      parameter (MAX_PUSH=32)
c --------------------------------------------------------------------
      common /pfeel_alc/np_work,iptr,np_push(MAX_PUSH),np_heap,max_heap
c --------------------------------------------------------------------
      if(iptr .eq. 0) then
         call abortexit(-1,'TOO MANY F_ALLOC_POP called')
      endif
      np_work = np_push(iptr)
      iptr = iptr - 1
      return
      end
      subroutine f_move(ide,ia, num)
*-----------------------------------
* Move array block de ide(*) a ia(*).
*-----------------------------------
      integer*4 ide(*),ia(*)
      do 100 i=1,num
         ia(i)=ide(i)
 100  continue
      return
      end
