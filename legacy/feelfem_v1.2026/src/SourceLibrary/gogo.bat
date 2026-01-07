for i in  SL_feelfem90 SL_feelfem90DRAMA SL_feelP2 SL_MT_P2CRS SL_MT_ff90PAMGCRS SL_MT_ff90AMGCRS SL_LIB_feelP2Achim SL_MT_P2Skyline SL_LIB_feelP2Skyline SL_LIB_feelfem90Skyline SL_MT_ff90SKYLINE
do
echo $i
cd $i
\rm *.cpp Makefile *.o *.a
cd original
../../ssmake NAMEDATA
mv *.cpp ..
mv *.hpp /home/fujio/feelfem/src/class
cd ..
feelfemSourceLibraryMakeMakefile *.cpp
cd ..
done
