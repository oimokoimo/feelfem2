      subroutine ReadMetisBamg(npart,nelem,nparts)
      dimension npart(nelem)
      open(unit=38,file='metis.bamg',status='old',err=999)
      nparts = 0 
      do 100 i=1,nelem
      read(38,*) npart(i)
      if(npart(i) .gt. nparts) nparts = npart(i)
100   continue
      close(38)
      return
*
999   stop 'cannot open metis.bamg'
      end


