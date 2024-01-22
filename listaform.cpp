// En ListaForm.cpp

#include "listaform.h"
#include <QListWidgetItem>

ListaForm::ListaForm(QWidget *parent)
    : QWidget(parent), ui(new Ui::ListaForm)
{
    ui->setupUi(this);

    // Puedes personalizar el estilo del QListWidget
    ui->listaWidget->setStyleSheet("QListWidget { background-color: #f0f0f0; }"
                                   "QListWidget::item { background-color: #ffffff; border: 1px solid #d3d3d3; }"
                                   "QListWidget::item:selected { background-color: #a0a0a0; }");

    // Puedes agregar más personalizaciones según sea necesario
}



void ListaForm::generarListaApuntes()
{
    // Limpiar la lista previa
    ui->listaWidget->clear();

    foreach (Asignatura *asignatura, m_asignaturas)
    {
        foreach (Tema *tema, asignatura->temas())
        {
            foreach (Apunte *apunte, tema->apuntes())
            {
                QString texto = QString("%1 - %2: %3")
                                    .arg(asignatura->nombre())
                                    .arg(tema->nombre())
                                    .arg(apunte->toString());

                QListWidgetItem *item = new QListWidgetItem(texto);

                // Puedes personalizar el estilo de cada item si lo deseas
                item->setBackground(QBrush(QColor("#ffffff")));

                ui->listaWidget->addItem(item);
            }
        }
    }
}
