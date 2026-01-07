      subroutine NC_connect(nc,ipf,npmax,ielem,nelem,np,ncmax,ndf)
*------------------------------------------------------------------
*     Calculate the maximum number of connecting elements
*     This routines used for CRS type matrix topology
*     
*     ndf is also calculated in this 
*
*
*     nc(*)    : work array
*     ipf(*)   : freedom array for each node
*     npmax    : number of nodes
*     ielem(np,nelem)  : element-node array  nelem,np elements,node per E resp.
*    
*
*     OUTPUT
*
*     ncmax  : number of maximum connecting elements
*     ndf    : number of degree of freedom in one element
*------------------------------------------------------------------
      dimension nc(npmax)
      dimension ipf(npmax)
      dimension ielem(np,nelem)
*
      do 100 i=1,npmax
      nc(i)=0
100   continue
  
      do 200 i=1,nelem
      do 210 j=1,np
      nc(ielem(j,i))=nc(ielem(j,i))+1
210   continue
200   continue
*
      ncmax = nc(1)
      nptr  =    1
      do 300 i=2,npmax
      if(ncmax .LT. nc(i)) then
        ncmax = nc(i)
	nptr  = i
      endif
300   continue

      ndf = 0
      do 400 i=1,np
      ndf = ndf + ipf(ielem(i,1))
400   continue
*
      return
      end


