#ifndef _EVLK_HPDL1414_H_
#define _EVLK_HPDL1414_H_

#include "Arduino.h"
#include "evlk_nopins.h"

namespace _EVLK_HPDL1414_
{
    class hpdl1414 : public Print
    {
    private:
        using nopin_size_t = _EVLK_NOPINS_::nopin_size_t;
        nopin_size_t D0;
        nopin_size_t D1;
        nopin_size_t D2;
        nopin_size_t D3;
        nopin_size_t D4;
        nopin_size_t D5;
        nopin_size_t D6;
        nopin_size_t A0;
        nopin_size_t A1;
        nopin_size_t WR;
        char Buffer[4];

    public:
        hpdl1414(nopin_size_t D0,
                 nopin_size_t D1,
                 nopin_size_t D2,
                 nopin_size_t D3,
                 nopin_size_t D4,
                 nopin_size_t D5,
                 nopin_size_t D6,
                 nopin_size_t A0,
                 nopin_size_t A1,
                 nopin_size_t WR);
        void Begin();      // init driver pins
        void pos(int num); // 0~3
        void send(char c);
        void latch();
        size_t write(uint8_t) override;
        size_t write(const uint8_t *buffer, size_t size) override;
        void flush() override;
    };
}
#endif