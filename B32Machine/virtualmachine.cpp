#include "virtualmachine.h"
//#include "common.h"


#include<QDebug>
#include<QFile>
#include<QMessageBox>



 VirtualMachine::VirtualMachine(QString fileName){
   // B32Memory[65535];
    StartAddr = 0;
    ExecAddr = 0;
    Register_A = 0;
    Register_B = 0;
    Register_D = 0;
    Register_X = 0;
    Register_Y = 0;
    CompareFlag = 0;
  //  InstructionPointer=0;
    UpdateRegisterStatus();
    OpenFileToExecute(fileName);
    qDebug()<<"Instructionpointer:"<<InstructionPointer;

    }


void VirtualMachine:: UpdateRegisterStatus(){
    QString strRegisters = "";
    QString str = "";
    str.setNum(Register_A, 16);
    strRegisters = "Register A = $";
    strRegisters += str;
    str.setNum(Register_B,16);
    strRegisters += "Register B = $";
    strRegisters += str;
    str.setNum(Register_D,16);
    strRegisters += "Register D = $";
    strRegisters +=str;
    str.setNum(Register_X, 16);
    strRegisters += "\nRegister X = $";
    strRegisters += str;
    str.setNum(Register_Y, 16);
    strRegisters += "Register Y = $";
    strRegisters += str;
    str.setNum(InstructionPointer, 16);
    strRegisters += " Instruction Pointer = $";
    strRegisters +=str;
    strRegisters+= " CompareFlag = $";
    str.setNum(CompareFlag,16 );

    qDebug() << strRegisters;
}
void VirtualMachine::OpenFileToExecute(QString fileName)
{
    //qDebug() << "Inside Execute";
    quint8 Magic1;
    quint8 Magic2;
    quint8 Magic3;
    QFile file2(fileName);
    file2.open(QIODevice::ReadOnly);

    QDataStream br(&file2);
    br >> Magic1;
    br >> Magic2;
    br >> Magic3;
    if (Magic1 != 'B' && Magic2 != '3' && Magic3 != '2')
    {
        qDebug()<< "This is not a valid B32 file!"<< "Error!";
        return;
    }
    br >> StartAddr;
    br >> ExecAddr;
    ushort Counter = 0;
    while (!(br.atEnd()))
    {
         br >> B32Memory[StartAddr + Counter];
         Counter++;
    }
    file2.close();
    qDebug()<<"the memory hexdump";
    for(int j=0;j<Counter;j++)
        qDebug()<<B32Memory[StartAddr+j];
    InstructionPointer = ExecAddr;
    qDebug()<<"execAdd"<<ExecAddr<<" IP:"<<InstructionPointer<<" Counter="<<Counter;
   // ExecuteProgram(ExecAddr, Counter);
    qDebug() << "Exiting openfile toexecute";
}


