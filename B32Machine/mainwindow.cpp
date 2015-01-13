#include<QtGui>
#include<QFile>


#include "ui_mainwindow.h"
#include "mainwindow2.h"
//#include "common.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->btnSourceBrowse,SIGNAL(clicked()),this,SLOT(btnSourceFileNameClicked()));

    connect(ui->btnAssemble,SIGNAL(clicked()),this,SLOT(btnAssembleClicked()));


    //initialize the variables
    CurrentNdx = 0;
    AsLength = 0;
    ExecutionAddress = 0;
    IsEnd = false;
    SourceProgram = "";
    Origin="1000";
    //ui->txtOrigin->setText("1000");

}



void MainWindow::btnSourceFileNameClicked()
{
    QString fileName=QFileDialog::getOpenFileName(this, tr("Open File"),
                                                  "",
                                                  tr("C sourcefiles (*.c)"));
    ui->txtSourceFIleName->setText(fileName);
}




void MainWindow::btnAssembleClicked()
{
    bool ok;
    QString command = "/home/shikamaru/project/B32Machine/a.out " +ui->txtSourceFIleName->text();

        system(command.toStdString().c_str());

  AsLength = Origin.toUShort(&ok,16);
  QFile sourceFile("/home/shikamaru/project/B32Machine/ICode.asm");
  if (!sourceFile.open(QIODevice::ReadOnly | QIODevice::Text))
           return;

  QTextStream in(&sourceFile);
  SourceProgram=in.readAll();
  sourceFile.close();


  QFile outputFile("/home/shikamaru/project/B32Machine/ICode.B32");
  if (!outputFile.open(QIODevice::WriteOnly | QIODevice::Text))
           return;

  QDataStream out(&outputFile);
  out << (quint8)'B';
  out<<(quint8)'3';
  out<<(quint8)'2';


  QString add=Origin;
       out<<add.toUShort(&ok,16);
//       out<<ui->txtOrigin->text().toUShort(&ok,16);
       out<<(quint16)0x0;
       parse(out);
       // ExecutionAddress=0x32;
       outputFile.reset();
       outputFile.seek(5);

       out<<ExecutionAddress;
       outputFile.close();

    // new VirtualMachine(outputFile.fileName());
     this->close();
       MainWindow2 *win= new MainWindow2();
     win->show();



}

void MainWindow::parse(QDataStream& out)
{
    CurrentNdx = 0;
    bool ok;
    while (IsEnd == false)
        LabelScan(out,true);
    IsEnd = false;
    CurrentNdx = 0;
    QString add = Origin;
    AsLength = add.toUShort(&ok,16);
    while (IsEnd == false)
        LabelScan(out,false);


}

void MainWindow::LabelScan(QDataStream &out, bool isLabelScan)
{
    if(SourceProgram[CurrentNdx].isLetter())
     {
    // Must be a label

        if (isLabelScan) LabelTable.insert(GetLabelName(),AsLength);
        while (SourceProgram[CurrentNdx] != '\n')
            CurrentNdx++;
        CurrentNdx++;
        return;
    }
    EatWhiteSpaces();
    ReadMneumonic(out, isLabelScan);

}

void MainWindow::ReadMneumonic(QDataStream &out, bool isLabelScan)
{
    QString Mneumonic = "";
    while (!(SourceProgram[CurrentNdx].isSpace()))
    {
    Mneumonic += SourceProgram[CurrentNdx];
    CurrentNdx++;
    }
    if (Mneumonic.toUpper() == "LDX")
        InterpretLDX(out,isLabelScan);

    if (Mneumonic.toUpper() == "LDA")
        InterpretLDA(out,isLabelScan);

    if (Mneumonic.toUpper() == "STA")
        InterpretSTA(out,isLabelScan);

    if (Mneumonic.toUpper() == "CMPA")
        InterpretCMPA(out,isLabelScan);

    if (Mneumonic.toUpper() == "CMPB")
        InterpretCMPB(out,isLabelScan);

    if (Mneumonic.toUpper() == "CMPX")
        InterpretCMPX(out,isLabelScan);

    if (Mneumonic.toUpper() == "CMPY")
        InterpretCMPY(out,isLabelScan);

    if (Mneumonic.toUpper() == "CMPD")
        InterpretCMPD(out,isLabelScan);

    if (Mneumonic.toUpper() == "JMP")
        InterpretJMP(out,isLabelScan );

    if (Mneumonic.toUpper() == "JEQ")
        InterpretJEQ(out, isLabelScan );

    if (Mneumonic.toUpper() == "JNE")
        InterpretJNE(out, isLabelScan );

    if (Mneumonic.toUpper() == "JGT")
        InterpretJGT(out, isLabelScan );

    if (Mneumonic.toUpper() == "JLT")
        InterpretJLT(out, isLabelScan );

    if (Mneumonic.toUpper() == "ADD")
        InterpretADD(out, isLabelScan );
    if (Mneumonic.toUpper() == "WAIT")
        InterpretWait(out, isLabelScan );

    if (Mneumonic.toUpper() == "END")
        {
            IsEnd = true;
            DoEnd(out,isLabelScan);
            EatWhiteSpaces();
            ExecutionAddress =(ushort)LabelTable[(GetLabelName())];
            return;
        }
    while (SourceProgram[CurrentNdx] != '\n')
    {
    CurrentNdx++;
    }
    CurrentNdx++;

}

