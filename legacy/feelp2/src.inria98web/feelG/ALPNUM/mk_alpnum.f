
*               superscripted if it follows after ^ *
*             and subscripted if it follows after _ *
*            When N = -1 or -2 characters cannot    *
*             be super- or subscripted              *
*     RWIDTH...ratio of width between characters    *
*              to height H                          *
*              normally RWIDTH = 1.0                *
*****************************************************
*
      PARAMETER (MAXSTR = 17, MESHST = 7)
      CHARACTER*72 IA
*
      I = 1

      OPEN (11, FILE='alpnum.str',
     $         ACCESS='DIRECT', RECL=72,
     $         FORM='UNFORMATTED', ERR=99)
 1000 if(i.eq.97) goto 9999
      read(*,'(A72)') ia
      write(*,*) 'READ IA =',IA

      write (11,REC=i) IA

      i = i + 1
      goto 1000
9999  close(11)
       stop 'normal'
99     stop ' file err'
      end
