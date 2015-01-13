#include <QtGui/QApplication>
#include<QProcess>
#include<QDebug>

#include "mainwindow.h"
//#include "common.h"



int main(int argc, char *argv[])
{

    QByteArray ab,error;
QApplication a(argc, argv);

   /*
    if(!mp->waitForStarted())
        qDebug()<<"didnt start";
    if(!mp->waitForFinished())
        qDebug()<<"didnt finish";
   ab=mp->readAllStandardOutput();
   error=mp->readAllStandardError();

    qDebug()<<ab;
    qDebug()<<error;
   /* QProcess process;
    QProcess Oprocess, tprocess;
    process.start(command, QStringList() << "-d /home/snigdha/B32Machine/parser.y");
    process.waitForFinished();
    process.start("flex", QStringList() << "/home/snigdha/B32Machine/scanner.l");
    process.waitForFinished();
    process.start("gcc", QStringList() << "/home/snigdha/B32Machine/parser.tab.c /home/snigdha/B32Machine/lex.yy.c");
    process.waitForFinished();*/
   // system("/home/snigdha/B32Machine/a.out");
    //setinput("test.c");
    //yyparse();



        //Oprocess.start("cat new.txt");
    MainWindow w;
    w.show();
    
    return a.exec();
}
