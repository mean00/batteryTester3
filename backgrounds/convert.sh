#!/bin/sh
conv()
{
convert  $1.png  -monochrome $1.h
mv $1.h $1.tmp
cat $1.tmp | sed "s/MagickImage/$1/g" > $1.h
rm -f $1.tmp
}
conv background
