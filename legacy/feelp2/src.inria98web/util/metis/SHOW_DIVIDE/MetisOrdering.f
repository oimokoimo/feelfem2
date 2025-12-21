      subroutine MetisOrdering(morder,nparts,nelem)
*
*     Read metis.feel data.  Because metis reads raw bamg.mesh data
*     ordering, it is required to reoder again.
*
*
      dimension morder(nelem),nparts(nelem),newnparts(nelem)
*
      open(unit=39,file='metis.feel',status='old',err=9999)
*
      do 100 i=1,nelem
      read(39,*) nptr
      morder(nptr) = nparts(i)
100   continue
*
      close(39)
      return
*
9999  stop 'cannot open metis.feel'
      end
 
      
