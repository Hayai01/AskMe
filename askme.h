#ifndef ASKME_H
#define ASKME_H

#include <QMainWindow>
#include <QMdiSubWindow>
#include <QListWidgetItem>
#include <QDialog>
#include <QVBoxLayout>
#include <QApplication>
#include <QComboBox>
#include <QFile>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>
#include <QTreeWidget>
#include <QStandardItemModel>
#include <QTreeView>



#include "apunteform.h"
#include "cuestionarioform.h"
#include "preguntaform.h"
#include "creditosform.h"


#include "asignatura.h"


QT_BEGIN_NAMESPACE
namespace Ui { class Askme; }
QT_END_NAMESPACE

class Askme : public QMainWindow
{
    Q_OBJECT

public:
    Askme(QWidget *parent = nullptr);
    ~Askme();


public slots:
    void on_apunteTomado(Apunte *apunte);
    void on_cuestionarioCreado(Cuestionario *cuestionario);
    void on_resultadosCreado(int preguntasCorrectas, int totalPreguntas, float score);

private slots:
    void on_actionNuevo_triggered();
    void on_actionLista_triggered();
    void on_actionGenerar_triggered();

    void on_actionCreditos_triggered();

private:
    Ui::Askme *ui;
    void cargarSubVentana(QWidget *ventana);
    void cargarDatos();
    void guardar();
    void mostrarListaApuntes();

    QList<Asignatura*> m_asignaturas;
    QList<Apunte*> m_listaApuntes;

    QListWidget *listaWidget;

    QComboBox *comboAsignaturas;
    QComboBox *comboTemas;
    void actualizarTablaApuntes(QDialog *dialogo, int indexAsignatura, int indexTema);
    void cargarEstilos();
};
#endif // ASKME_H
