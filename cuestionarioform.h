#ifndef CUESTIONARIOFORM_H
#define CUESTIONARIOFORM_H

#include <QWidget>

#include "preguntaform.h"

#include "asignatura.h"
#include "cuestionario.h"

namespace Ui {
class CuestionarioForm;
}

class CuestionarioForm : public QWidget
{
    Q_OBJECT

public:
    explicit CuestionarioForm(QWidget *parent = nullptr);
    ~CuestionarioForm();

    void setAsignaturas(QList<Asignatura *> &newAsignaturas);
    void cargarAsignaturas();

signals:
    void cuestionarioCreado(Cuestionario *cuestionario);


private slots:
    void on_cmbAsignaturas_currentIndexChanged(int index);

    void on_buttonBox_accepted();

private:
    Ui::CuestionarioForm *ui;
    QList<Asignatura*> *m_asignaturas;
};

#endif // CUESTIONARIOFORM_H
