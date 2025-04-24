#include "evlk_hpdl1414.h"

#define pMode(pin, val) _EVLK_NOPINS_::pinMode((pin), (PinMode)(val))
#define dWrite(pin, val) _EVLK_NOPINS_::digitalWrite((pin), (PinStatus)(val))

namespace _EVLK_HPDL1414_ {
hpdl1414::hpdl1414(nopin_size_t D0, nopin_size_t D1, nopin_size_t D2, nopin_size_t D3,
                   nopin_size_t D4, nopin_size_t D5, nopin_size_t D6, nopin_size_t A0,
                   nopin_size_t A1, nopin_size_t WR)
    : D0(D0), D1(D1), D2(D2), D3(D3), D4(D4), D5(D5), D6(D6), A0(A0), A1(A1), WR(WR) {
    memset(Buffer, 0, 4 * sizeof(char));
};
hpdl1414::~hpdl1414() {
    pMode(D0, INPUT);
    pMode(D1, INPUT);
    pMode(D2, INPUT);
    pMode(D3, INPUT);
    pMode(D4, INPUT);
    pMode(D5, INPUT);
    pMode(D6, INPUT);
    pMode(A0, INPUT);
    pMode(A1, INPUT);
    pMode(WR, INPUT);
}
void hpdl1414::Begin() {
    pMode(D0, OUTPUT);
    pMode(D1, OUTPUT);
    pMode(D2, OUTPUT);
    pMode(D3, OUTPUT);
    pMode(D4, OUTPUT);
    pMode(D5, OUTPUT);
    pMode(D6, OUTPUT);
    pMode(A0, OUTPUT);
    pMode(A1, OUTPUT);
    pMode(WR, OUTPUT);
};
void hpdl1414::pos(int num) {
    dWrite(A0, LOW);
    dWrite(A1, LOW);
    switch (num) {
    case 0:
        dWrite(A0, HIGH);
        dWrite(A1, HIGH);
        break;
    case 1:
        dWrite(A1, HIGH);
        break;
    case 2:
        dWrite(A0, HIGH);
        break;
    case 4:
        break;
    default:
        break;
    }
};
void hpdl1414::send(char data) {
    dWrite(D0, (data >> 0) & 0x1);
    dWrite(D1, (data >> 1) & 0x1);
    dWrite(D2, (data >> 2) & 0x1);
    dWrite(D3, (data >> 3) & 0x1);
    dWrite(D4, (data >> 4) & 0x1);
    dWrite(D5, (data >> 5) & 0x1);
    dWrite(D6, (data >> 6) & 0x1);
};
void hpdl1414::latch() {
    dWrite(WR, LOW);
    delay(1);
    dWrite(WR, HIGH);
};
size_t hpdl1414::write(uint8_t c) {
    memmove(Buffer + 1, Buffer, 4 - 1);
    Buffer[0] = (char)c;
    flush();
    return 1;
};
size_t hpdl1414::write(const uint8_t *buffer, size_t size) {
    size_t n = 0;
    size     = size > 4 ? 4 : size;
    memmove(Buffer + size, Buffer, 4 - size);
    memcpy(Buffer, buffer, size);
    flush();
    return n;
};
void hpdl1414::flush() {
    for (size_t i = 0; i < 4; i++) {
        pos(i);
        send(Buffer[i]);
        latch();
    }
}
} // namespace _EVLK_HPDL1414_