int VirtualMachine::ExecuteProgram(int ExexAddr )
{
    qDebug()<<"IP"<<InstructionPointer;
    if(ExexAddr==6400)InstructionPointer=ExecAddr;
   int ProgLength = ExexAddr;
    while (ProgLength > 0)
    {
        quint8 Instruction = B32Memory[InstructionPointer];
        qDebug()<<"Instruction:"<<Instruction;
        ProgLength--;





       if (Instruction == 0x02) // LDX #<value>
                {
                    qDebug()<<"instruction LDX";
                    Register_X = (ushort)((B32Memory[(InstructionPointer + 1)]) << 8);
                    Register_X += B32Memory[(InstructionPointer + 2)];
                    qDebug()<<"Register X="<<Register_X;
                    ProgLength -= 2;
                    qDebug()<<"IP"<<InstructionPointer;
                    InstructionPointer += 3;
                    qDebug()<<"IP"<<InstructionPointer;
                    qDebug()<<"next instruction:"<<B32Memory[InstructionPointer];
                    UpdateRegisterStatus();
                    qDebug()<<"IP"<<InstructionPointer;
                    continue;
                }


          if (Instruction == 0x01) // LDA #<value>
                {
                    qDebug()<<"LDA";
                    Register_A = (ushort)((B32Memory[(InstructionPointer + 1)]) << 8);
                    Register_A += B32Memory[(InstructionPointer + 2)];
                    ProgLength -= 2;
                    qDebug()<<"IP"<<InstructionPointer;
                    InstructionPointer += 3;
                    qDebug()<<"IP"<<InstructionPointer;
                    SetRegisterD();
                    qDebug()<<"next instruction:"<<B32Memory[InstructionPointer];
                    UpdateRegisterStatus();

                    continue;
                }
        if (Instruction == 0x11) // LDX <memory>
        {
            qDebug()<<"instruction LDX";
            ushort address= (ushort)((B32Memory[(InstructionPointer + 1)]) << 8);
            address += B32Memory[InstructionPointer+2];
            qDebug()<<"the memory address is ";
            qDebug()<<address;
            Register_X = (ushort)((B32Memory[address+1]) << 8);
             qDebug()<<"value of register X"<<Register_X;
            Register_X += B32Memory[(address)];
            qDebug()<<"value of register X"<<Register_X;
            ProgLength -= 2;
            qDebug()<<"IP"<<InstructionPointer;
            InstructionPointer += 3;
            qDebug()<<"IP"<<InstructionPointer;
            qDebug()<<"next instruction:"<<B32Memory[InstructionPointer];
            UpdateRegisterStatus();
            continue;
        }



        if (Instruction == 0x10) // LDA <memory>
        {
            qDebug()<<"LDA";
            ushort address= (ushort)((B32Memory[(InstructionPointer + 1)]) << 8);
            address += B32Memory[InstructionPointer+2];
            qDebug()<<"the memory address is ";
            qDebug()<<address;
            qDebug()<<"value at address"<< getValueAt(address);
            Register_A = (ushort)((B32Memory[address+1]) << 8);
            Register_A += B32Memory[(address )];
            qDebug()<<"value of register A "<<Register_A;
            ProgLength -= 2;
            qDebug()<<"IP"<<InstructionPointer;
            InstructionPointer += 3;
            qDebug()<<"IP"<<InstructionPointer;
            qDebug()<<"next instruction:"<<B32Memory[InstructionPointer];
            SetRegisterD();
            UpdateRegisterStatus();
            continue;
        }


        if (Instruction == 0x03) // STA ,X
        {
           ushort old= InstructionPointer;
            qDebug()<<"STA,X";
            qDebug()<<"IP 1"<< InstructionPointer;
            B32Memory[(quint8)Register_X] =(quint8) Register_A;
              qDebug()<<"IP 2"<< InstructionPointer;
            B32Memory[Register_X+1]= Register_A>>8;
              qDebug()<<"IP 3"<< InstructionPointer;
            qDebug()<<"register x"<<Register_X;
              qDebug()<<"IP 4"<< InstructionPointer;
            qDebug()<<B32Memory[Register_X];

            InstructionPointer=old;
            qDebug()<<"old pointer="<<old;
            qDebug()<<"IP"<<InstructionPointer;
            InstructionPointer++;
            qDebug()<<"IP"<<InstructionPointer;
            qDebug()<<"next instruction:"<<B32Memory[InstructionPointer];
            UpdateRegisterStatus();

            continue;
        }


        if (Instruction == 0x04) // END
        {
            qDebug()<<"END";
            InstructionPointer++;
            UpdateRegisterStatus();
            break;
        }

        if(Instruction==0x12) //wait
        {
            qDebug()<<"Wait";
            qDebug()<<"IP"<<InstructionPointer;
            InstructionPointer++;
            qDebug()<<"IP"<<InstructionPointer;
            UpdateRegisterStatus();
            return ProgLength;
        }

        if (Instruction == 0x05) // CMPA
        {
            qDebug()<<"CMPA";
        quint8 CompValue=B32Memory[InstructionPointer+1];
        CompareFlag = 0;
        if (Register_A == CompValue) CompareFlag =(quint8)(CompareFlag | 1);
        if (Register_A != CompValue) CompareFlag =(quint8)(CompareFlag | 2);
        if (Register_A  < CompValue) CompareFlag =(quint8)(CompareFlag | 4);
        if (Register_A > CompValue) CompareFlag = (quint8)(CompareFlag | 8);

        InstructionPointer += 2;
        UpdateRegisterStatus();
        continue;
        }

        if (Instruction == 0x06) // CMPB
        {
            qDebug()<<"CMPB";
        quint8 CompValue = B32Memory[InstructionPointer + 1];
        CompareFlag = 0;
        if (Register_B == CompValue) CompareFlag =(quint8)(CompareFlag | 1);
        if (Register_B != CompValue) CompareFlag =(quint8)(CompareFlag | 2);
        if (Register_B < CompValue) CompareFlag =(quint8)(CompareFlag | 4);
        if (Register_B  > CompValue) CompareFlag =(quint8)(CompareFlag | 8);

        InstructionPointer += 2;

        }

        if (Instruction == 0x07) //CMPX
        {
            qDebug()<<"CMPX";
        ushort CompValue =(ushort)((B32Memory[(InstructionPointer + 1)]) << 8);
        CompValue += B32Memory[(InstructionPointer + 2)];
        CompareFlag = 0;
        if (Register_X == CompValue) CompareFlag = (quint8)(CompareFlag | 1);
        if (Register_X!= CompValue) CompareFlag = (quint8)(CompareFlag | 2);
        if (Register_X < CompValue) CompareFlag = (quint8)(CompareFlag | 4);
        if (Register_X > CompValue) CompareFlag =(quint8)(CompareFlag | 8);
        InstructionPointer += 3;
        UpdateRegisterStatus();
        continue;
        }


        if (Instruction == 0x08) //CMPY
        {
            qDebug()<<"CMPY";
        ushort CompValue =(ushort)((B32Memory[(InstructionPointer + 1)]) << 8);
        CompValue += B32Memory[(InstructionPointer + 2)];
        CompareFlag = 0;
        if (Register_Y == CompValue) CompareFlag =(quint8)(CompareFlag | 1);
        if (Register_Y!= CompValue) CompareFlag = (quint8)(CompareFlag | 2);
        if (Register_Y < CompValue) CompareFlag = (quint8)(CompareFlag | 4);
        if (Register_Y > CompValue) CompareFlag = (quint8)(CompareFlag | 8);
        InstructionPointer += 3;
        UpdateRegisterStatus();
        continue;
        }


        if (Instruction == 0x09) //CMPD
        {
            qDebug()<<"CMPD";
        ushort CompValue =(ushort)((B32Memory[(InstructionPointer + 1)]) << 8);
        CompValue += B32Memory[(InstructionPointer + 2)];
        CompareFlag = 0;
        if (Register_D == CompValue) CompareFlag =(quint8)(CompareFlag | 1);
        if (Register_D!= CompValue) CompareFlag = (quint8)(CompareFlag | 2);
        if (Register_D < CompValue) CompareFlag = (quint8)(CompareFlag | 4);
        if (Register_D > CompValue) CompareFlag = (quint8)(CompareFlag | 8);
        InstructionPointer += 3;
        UpdateRegisterStatus();
        continue;
        }

        if (Instruction == 0x0A) // JMP
        {
            qDebug()<<"JMP";
        ushort JmpValue = (ushort)((B32Memory[(InstructionPointer + 1)]) << 8);
        JmpValue += B32Memory[(InstructionPointer + 2)];
        InstructionPointer = JmpValue;
        UpdateRegisterStatus();
        continue;
        }

        if (Instruction == 0x0B) // JEQ
        {
            qDebug()<<"JEQ";
        ushort JmpValue = (ushort)((B32Memory[(InstructionPointer +1)]) << 8);
        JmpValue += B32Memory[(InstructionPointer + 2)];
        if ((CompareFlag & 1) == 1)
        {
        InstructionPointer = JmpValue;
        }
        else
        {
        InstructionPointer += 3;
        }
        UpdateRegisterStatus();
        continue;
        }


        if (Instruction == 0x0C) // JNE
        {
            qDebug()<<"JNE";
        ushort JmpValue = (ushort)((B32Memory[(InstructionPointer +1)]) << 8);
        JmpValue += B32Memory[(InstructionPointer + 2)];
        if ((CompareFlag & 2) == 2)
        {
        InstructionPointer = JmpValue;
        }
        else
        {
        InstructionPointer += 3;
        }
        UpdateRegisterStatus();
        continue;
        }
        if (Instruction == 0x0D) // JGT
        {
            qDebug()<<"JGT";
        ushort JmpValue = (ushort)((B32Memory[(InstructionPointer + 1)]) << 8);
        JmpValue += B32Memory[(InstructionPointer + 2)];
        if ((CompareFlag & 4) == 4)
        {
        InstructionPointer = JmpValue;
        }
        else
        {
        InstructionPointer += 3;
        }
        UpdateRegisterStatus();
        continue;
        }
        if (Instruction == 0x0E) // JLT
        {
            qDebug()<<"JLT";
        ushort JmpValue = (ushort)((B32Memory[(InstructionPointer + 1)]) << 8);
        JmpValue += B32Memory[(InstructionPointer + 2)];
        if ((CompareFlag & 8) == 8)
        {
        InstructionPointer = JmpValue;
        }
        else
        {
        InstructionPointer += 3;
        }
        UpdateRegisterStatus();
        continue;
        }
        if(Instruction==0x0F) // ADD
        {
            int temp=0;
            qDebug()<<"ADD";
            quint8 r1, r2;
            qDebug()<<"IP"<<InstructionPointer;
            r1=B32Memory[InstructionPointer+1];
            r2=B32Memory[InstructionPointer+2];
            switch(r2)
            {
                case 4:
                    temp=Register_A;
                    break;
            case 2:
                temp=Register_B;
                break;
            case 1:
                temp=Register_D;
                break;
            case 16:
                temp=Register_X;
                break;
            case 8:
                temp=Register_Y;
                break;
            }
         qDebug()<<"value of temp="<<temp;
            switch(r1)
            {
                case 4:
                    Register_A+=temp;
                    qDebug()<<"result of addition A:"<<Register_A;
                    break;
            case 2:
                Register_B+=temp;
                qDebug()<<"result of addition"<<Register_B;
                break;
            case 1:
                Register_D+=temp;
                qDebug()<<"result of addition"<<Register_D;
                break;
            case 16:
                Register_X+=temp;
                qDebug()<<"result of addition X:"<<Register_X;
                break;
            case 8:
                Register_Y+=temp;
                qDebug()<<"result of addition"<<Register_Y;
                break;
            }
            qDebug()<<"IP"<<InstructionPointer;

            InstructionPointer+=3;
            qDebug()<<"IP"<<InstructionPointer;
            UpdateRegisterStatus();
            continue;
        }



    }
    return -1;
}

void VirtualMachine::setValueAt(int position, quint8 value)
{
    B32Memory[position]=value;


}

quint8 VirtualMachine::getValueAt(int position)
{
    return B32Memory[position];
}

void VirtualMachine::SetRegisterD()
{
    Register_D = (ushort)(Register_A << 8 + Register_B);
}
