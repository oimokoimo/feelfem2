*realformat "%12.5f"
*intformat  "%8i"
*if(ndime==2)
*if(nnode==3)
*set var BNP=2
*set var NETYPE=3
*endif
*if(nnode==6)
*set var BNP=3
*set var NETYPE=3
*endif
*if(nnode==4)
*set var BNP=2
*set var NETYPE=4
*endif
*if(nnode==8)
*set var BNP=3
*set var NETYPE=4
*endif
*if(nnode==9)
*set var BNP=3
*set var NETYPE=4
*endif
*endif
*if(ndime==3)
*if(nnode==4)
*set var BNP=3
*set var NETYPE=5
*endif
*if(nnode==10)
*set var BNP=6
*set var NETYPE=5
*endif
*if(nnode==8)
*set var BNP=4
*set var NETYPE=6
*endif
*if(nnode==20)
*set var BNP=8
*set var NETYPE=6
*endif
*if(nnode==27)
*set var BNP=9
*set var NETYPE=6
*endif
*endif
FEELFEMGID
*ndime*npoin       2       2       0       0


NODE
*loop nodes
*NodesNum*NodesCoord(1,real)*NodesCoord(2,real)*NodesCoord(3,real)
*end nodes
       0
EDAT
       1*nelem*nnode*NETYPE
*loop elems
*ElemsConec*ElemsMat
*end elems
NSET
*Set Cond outer *nodes
*set var ND(int)=CondNumEntities(int)
       1*ND       2
*loop nodes *OnlyInCond
*NodesNum       0
*end
NSET
*Set Cond koimo(d) *nodes
*set var ND(int)=CondNumEntities(int)
       2*ND       2
*loop nodes *OnlyInCond
*NodesNum       0
*end
EDAT
*Set Cond koimo(n) *elems
*set var NE(int)=CondNumEntities(int)
       2*NE*BNP
*loop elems *OnlyInCond
*globalnodes*elemsnum()
*end
REGN
       2              # number of regions in script
*for(i=1;i<=2;i=i+1)
*set var assigned=-1
*loop materials
*if(MatProp(Region_code,int)==i)
*set var assigned=MatNum
*break
*endif
*end materials
*assigned        # matno for region code *i
*end for
END 
