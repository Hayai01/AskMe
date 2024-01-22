#include "cuestionarioform.h"
#include "ui_cuestionarioform.h"

CuestionarioForm::CuestionarioForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CuestionarioForm)
{
    ui->setupUi(this);
}

CuestionarioForm::~CuestionarioForm()
{
    delete ui;
}

void CuestionarioForm::setAsignaturas(QList<Asignatura *> &asignaturas)
{
    m_asignaturas = &asignaturas;
}

void CuestionarioForm::cargarAsignaturas()
{
    ui->cmbAsignaturas->clear();
    foreach(Asignatura *a, *m_asignaturas){
        ui->cmbAsignaturas->addItem(a->nombre());
    }
}

void CuestionarioForm::on_cmbAsignaturas_currentIndexChanged(int index)
{
    ui->cmbTemas->clear();
    if (index >= 0 && index < m_asignaturas->size()){
        Asignatura *a = m_asignaturas->at(index);
        foreach(Tema *t, a->temas()){
            ui->cmbTemas->addItem(t->nombre());
        }
    }
}


void CuestionarioForm::on_buttonBox_accepted()
{
    // Obtener nos indices d elos combos
    int indexAsignatura = ui->cmbAsignaturas->currentIndex();
    int indextema = ui->cmbTemas->currentIndex();
    // Crear la tarea
    Tema *t = m_asignaturas->at(indexAsignatura)->temas().at(indextema);
    // Emitir señal
    emit cuestionarioCreado(new Cuestionario(t));
    // Cerrar la ventana
    this->parentWidget()->close();
}