void MainWindow::InterpretLDA(QDataStream &out, bool isLabelScan)
{
    qDebug()<<"reading LDA\n";
    EatWhiteSpaces();
    if (SourceProgram[CurrentNdx] == '#')
    {
        CurrentNdx++;
        ushort val = ReadWordValue();
        AsLength += 3;
        if (!isLabelScan)
        {

            out<<(quint8)0x01;
            out<<(val);
        }
    }
    else
    {

        ushort val =ReadWordValue();
        AsLength+=3;
        if (!isLabelScan)
        {

            out<<(quint8)0x10;
            out<<(val);
        }
    }


}

void MainWindow::InterpretLDX( QDataStream &out, bool isLabelScan)
{
    qDebug()<<"reading LDX\n";
    EatWhiteSpaces();
    if (SourceProgram[CurrentNdx] == '#')
    {
        CurrentNdx++;
        ushort val = ReadWordValue();
        qDebug()<<"val="<<val;
        AsLength += 3;
        if (!isLabelScan)
        {
            out<<(quint8)0x02;
            out<<val;
        }
    }
    else
    {

        ushort val =ReadWordValue();
        qDebug()<<"val="<<val;
        AsLength+=3;
        if (!isLabelScan)
        {

            out<<(quint8)0x11;
            out<<(val);
        }
    }


}

void MainWindow::InterpretSTA(QDataStream &out, bool isLabelScan)
{
    qDebug()<<"reading STA\n";
    EatWhiteSpaces();
    if (SourceProgram[CurrentNdx] == ',')
    {
        Registers r;
        quint8 opcode = 0x00;
        CurrentNdx++;
        EatWhiteSpaces();
        r = ReadRegister();
        switch (r)
        {
            case X:
            opcode = 0x03;
            break;
        }
        AsLength += 1;
        if (!isLabelScan)
        {
            out<<opcode;
        }
    }


}

void MainWindow::InterpretCMPA(QDataStream &out, bool isLabelScan)
{
    EatWhiteSpaces();
    if (SourceProgram[CurrentNdx] == '#')
    {
        CurrentNdx++;
        quint8 val = ReadByteValue();
        AsLength += 2;
        if (!isLabelScan)
        {
            out<<(quint8)0x05;
            out<<val;
        }
    }
}


void MainWindow::InterpretCMPB(QDataStream &out, bool isLabelScan)
{
    EatWhiteSpaces();
    if (SourceProgram[CurrentNdx] == '#')
    {
        CurrentNdx++;
        quint8 val = ReadByteValue();
        AsLength += 2;
        if (!isLabelScan)
        {
            out<<(quint8)0x06;
            out<<val;
        }
    }
}


void MainWindow::InterpretCMPX(QDataStream &out, bool isLabelScan)
{
    EatWhiteSpaces();
    if (SourceProgram[CurrentNdx] == '#')
    {
        CurrentNdx++;
        ushort val = ReadWordValue();
        AsLength += 3;
        if (!isLabelScan)
        {
            out<<(quint8)0x07;
            out<<(val);
        }
    }
}


void MainWindow::InterpretCMPY(QDataStream &out, bool isLabelScan)
{
    EatWhiteSpaces();
    if (SourceProgram[CurrentNdx] == '#')
    {
        CurrentNdx++;
        ushort val = ReadWordValue();
        AsLength += 3;
        if (!isLabelScan)
        {
            out<<(quint8)0x08;
            out<<(val);
        }
    }
}


void MainWindow::InterpretCMPD(QDataStream &out, bool isLabelScan)
{
    EatWhiteSpaces();
    if (SourceProgram[CurrentNdx] == '#')
    {
        CurrentNdx++;
        ushort val = ReadWordValue();
        AsLength += 3;
        if (!isLabelScan)
        {
            out<<(quint8)0x09;
            out<<(val);
        }
    }
}

void MainWindow::InterpretJMP(QDataStream &out, bool isLabelScan)
{
    EatWhiteSpaces();
    if (SourceProgram[CurrentNdx] == '#')
    {
        CurrentNdx++;
        AsLength += 3;
        if (isLabelScan) return;
        ushort val = ReadWordValue();
        if (!isLabelScan)
        {
            out<<(quint8)0x0A;
            out<<val;
        }
    }
}

void MainWindow::InterpretJEQ(QDataStream &out, bool isLabelScan)
{
    EatWhiteSpaces();
    if (SourceProgram[CurrentNdx] == '#')
    {
        CurrentNdx++;
        AsLength += 3;
        if (isLabelScan) return;
        ushort val = ReadWordValue();
        if (!isLabelScan)
        {
            out<<(quint8)0x0B;
            out<<val;
        }
    }
}

