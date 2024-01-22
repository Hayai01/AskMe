#include "preguntaform.h"
#include "ui_preguntaform.h"

#include <QMessageBox>

PreguntaForm::PreguntaForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PreguntaForm)
{
    ui->setupUi(this);
}

PreguntaForm::~PreguntaForm()
{
    delete ui;
}

void PreguntaForm::setCuestionario(Cuestionario *newCuestionario)
{
    m_cuestionario = newCuestionario;
    cargarDatos();
}

void PreguntaForm::cargarDatos()
{
    ui->lblTema->setText(m_cuestionario->nombreTema());
    ui->cmbTerminos->addItems(m_cuestionario->terminos());
    obtenerPregunta();
}

void PreguntaForm::siguiente()
{
    QString termino = ui->cmbTerminos->currentText();
    m_pregunta->responder(termino);
    obtenerPregunta();
}

void PreguntaForm::obtenerPregunta()
{
    if (m_cuestionario->hayMasPreguntas()){
        m_pregunta = m_cuestionario->siguiente();
        ui->txtConcepto->setText(m_pregunta->apunte()->concepto());
        int actual = m_cuestionario->mostradas();
        int total = m_cuestionario->totalPreguntas();
        ui->lblContador->setText(QString::number(actual) + " / " + QString::number(total));
    }else{
        m_cuestionario->terminar();
        emit cuestionarioFinalizado(m_cuestionario->preguntasCorrectas(), m_cuestionario->totalPreguntas(), m_cuestionario->score());
        this->parentWidget()->close();
    }

}


void PreguntaForm::on_buttonBox_rejected()
{
    // Mostrar un cuadro de diálogo de confirmación
    QMessageBox::StandardButton reply = QMessageBox::question(
        this,
        "Confirmación",
        "¿Está seguro de cerrar la ventana?",
        QMessageBox::Yes | QMessageBox::No
        );

    // Si el usuario confirma, cerrar y eliminar la ventana
    if (reply == QMessageBox::Yes) {
        this->parentWidget()->close();
    }
}



void PreguntaForm::on_buttonBox_accepted()
{
    siguiente();
}

