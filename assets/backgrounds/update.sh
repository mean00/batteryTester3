process()
{
export base=`basename $1`
export base="${base%.*}"
python3 convert.py $1 generated/${base}_compressed.h  generated/${base}_decl.h  $base
}
process li_ion.png
process bat0.gif
process bat1.gif
process bat2.gif
process bat3.gif
process bat4.gif
process bat5.gif
process bat6.gif

