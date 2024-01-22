// En resultadosform.cpp

#include "resultadosform.h"
#include "ui_resultadosform.h"
#include <QLabel>
#include <QProgressBar>
#include <QVBoxLayout>

ResultadosForm::ResultadosForm(int preguntasCorrectas, int totalPreguntas, float score, QWidget *parent)
    : QWidget(parent), ui(new Ui::ResultadosForm)
{
    ui->setupUi(this);

    // Etiqueta para el título
    ui->titleLabel->setFont(QFont("Arial", 24, QFont::Bold));  // Aumenta el tamaño de la fuente
    ui->titleLabel->setAlignment(Qt::AlignCenter);

    // Separador de línea
    ui->line->setFrameShape(QFrame::HLine);
    ui->line->setFrameShadow(QFrame::Sunken);

    // Etiqueta para preguntas correctas
    ui->labelPreguntasCorrectas->setText(QString("Preguntas correctas: %1").arg(preguntasCorrectas));

    // Etiqueta para total de preguntas
    ui->labelTotalPreguntas->setText(QString("Total de preguntas: %1").arg(totalPreguntas));

    // Barra de progreso para mostrar el porcentaje de respuestas correctas
    ui->progressBar->setRange(0, 100);
    ui->progressBar->setValue(score);
    ui->progressBar->setTextVisible(false);
    ui->progressBar->setStyleSheet("QProgressBar { border: 1px solid grey; background: white; } QProgressBar::chunk { background: blue; }");

    // Etiqueta para score
    ui->labelScore->setText(QString("Score: %1%").arg(score));

    // Ajustar el tamaño mínimo del formulario principal
    setMinimumSize(400, 300);  // Establece el tamaño mínimo deseado
}

ResultadosForm::~ResultadosForm()
{
    delete ui;
}
