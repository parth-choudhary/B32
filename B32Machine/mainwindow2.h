#ifndef MainWindow2_H
#define MainWindow2_H

#include <QMainWindow>
#include "virtualmachine.h"

//extern quint8 B32Memory[];
namespace Ui {
class MainWindow2;
}

class MainWindow2 : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow2(QWidget *parent = 0);
    void paintEvent(QPaintEvent *);
    void LabelSetter();
    void buildStack();
    void sort();
    void constantBuilder();
    void generateArray();
    void allocate();
    VirtualMachine *vm;


    ~MainWindow2();
private slots:
    void clicked();
    
private:
    Ui::MainWindow2 *ui;
};

#endif // MainWindow2_H
