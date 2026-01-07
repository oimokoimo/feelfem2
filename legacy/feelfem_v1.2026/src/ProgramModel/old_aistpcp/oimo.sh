for i  in $*
do
 mv $i  `echo $i | sed 's/cpp/CPP/'`
done
