#include "evlk_hpdl1414.h"

namespace _EVLK_HPDL1414_
{
    hpdl1414::hpdl1414(nopin_size_t D0,
                       nopin_size_t D1,
                       nopin_size_t D2,
                       nopin_size_t D3,
                       nopin_size_t D4,
                       nopin_size_t D5,
                       nopin_size_t D6,
                       nopin_size_t A0,
                       nopin_size_t A1,
                       nopin_size_t WR)
        : D0(D0), D1(D1), D2(D2), D3(D3), D4(D4), D5(D5), D6(D6),
          A0(A0), A1(A1), WR(WR)
    {
        memset(Buffer, 0, 4 * sizeof(char));
        pinMode(D0, OUTPUT);
        pinMode(D1, OUTPUT);
        pinMode(D2, OUTPUT);
        pinMode(D3, OUTPUT);
        pinMode(D4, OUTPUT);
        pinMode(D5, OUTPUT);
        pinMode(D6, OUTPUT);
        pinMode(A0, OUTPUT);
        pinMode(A1, OUTPUT);
        pinMode(WR, OUTPUT);
    };
    void hpdl1414::pos(int num)
    {
        digitalWrite(A0, LOW);
        digitalWrite(A1, LOW);
        switch (num)
        {
        case 0:
            digitalWrite(A0, HIGH);
            digitalWrite(A1, HIGH);
            break;
        case 1:
            digitalWrite(A1, HIGH);
            break;
        case 2:
            digitalWrite(A0, HIGH);
            break;
        case 4:
            break;
        default:
            break;
        }
    };
    void hpdl1414::send(char data)
    {
        digitalWrite(D0, (data >> 0) & 0x1);
        digitalWrite(D1, (data >> 1) & 0x1);
        digitalWrite(D2, (data >> 2) & 0x1);
        digitalWrite(D3, (data >> 3) & 0x1);
        digitalWrite(D4, (data >> 4) & 0x1);
        digitalWrite(D5, (data >> 5) & 0x1);
        digitalWrite(D6, (data >> 6) & 0x1);
    };
    void hpdl1414::latch()
    {
        digitalWrite(WR, LOW);
        delay(1);
        digitalWrite(WR, HIGH);
    };
    size_t hpdl1414::write(uint8_t c)
    {
        memmove(Buffer + 1, Buffer, 4 - 1);
        Buffer[0] = (char)c;
        flush();
        return 1;
    };
    size_t hpdl1414::write(const uint8_t *buffer, size_t size)
    {
        size_t n = 0;
        size = size > 4 ? 4 : size;
        buffer += size - 1;
        while (size--)
            if (write(*buffer--))
                n++;
            else
                break;
        return n;
    };
    void hpdl1414::flush()
    {
        for (size_t i = 0; i < 4; i++)
        {
            pos(i);
            send(Buffer[i]);
            latch();
        }
    }
}