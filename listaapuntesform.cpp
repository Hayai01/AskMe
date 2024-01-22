
#include "listaapuntesform.h"
#include "ui_listaapuntesform.h"

ListaApuntesForm::ListaApuntesForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ListaApuntesForm)
{
    ui->setupUi(this);
}

ListaApuntesForm::~ListaApuntesForm()
{
    delete ui;
}
