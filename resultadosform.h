#ifndef RESULTADOSFORM_H
#define RESULTADOSFORM_H

#include <QWidget>

namespace Ui {
class ResultadosForm;
}

class ResultadosForm : public QWidget
{
    Q_OBJECT

public:
    explicit ResultadosForm(int preguntasCorrectas, int totalPreguntas, float score, QWidget *parent = nullptr);
    ~ResultadosForm();

private:
    Ui::ResultadosForm *ui;

    // Añade widgets u objetos necesarios para mostrar la información
};

#endif // RESULTADOSFORM_H
