
#include "TFT_eSPI_extended.h"

int tftLocked=0;

/**
 */
void TFT_eSPI_extended::drawBitmap(int width, int height, int wx, int wy, int fgcolor, int bgcolor, const uint8_t *data)
{
    uint8_t *p=(uint8_t *)data;    
    uint16_t line[320];
    
    width>>=3;
    for(int y=0;y<height;y++)
    {
        uint16_t *o=line;
        setWindowLocked(wx, wy+y, wx+width*8-1, wy+y-1);
        for(int x=0;x<width;x++)
        {
            int stack=*p++;
            for(int step=0;step<8;step++)
            {
                int color;
                if(stack&0x80)                                        
                    color=fgcolor;
                else
                    color=bgcolor;
                *o++=color;
                stack<<=1;
            }            
        }    
        pushColors(line,width*8,0);
    }   
}

/**
 */
void TFT_eSPI_extended::drawRLEBitmap(int width, int height, int wx, int wy, int fgcolor, int bgcolor, const uint8_t *data)
{
    uint8_t *p=(uint8_t *)data;    
    uint16_t line[320];
    
    
    width>>=3;
    for(int y=0;y<height;y++)
    {
        uint16_t *o=line;
        setWindowLocked(wx, wy+y, wx+width*8-1, wy+y-1);
        for(int x=0;x<width;) // in bytes
        {
            int val=*p++;
            int count=1;
            if(val==0x76)
            {
                val=*p++;
                count=*p++;
            }
            for(int i=0;i<count;i++)
            {
                int stack=val;
                for(int step=0;step<8;step++)
                {
                    int color;
                    if(stack&0x80)                                        
                        color=fgcolor;
                    else
                        color=bgcolor;
                    *o++=color;
                    stack<<=1;
                }            
            }
            x+=count;
        }    
        pushColors(line,width*8,0);
    }   
}


