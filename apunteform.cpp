#include "apunteform.h"
#include "ui_apunteform.h"

ApunteForm::ApunteForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ApunteForm)
{
    ui->setupUi(this);
}

ApunteForm::~ApunteForm()
{
    delete ui;
}

void ApunteForm::setAsignaturas(QList<Asignatura *> &asignaturas)
{
    m_asignaturas = &asignaturas;
}

void ApunteForm::cargarAsignaturas()
{
    ui->cmbAsignaturas->clear();
    foreach(Asignatura *a, *m_asignaturas){
        ui->cmbAsignaturas->addItem(a->nombre());
    }
}

void ApunteForm::on_btnAgregarAsignatura_released()
{
    bool ok;
    QString nombre = QInputDialog::getText(this,"Nueva asignatura","Nombre",QLineEdit::Normal,"",&ok);

    if (ok && !nombre.isEmpty()){
        m_asignaturas->append(new Asignatura(nombre));
        cargarAsignaturas();
        ui->cmbAsignaturas->setCurrentText(nombre);
    }
}

void ApunteForm::on_btnRefAsig_clicked()
{
    cargarAsignaturas();
}


void ApunteForm::on_cmbAsignaturas_currentIndexChanged(int index)
{
    ui->cmbTemas->clear();
    if (index >= 0 && index < m_asignaturas->size()){
        Asignatura *a = m_asignaturas->at(index);
        foreach(Tema *t, a->temas()){
            ui->cmbTemas->addItem(t->nombre());
        }
    }
}


void ApunteForm::on_btnAgregarTema_released()
{
    bool ok;
    QString nombre = QInputDialog::getText(this,"Nuevo tema","Nombre",QLineEdit::Normal,"",&ok);

    if (ok && !nombre.isEmpty()){
        int index = ui->cmbAsignaturas->currentIndex();
        m_asignaturas->at(index)->agregarTema(new Tema(nombre));
        on_cmbAsignaturas_currentIndexChanged(index);
        ui->cmbTemas->setCurrentText(nombre);
    }
}


void ApunteForm::on_buttonBox_accepted()
{
    int asignaturaIndex = ui->cmbAsignaturas->currentIndex();
    int temaIndex = ui->cmbTemas->currentIndex();
    QString termino = ui->txtTermino->text();
    QString concepto = ui->txtConcepto->toPlainText();

    if (asignaturaIndex < 0){
        QMessageBox::warning(this, "Agregar apunte", "No se ha seleccionado una asignatura");
        ui->cmbAsignaturas->setFocus();
        return;
    }

    if (temaIndex < 0){
        QMessageBox::warning(this, "Agregar apunte", "No se ha seleccionado un tema");
        ui->cmbTemas->setFocus();
        return;
    }

    if (termino.isEmpty()){
        QMessageBox::warning(this, "Agregar apunte", "El término no pueden estar vacío");
        ui->txtTermino->setFocus();
        return;
    }

    if (concepto.isEmpty()){
        QMessageBox::warning(this, "Agregar apunte", "El concepto no pueden estar vacío");
        ui->txtConcepto->setFocus();
        return;
    }
    // Crear el nuevo apunte
    Apunte *apunte = new Apunte(termino, concepto);
    // Obtener la asignatura seleccionada
    Asignatura *a = m_asignaturas->at(asignaturaIndex);
    // Agregar el apunte al tema seleccionado
    a->temas().at(temaIndex)->agregarApunte(apunte);
    // Emitir una señal
    emit apunteTomado(apunte);
    // Cerrar la ventana
    this->parentWidget()->close();
}


void ApunteForm::on_buttonBox_rejected()
{
    this->parentWidget()->close();
}

