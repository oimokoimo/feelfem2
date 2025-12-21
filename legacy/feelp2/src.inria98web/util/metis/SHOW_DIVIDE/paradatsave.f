      subroutine paradatsave(n,num)
      data isav/99999/
      save isav
*
      if(n .eq. 0) then
         isav = num
      else
         num  = isav
      endif
*
      return
      end

         
