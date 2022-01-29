#!/bin/sh
# Convert to 1 bit per pixel + heatshrink
#
#set -x
export HS_ARG="-w 8 -l 4"
export HS=/usr/local/bin/heatshrink
export CONVERTHS=../../externals/simplerILI9341/tools/bitmap/convertHS.py

dump()
{
export ST="s/generated.*\[/$1\[/g"
xxd -i generated/$1.hs  | sed "$ST" | sed "s/unsigned/extern const unsigned/g"> generated/$1_compressed.h
python3 $CONVERTHS $2 generated/$1_decl.h $1

}

convGif()
{
rm -f converted/$1*
convert  $1.gif    -depth 1 GRAY:generated/$1.bin
$HS $HS_ARG generated/$1.bin generated/$1.hs
dump $1 $1.gif
}
conv()
{
rm -f converted/$1*
convert  $1.png    -depth 1 GRAY:generated/$1.bin
$HS $HS_ARG generated/$1.bin generated/$1.hs $1
dump $1 $1.png
}

conv li_ion
convGif bat0
convGif bat1
convGif bat2
convGif bat3
convGif bat4
convGif bat5
convGif bat6

