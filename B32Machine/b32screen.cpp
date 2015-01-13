#include "b32screen.h"
#include<QDebug>

B32Screen::B32Screen()
{
    m_ScreenMemoryLocation = 0xA000;

    for (int i = 0; i < 4000; i += 2)
    {
    m_ScreenMemory[i] = 32;
    m_ScreenMemory[i + 1] = 7;
    }

}

void B32Screen::Poke(ushort Address, quint8 Value)
{
    ushort MemLoc;
    MemLoc = (ushort)(Address - m_ScreenMemoryLocation);
    if (MemLoc < 0 || MemLoc > 3999)
    {
        qDebug()<<"returning:out of bounds";
        return;
    }
    qDebug()<<"the memory location="<<MemLoc;

    m_ScreenMemory[MemLoc] = Value;
 qDebug()<<"the value at memory location="<<m_ScreenMemory[MemLoc];

}

quint8 B32Screen::Peek(ushort Address)
{
    ushort MemLoc;
        MemLoc = (ushort)(Address - m_ScreenMemoryLocation);
        if (MemLoc < 0 || MemLoc > 3999)
            return (quint8)0;
        return m_ScreenMemory[MemLoc];
    }
