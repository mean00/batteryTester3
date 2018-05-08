#!/bin/sh
conv()
{
rm -f $1.h $1_preview.png
convert  $1.png  -monochrome -flatten $1.h
convert  $1.png  -monochrome -flatten $1_preview.png
mv $1.h $1.tmp
cat $1.tmp | sed "s/MagickImage/$1/g" > $1.h
rm -f $1.tmp
}
conv background
conv li_ion
