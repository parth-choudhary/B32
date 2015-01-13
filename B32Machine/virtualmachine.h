#ifndef VIRTUALMACHINE_H
#define VIRTUALMACHINE_H

#include"mainwindow.h"



class VirtualMachine
{
public:
    VirtualMachine(QString name);
     int ExecuteProgram(int ExexAddr);
     quint8 getValueAt(int position);
     void setValueAt(int position,quint8 value);


private:

    enum Registers
    {
    Unknown = 0,
    A = 4,
    B = 2,
    D = 1,
    X = 16,
    Y = 8
    };

    quint8 B32Memory[65535];
    ushort StartAddr;
    ushort ExecAddr;
    ushort InstructionPointer;
    ushort Register_A;
    ushort Register_B;
    ushort Register_X;
    ushort Register_Y;
    ushort Register_D;
    void UpdateRegisterStatus();
    void OpenFileToExecute(QString name);

    void SetRegisterD();
    quint8 CompareFlag;

};

#endif // VIRTUALMACHINE_H
