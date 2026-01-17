echo *.c  >$1.mktmp
echo *.c >>$1.mktmp
echo *.c | sed 's/\.c/.obj/g' >>$1.mktmp
../win32tool/makenmakesub $1 <$1.mktmp >$1.mk
rm $1.mktmp
