#ifndef PREGUNTAFORM_H
#define PREGUNTAFORM_H

#include <QWidget>
#include <QDebug>

#include "cuestionario.h"
#include "resultadosform.h"

namespace Ui {
class PreguntaForm;
}

class PreguntaForm : public QWidget
{
    Q_OBJECT
signals:
    void cuestionarioFinalizado(int preguntasCorrectas, int totalPreguntas, float score);
public:
    explicit PreguntaForm(QWidget *parent = nullptr);
    ~PreguntaForm();


    void setCuestionario(Cuestionario *newCuestionario);

    void mostrarResumen();
private slots:
    void on_buttonBox_rejected();

    void on_buttonBox_accepted();

private:
    Ui::PreguntaForm *ui;
    Cuestionario *m_cuestionario;
    Pregunta *m_pregunta;
    ResultadosForm *m_resultadosForm;

    void cargarDatos();
    void siguiente();
    void obtenerPregunta();
};

#endif // PREGUNTAFORM_H
