/***************************************************
 Battery Tester
 * GPL v2
 * (c) mean 2018 fixounet@free.fr
 ****************************************************/

#pragma once

/**
 */
class PushButton
{
public:
                    PushButton(int pin);
        bool        pressed();
        void        interrupt();
protected:        
        int          _pressed;
};
