#ifndef LISTAFORM_H
#define LISTAFORM_H

#include <QWidget>
#include <Asignatura.h>

namespace Ui {
class ListaForm;
}

class ListaForm : public QWidget
{
    Q_OBJECT

public:
    explicit ListaForm(QWidget *parent = nullptr);
    ~ListaForm();

private:
    Ui::ListaForm *ui;
    void generarListaApuntes();
    QList<Asignatura*> m_asignaturas;
};

#endif // LISTAFORM_H
