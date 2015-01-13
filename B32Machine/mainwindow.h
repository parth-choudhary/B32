#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QHash>
//#include"virtualmachine.h"



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);


    ~MainWindow();

private slots:
    void btnSourceFileNameClicked();
    void btnAssembleClicked();

    
private:
    Ui::MainWindow *ui;
    QString SourceProgram;
    QString Origin;
    int CurrentNdx;
    unsigned short AsLength;
    bool IsEnd;
    unsigned short ExecutionAddress;
    QHash<QString,unsigned short> LabelTable;
    //QDataStream out;
    enum Registers
    {
    Unknown = 0,
    A = 4,
    B = 2,
    D = 1,
    X = 16,
    Y = 8
    };
    void parse(QDataStream& out);
    void LabelScan( QDataStream& out,bool isLabelScan);
    void ReadMneumonic(QDataStream& out, bool isLabelScan);
    void InterpretLDA(QDataStream& out, bool isLabelScan);
    void InterpretLDX(QDataStream& out, bool isLabelScan);
    void InterpretSTA(QDataStream &out, bool isLabelScan);
    void InterpretCMPA(QDataStream &out, bool isLabelScan);
    void InterpretCMPB(QDataStream &out, bool isLabelScan);
    void InterpretCMPD(QDataStream &out, bool isLabelScan);
    void InterpretCMPX(QDataStream &out, bool isLabelScan);
    void InterpretCMPY(QDataStream &out, bool isLabelScan);
    void InterpretJMP(QDataStream &out, bool isLabelScan);
    void InterpretJEQ(QDataStream &out, bool isLabelScan);
    void InterpretJLT(QDataStream &out, bool isLabelScan);
    void InterpretJGT(QDataStream &out, bool isLabelScan);
    void InterpretJNE(QDataStream &out, bool isLabelScan);
     void InterpretADD(QDataStream &out, bool isLabelScan);
     void InterpretWait(QDataStream &out, bool isLabelScan);


    void DoEnd(QDataStream& out, bool isLabelScan);
    Registers ReadRegister();
    ushort ReadWordValue();
    quint8 ReadByteValue();
    void EatWhiteSpaces();
    QString GetLabelName();


};

#endif // MAINWINDOW_H
