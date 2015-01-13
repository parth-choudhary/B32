#include "mainwindow2.h"
#include "ui_mainwindow2.h"


//#include "common.h"
#include<QPainter>
#include<QLabel>
#include<QFile>
#include<QDebug>

QString LabelLine, name[100],constant[100];
int LineNo = 1,count = 0, offset[100];
int symbolCount=0;
int maxline=0;

QString Symbolname[100];
//extern quint8 B32Memory[65535];
int Symboloffset[100] ;
int position;


MainWindow2::MainWindow2(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow2)

{
    generateArray();
    vm=new VirtualMachine("/home/shikamaru/project/B32Machine/ICode.B32");
    this->showMaximized();
    ui->setupUi(this);
    sort();
    allocate();
    LabelSetter();
    position=6400;




}
void MainWindow2::generateArray()

{

    QByteArray reader,buf;
    int toggle=0,j=0,i=0;
    bool ok;

    QFile  fp("/home/shikamaru/project/B32Machine/symbols.txt");

    if(!fp.open(QIODevice::ReadOnly | QIODevice::Text))
    qDebug()<<"symbols";


    while(!fp.atEnd())

    {

        reader = fp.readLine();


        if(!toggle)
              Symbolname[j++] = reader;

        else
        {
            buf=reader.remove(reader.indexOf('\n'),1);
             qDebug()<<reader;
            Symboloffset[i++] = buf.toInt(&ok,10) ;}

        if(toggle==0)
            toggle=1;
        else
            toggle=0;

        }

    symbolCount=j;
}

void MainWindow2::sort()
{
    QString temps;
    int temp;
    int size =symbolCount;
    qDebug() <<size;
    for(int i = 0; i < (size -1); i++)
    {
        for(int j = 0; j < size-i-1; j++)
          {
            if(Symboloffset[j] > Symboloffset[j + 1])
            {
                temps = Symbolname[j];
                Symbolname[j] = Symbolname[j + 1];
                Symbolname[j + 1] = temps;

                temp = Symboloffset[j];
                Symboloffset[j] = Symboloffset[j + 1];
                Symboloffset[j + 1] = temp;

            }
        }
    }
}

void MainWindow2::allocate()
{
    bool ok;
    qDebug()<<"in allocate";
    for(int i=0;i< symbolCount;i++)
    {
        if(Symbolname[i].at(0).isDigit()){
            int number=Symbolname[i].toInt(&ok,10);
            qDebug()<<"at offset:"<< Symboloffset[i];
            vm->setValueAt(Symboloffset[i],(quint8)number);
          //  vm->B32Memory[Symboloffset[i]]=(quint8)number;
            qDebug()<<vm->getValueAt(Symboloffset[i]);
            vm->setValueAt(Symboloffset[i]+1,(quint8)(number>>8));
           // vm->B32Memory[Symboloffset[i]+1]=(quint8)(number>>8);
            //qDebug()<<vm->B32Memory[Symboloffset[i]+1];
        }
    }
}

void MainWindow2::LabelSetter()
{
    int x = 800, y = 80, h = 1000, w = 100;
    QString filename = "/home/shikamaru/project/B32Machine/test.c";
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        qDebug() << "Error";


    QTextStream input(&file);

    /*LabelLine = input.readLine();
    qDebug()<<LabelLine;*/
   do
    {
        LabelLine = input.readLine();
        count++;
       // qDebug() << LabelLine;


        QLabel * lb = new QLabel(this);
        lb->setText(LabelLine);
        lb->setGeometry(x, y, h, w);
        if(count == LineNo)
            lb->setStyleSheet("QLabel { color : red; }");
        lb->setVisible(true);

        y += 20;
    } while(!input.atEnd() );
    maxline=count;
    file.close();
}

void MainWindow2::clicked()
{
    //VirtualMachine *vm= new VirtualMachine("/home/snigdha/B32Machine/ICode.B32");
    position=vm->ExecuteProgram(position);
//    qDebug() << "clicked";
    LineNo++;
    count = 0;
    update();
    LabelSetter();


}

void MainWindow2::paintEvent(QPaintEvent *)
 {


    QString value, addr;

    int x = 20, y = 80, w = 20, h = 100, i = 0,j;
    int rectx = x + 90;
    for(j = 0; j < symbolCount; j++)
    {
        if(Symbolname[j].at(1) != '_')
          {
            name[i] = Symbolname[j];
            offset[i++] = Symboloffset[j];
          }
    }
    //qDebug()<<i;

    int noofRects = i;
    i = 0;


    QRectF crect(x, y - 25, h, w);
    QPainter painter(this);
    painter.drawText(crect,Qt::AlignCenter,"Variables");
    while(i < noofRects)
    {
        if(!(name[i].at(0).isDigit()))
        {

        QRectF rect(x, y, h, w);
        painter.drawText(rect, Qt::AlignLeft, name[i]);
        QRectF brect(rectx, y, h, w);
        painter.drawRect(brect);
        QRectF Arect(rectx, y + 20, h, w);
        value.setNum(vm->getValueAt(offset[i]), 10);
        addr.setNum(offset[i], 10);
        painter.drawText(brect, Qt::AlignCenter, value );
        painter.drawText(Arect, Qt::AlignCenter, addr);

        y += 60;
        }
        i++;

    }
    if(LineNo<(maxline+2)) buildStack();
    constantBuilder();

}
void MainWindow2::constantBuilder()
{
    int x = 100, y = 680, w = 35, h = 140;
    int j = 0;
    int Caddr[100];
    for(int i = 0; i < symbolCount; i++)
    {
        if(Symbolname[i].at(0).isDigit())
        {
            constant[j] = Symbolname[i];
            Caddr[j++] = Symboloffset[i];
        }
    }

    QRectF drect(x - 90,y,h,w);
    QPainter painter(this);
    painter.drawText(drect,Qt::AlignLeft, "Constants");
    for(int i = 0; i < j; i++)
    {
        QRectF rect(x, y, h, w);
        painter.drawRect(rect);
        painter.drawText(rect,Qt::AlignCenter, constant[i]);
        QString address;
        address.setNum(Caddr[i],10);
        painter.drawText(rect,Qt::AlignRight,address);
        x += h;
    }
}

void MainWindow2::buildStack()
{
    int x = 300, y = 80, w = 30, h = 140;
    QString value, addr;

    QPainter painter(this);
    QRectF drect(x, y - 30, h , w);
    painter.drawText(drect,Qt::AlignCenter,"Stack");
    for(int i = 0; i < symbolCount; i++)
    {
        if(!(Symbolname[i].at(0).isDigit()))
        {
            value.setNum(vm->getValueAt(Symboloffset[i]),10);
            addr.setNum(Symboloffset[i]);
            QRectF rect (x, y, h, w);

            painter.drawRect(rect);
            painter.drawText(rect,Qt::AlignCenter, value);
            painter.drawText(rect,Qt::AlignLeft,addr);
            painter.drawText(rect,Qt::AlignRight,Symbolname[i]);
            y += w;
        }
    }

}


MainWindow2::~MainWindow2()
{
    delete ui;
}
