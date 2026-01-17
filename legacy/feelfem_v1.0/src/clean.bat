
echo lib directory            ;cd lib                    ;rm *.a   

echo ElemGenerator            ;cd ElemGenerator          ;make clean; cd ..
echo ProgramModel             ;cd ProgramModel           ;make clean; cd ..
echo MatrixModel              ;cd MatrixModel            ;make clean; cd ..
echo Scheme                   ;cd Scheme                 ;make clean; cd ..
echo SolverLibrary            ;cd SolverLibrary          ;make clean; cd ..
echo Solve                    ;cd Solve                  ;make clean; cd ..
echo Source                   ;cd Source                 ;make clean; cd ..
echo main                     ;cd main                   ;make clean; cd ..
echo system                   ;cd system                 ;make clean; cd ..
echo test                     ;cd test                   ;make clean; cd ..
echo Object                   ;cd Object                 ;make clean; cd ..
echo basic                    ;cd basic                  ;make clean; cd ..
echo ToP2Interface            ;cd ToP2Interface          ;make clean; cd ..
echo FromP2Interface          ;cd FromP2Interface        ;make clean; cd ..
echo Quadrature               ;cd Quadrature             ;make clean; cd ..
echo TermConvert              ;cd TermConvert            ;make clean; cd ..
echo Main                     ;cd Main                   ;make clean; cd ..
echo class                    ;cd class                  ;make clean; cd ..
echo FiniteElement            ;cd FiniteElement          ;make clean; cd ..
echo tool                     ;cd tool                   ;rm *~ a.out; cd ..

echo ## PARSER SECTION
echo PARSER_SECTION           ;cd parser                 
echo parser                   ;make clean; 
echo SYNTAX                   ;cd Syntax                 ;make clean; cd ..
echo ParserFin                ;cd ..


echo ## SOURCE LIBRARY SECTION

echo SourceLibrary            ;cd SourceLibrary
echo SL_feelfem90DRAMA        ;cd SL_feelfem90DRAMA      ;make clean; cd ..
echo SL_feelfem90             ;cd SL_feelfem90           ;make clean; cd ..
echo SL_feelP2                ;cd SL_feelP2              ;make clean; cd ..
echo SL_MT_P2CRS              ;cd SL_MT_P2CRS            ;make clean; cd ..
echo SL_MT_P2Skyline          ;cd SL_MT_P2Skyline        ;make clean; cd ..
echo SL_MT_ff90AMGCRS         ;cd SL_MT_ff90AMGCRS       ;make clean; cd ..
echo SL_MT_ff90PAMGCRS        ;cd SL_MT_ff90PAMGCRS      ;make clean; cd ..
echo SL_LIBfeelP2Achim        ;cd SL_LIB_feelP2Achim     ;make clean; cd ..
echo SL_LIB_feelP2Skyline     ;cd SL_LIB_feelP2Skyline   ;make clean; cd ..
echo SL_LIB_feelfem90SAMG20c  ;cd SL_LIB_feelfem90SAMG20c;make clean; cd ..
echo SL_LIB_feelfem90Skyline  ;cd SL_LIB_feelfem90Skyline;make clean; cd ..

echo SourceLibraryFin         ;cd ..


