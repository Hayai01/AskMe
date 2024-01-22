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

    // Crear un diseño vertical principal para organizar los elementos
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Etiqueta para el título
    QLabel *titleLabel = new QLabel("Resultados del Cuestionario", this);
    titleLabel->setFont(QFont("Arial", 18, QFont::Bold));
    titleLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(titleLabel);

    // Separador de línea
    QFrame *line = new QFrame(this);
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    layout->addWidget(line);

    // Etiqueta para preguntas correctas
    QLabel *labelPreguntasCorrectas = new QLabel(QString("Preguntas correctas: %1").arg(preguntasCorrectas), this);
    layout->addWidget(labelPreguntasCorrectas);

    // Etiqueta para total de preguntas
    QLabel *labelTotalPreguntas = new QLabel(QString("Total de preguntas: %1").arg(totalPreguntas), this);
    layout->addWidget(labelTotalPreguntas);

    // Barra de progreso para mostrar el porcentaje de respuestas correctas
    QProgressBar *progressBar = new QProgressBar(this);
    progressBar->setRange(0, 100);
    progressBar->setValue(score);
     progressBar->setTextVisible(false);
    progressBar->setStyleSheet("QProgressBar { border: 1px solid grey; background: white; } QProgressBar::chunk { background: blue; }");
    layout->addWidget(progressBar);

    // Etiqueta para score
    QLabel *labelScore = new QLabel(QString("Score: %1%").arg(score), this);
    layout->addWidget(labelScore);

    // Agrega el diseño principal al widget
    setLayout(layout);
}

ResultadosForm::~ResultadosForm()
{
    delete ui;
}
