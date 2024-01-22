#include "creditosform.h"
#include "ui_creditosform.h"

CreditosForm::CreditosForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreditosForm)
{
    ui->setupUi(this);
    QStringList colaboradores = {"Joseph Uyana ", "Rodrigo Tufiño", "Mateo Espinosa"};

        // Construir la cadena de créditos
        QString creditos;
        for (const QString &nombre : colaboradores)
        {
            creditos += "- " + nombre + "\n";
        }

        // Mostrar los créditos en el QTextEdit (puedes usar otro widget según tu diseño)
        ui->textEditCreditos->setPlainText(creditos);
}

CreditosForm::~CreditosForm()
{
    delete ui;
}
