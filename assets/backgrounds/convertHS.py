#
# Simple RLE packing with magic byte = 0x76
#

from PIL import Image
from struct import *
import sys

mpretty=0
compressed=0
stuct_name=""
def print_external_header(f):
    global struct_name
    f.write("#define "+str(struct_name)+"_width "+str(width)+"\n")
    f.write("#define "+str(struct_name)+"_height "+str(height)+"\n")
    f.write("extern const unsigned char "+str(struct_name)+"[];\n");

if 4!=len(sys.argv):
    #           0   1           2     3     
    print("convert intput.png decl.h name")
    exit(1)
image=Image.open(sys.argv[1])
struct_name=sys.argv[3]
(width,height) = image.size
f= open(sys.argv[2], 'wt')
print_external_header(f);
f.close()

