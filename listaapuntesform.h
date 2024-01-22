#ifndef LISTAAPUNTESFORM_H
#define LISTAAPUNTESFORM_H

#include <QWidget>

namespace Ui {
class ListaApuntesForm;
}

class ListaApuntesForm : public QWidget
{
    Q_OBJECT

public:
    explicit ListaApuntesForm(QWidget *parent = nullptr);
    ~ListaApuntesForm();

private:
    Ui::ListaApuntesForm *ui;
};

#endif // LISTAAPUNTESFORM_H
