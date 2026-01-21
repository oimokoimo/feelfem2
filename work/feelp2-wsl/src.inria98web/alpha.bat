for i
do
cd $i
ar rv $i.a *.o
ranlib $i.a
cd ..
done

