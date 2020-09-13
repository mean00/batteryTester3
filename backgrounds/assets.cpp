#include "stdint.h"
extern const unsigned char li_ion[];
extern const unsigned char background[];

#include "generated/li_ion_compressed.h"
#include "generated/background_compressed.h"
void dummyFunc()
{
    const unsigned char *a=li_ion;
    const unsigned char *b=background;
    
    int c=a[4]+b[9];
    
}