void MainWindow::InterpretJNE(QDataStream &out, bool isLabelScan)
{
EatWhiteSpaces();
if (SourceProgram[CurrentNdx] == '#')
{
CurrentNdx++;
AsLength += 3;
if (isLabelScan) return;
ushort val = ReadWordValue();
if (!isLabelScan)
{
out<<(quint8)0x0C;
out<<(val);
}
}
}


void MainWindow::InterpretJGT(QDataStream &out, bool isLabelScan)
{
EatWhiteSpaces();
if (SourceProgram[CurrentNdx] == '#')
{
CurrentNdx++;
AsLength += 3;
if (isLabelScan) return;
ushort val = ReadWordValue();
if (!isLabelScan)
{
    out<<(quint8)0x0D;
    out<<(val);
}
}
}
void MainWindow::InterpretJLT(QDataStream &out, bool isLabelScan)
{
EatWhiteSpaces();
if (SourceProgram[CurrentNdx] == '#')
{
CurrentNdx++;
AsLength += 3;
if (isLabelScan) return;
ushort val = ReadWordValue();
if (!isLabelScan)
{
out<<(quint8)0x0E;
out<<(val);
}
}
}

void MainWindow::InterpretADD(QDataStream &out, bool isLabelScan)
{
    qDebug()<<"reading ADD\n";
    EatWhiteSpaces();
    Registers r1,r2;
    r1=ReadRegister();
    EatWhiteSpaces();
    CurrentNdx++;
    r2=ReadRegister();
    AsLength+=3;
    if(!isLabelScan)
    {
        out<<(quint8)0x0F;
        out<<(quint8)r1;
        out<<(quint8)r2;
    }


}

void MainWindow::InterpretWait(QDataStream &out, bool isLabelScan)
{
    AsLength++;
    if (!isLabelScan)
    {
    out<<(quint8)0x12;
    }
}

void MainWindow::DoEnd(QDataStream &out, bool isLabelScan)
{
    AsLength++;
    if (!isLabelScan)
    {
    out<<(quint8)0x04;
    }

}

MainWindow::Registers MainWindow::ReadRegister()
{
    Registers r = Unknown;
    if ((SourceProgram[CurrentNdx]=='X') ||(SourceProgram[CurrentNdx]=='x'))
        r= X;
    if ((SourceProgram[CurrentNdx]=='Y')||(SourceProgram[CurrentNdx]=='y'))
        r=Y;
    if ((SourceProgram[CurrentNdx]=='D')||(SourceProgram[CurrentNdx]=='d'))
        r=D;
    if ((SourceProgram[CurrentNdx]=='A')||(SourceProgram[CurrentNdx]=='a'))
        r=A;
    if ((SourceProgram[CurrentNdx]=='B')||(SourceProgram[CurrentNdx]=='b'))
        r=B;
    CurrentNdx++;
    return r;


}

ushort MainWindow::ReadWordValue()
{
    ushort val = 0;
    bool ok;
    bool IsHex = false;
    QString sval = "";
    if (SourceProgram[CurrentNdx] == '$')
    {
        CurrentNdx++;
        IsHex = true;
    }
    if ((IsHex == false) && (SourceProgram[CurrentNdx].isLetter()))
    {
    val = (ushort)LabelTable[GetLabelName()];
    return val;
    }

    while (SourceProgram[CurrentNdx].isLetterOrNumber())
    {
        sval += SourceProgram[CurrentNdx];
        CurrentNdx++;
    }
    if (IsHex)
    {

        val = sval.toUShort(&ok, 16);
    }
    else
    {
         val = sval.toUShort(&ok,10);
    }
    return val;

}

quint8 MainWindow::ReadByteValue()
{
    quint8 val = 0;
    bool IsHex = false,ok;

    QString sval = "";
    if (SourceProgram[CurrentNdx] == '$')
    {
        CurrentNdx++;
        IsHex = true;
    }
    while (SourceProgram[CurrentNdx].isLetterOrNumber())
    {
        sval += SourceProgram[CurrentNdx];
        CurrentNdx++;
    }
    if (IsHex)
    {
        val= (quint8)sval.toUShort(&ok,16);

    }
    else
    {
    val = (quint8)sval.toUShort(&ok,10);
    }
    return val;

}

void MainWindow::EatWhiteSpaces()
{
    while (SourceProgram[CurrentNdx].isSpace())
    {
    CurrentNdx++;
    }

}


QString MainWindow:: GetLabelName()
{
    QString lblname = "";
    while ((SourceProgram[CurrentNdx]).isLetterOrNumber())
    {
    if (SourceProgram[CurrentNdx] == ':')
    {
        CurrentNdx++;
        break;
    }
    lblname += SourceProgram[CurrentNdx];
    CurrentNdx++;
}
return lblname.toUpper();
}




MainWindow::~MainWindow()
{
    delete ui;
}
