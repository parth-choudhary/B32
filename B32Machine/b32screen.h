#ifndef B32SCREEN_H
#define B32SCREEN_H

#include "mainwindow.h"
class B32Screen
{
public:
    B32Screen();
    ushort ScreenMemoryLocation();
    void Poke(ushort Address, quint8 Value);
    quint8 Peek(ushort Address);

private:
    ushort m_ScreenMemoryLocation;
    quint8 m_ScreenMemory[4000];

};

#endif // B32SCREEN_H

