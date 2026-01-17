module numeric

integer, parameter :: INT4          = selected_int_kind(9)  ! INTEGER*4
integer, parameter :: REAL8         = kind(1.0d0)           ! REAL   *8
integer, parameter :: Oui           = 1
integer, parameter :: Non           = 0
integer, parameter :: NodeError     = -1
integer, parameter :: already       = 1
integer, parameter :: notYet        = 0
integer, parameter :: Nur_One_Etype = -999            ! for enptr(2,*)
integer, parameter :: EndOfEnptr    = -9999           ! for enptr(2,nelem+1)

end module numeric
