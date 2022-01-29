#include "stdint.h"
extern const unsigned char li_ion[];
extern const unsigned char background[];

#include "generated/li_ion_compressed.h"
//#include "generated/background_compressed.h"

#include "generated/bat0_compressed.h"
#include "generated/bat2_compressed.h"
#include "generated/bat4_compressed.h"
#include "generated/bat6_compressed.h"

const uint8_t *bat[4]={bat0,bat2,bat4,bat6};

void dummyFunc()
{
    const unsigned char *a=li_ion;
    const unsigned char *b=background;
    
    int c=a[4]+b[9];
    
}
