#include "askme.h"

#include <QApplication>
#include <QDebug>

#include "asignatura.h"
#include "cuestionario.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Askme w;
    w.show();


    return a.exec();
}














