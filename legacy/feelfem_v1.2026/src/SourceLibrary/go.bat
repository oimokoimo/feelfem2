for i in  $*
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
