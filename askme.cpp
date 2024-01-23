#include "askme.h"
#include "ui_askme.h"

#include <QTableWidget>


Askme::Askme(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Askme)
{
    ui->setupUi(this);
    cargarDatos();


    // Aplicar un estilo general a la ventana principal
    this->setStyleSheet(
        "background-color: #333333; /* Fondo gris oscuro */"
        "color: #F2F1EB; /* Color de texto claro */"
        "font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;"
        "font-size: 14px; /* Tamaño de letra */"
        "border-radius: 15px; /* Bordes muy redondeados */"
        );

    // Establecer bordes redondos y fondo para todos los QPushButton
    QString elementStyle =
        "QComboBox, QLineEdit, QTextEdit, QTableWidget, QStringList {"
        "   background-color: #F2F1EB; /* Color claro para QComboBox y QLineEdit */"
        "   color: #333333; /* Color de texto oscuro */"
        "   border: 2px solid #666666; /* Borde sólido */"
        "   border-radius: 8px; /* Bordes redondeados */"
        "   padding: 5px; /* Relleno interno */"
        "}"
        "QPushButton {"
        "   background-color: #333333; /* Color de fondo de botón principal */"
        "   color: #F2F1EB; /* Color de texto en botón principal */"
        "   padding: 10px 20px; /* Relleno interno */"
        "   border: 2px solid #666666; /* Borde sólido */"
        "   border-radius: 15px; /* Bordes muy redondeados */"
        "   font-size: 14px; /* Tamaño de letra */"
        "   font-weight: bold; /* Texto en negrita */"
        "}"
        "QPushButton:hover {"
        "   background-color: #444444; /* Cambio de color al pasar el ratón */"
        "}"
       "QHeaderView::section {"
            "background-color: #333333; /* Color de fondo para los índices */"
        "   color: #F2F1EB; /* Color del texto para los índices */"
             "}";



    // Aplicar el estilo a los elementos específicos
    qApp->setStyleSheet(elementStyle);
}

Askme::~Askme()
{
    delete ui;
}



void Askme::on_apunteTomado(Apunte *apunte)
{
    for (int i = 0; i < m_asignaturas.size(); ++i) {
            if (i >= 0 && i < m_asignaturas.size()) {
                Asignatura *a = m_asignaturas[i];
                qDebug().noquote() << a->toString();
            } else {
                // Manejo de error: el índice está fuera de los límites
                qDebug() << "Índice fuera de límites en m_asignaturas: " << i;
            }
        }

        guardar();

}

void Askme::on_cuestionarioCreado(Cuestionario *cuestionario)
{
    PreguntaForm *w = new PreguntaForm(this);
    w->setCuestionario(cuestionario);

    connect(w, SIGNAL(cuestionarioFinalizado(int, int, float)), this, SLOT(on_resultadosCreado(int, int, float)));

    cargarSubVentana(w);
}

void Askme::on_resultadosCreado(int preguntasCorrectas, int totalPreguntas, float score) {
    ResultadosForm *r = new ResultadosForm(preguntasCorrectas, totalPreguntas, score, this);
    cargarSubVentana(r);
}

void Askme::cargarSubVentana(QWidget *ventana)
{
    auto sub = ui->mdiArea->addSubWindow(ventana);
    sub->show();
}

void Askme::cargarDatos()
{

    QFile archivo("datos.csv");

    if (archivo.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&archivo);

        Asignatura *asignatura = nullptr;
        Tema *tema = nullptr;

        while (!in.atEnd())
        {
            QString linea = in.readLine();
            QStringList campos = linea.split("\t");  // Cambia el separador según el formato del archivo

            if (campos.size() > 1)
            {
                QString tipo = campos[0];
                QString valor = campos[1];

                if (tipo == "Asignatura")
                {
                    asignatura = new Asignatura(valor);
                    m_asignaturas.append(asignatura);
                }
                else if (tipo == "Tema")
                {
                    tema = new Tema(valor);
                    asignatura->agregarTema(tema);
                }
                else if (tipo == "Apunte")
                {
                    if (tema)
                    {
                        if (campos.size() > 2)
                        {
                            QString termino = campos[1];
                            QString concepto = campos[2];
                            Apunte *apunte = new Apunte(termino, concepto);
                            tema->agregarApunte(apunte);
                        }
                    }
                }
            }
        }

        archivo.close();
    }
    else
    {
        qDebug() << "No se pudo abrir el archivo para leer.";
    }
}




void Askme::guardar()
{
    QFile archivo("datos.csv");

    if (archivo.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&archivo);

        // Guardar asignaturas, temas y apuntes en el archivo CSV
        foreach (Asignatura *asignatura, m_asignaturas)
        {
            out << "Asignatura\t" << asignatura->nombre()<< "\n";

            foreach (Tema *tema, asignatura->temas())
            {
                out << "Tema\t" << tema->nombre() << "\n";

                foreach (Apunte *apunte, tema->apuntes())
                {
                    out << "Apunte\t" << apunte->termino() << "\t" << apunte->concepto() << "\n";
                }
            }
        }

        archivo.close();
    }
    else
    {
        qDebug() << "No se pudo abrir el archivo para escribir.";
    }


}

void Askme::mostrarListaApuntes()
{

    // Crear un diálogo para mostrar la lista
    QDialog *dialogo = new QDialog(this);
    dialogo->setWindowTitle("Lista de Apuntes");

    // Establecer un ancho mínimo más grande para el diálogo
    dialogo->setMinimumWidth(1000);  // Ajusta este valor según tus necesidades

    // Crear un layout vertical
    QVBoxLayout *layout = new QVBoxLayout(dialogo);

    // Crear combos de asignaturas y temas
    QComboBox *comboAsignaturas = new QComboBox();
    QComboBox *comboTemas = new QComboBox();

    // Llenar combos con datos



    foreach (Asignatura *asignatura, m_asignaturas)
    {
        comboAsignaturas->addItem(asignatura->nombre());
    }

    // Conectar la señal de cambio de asignatura

    connect(comboAsignaturas, QOverload<int>::of(&QComboBox::currentIndexChanged),
            [=](int index) {
                comboTemas->clear();
                if (index >= 0 && index < m_asignaturas.size()) {
                    foreach (Tema *tema, m_asignaturas[index]->temas()) {
                        comboTemas->addItem(tema->nombre());
                    }
                }
            });

    // Conectar la señal de cambio de tema
    connect(comboTemas, QOverload<int>::of(&QComboBox::currentIndexChanged),
            [=](int index) {
                // Actualizar la tabla de apuntes al cambiar el tema
                actualizarTablaApuntes(dialogo, comboAsignaturas->currentIndex(), index);
                // Ajustar el tamaño de la ventana al tamaño de la tabla
                dialogo->parentWidget()->adjustSize();
            });

    // Agregar combos al layout
    layout->addWidget(new QLabel("Asignatura:"));
    layout->addWidget(comboAsignaturas);
    layout->addWidget(new QLabel("Tema:"));
    layout->addWidget(comboTemas);

    // Crear una tabla de apuntes
    QTableWidget *tablaApuntes = new QTableWidget(dialogo);
    tablaApuntes->setColumnCount(1);
    QStringList headers;
    headers << "Apuntes";
    tablaApuntes->setHorizontalHeaderLabels(headers);

    // Agregar la tabla al layout
    layout->addWidget(tablaApuntes);

    // Agregar el layout al diálogo
    dialogo->setLayout(layout);

    actualizarTablaApuntes(dialogo, 0, 0);


    // Mostrar el diálogo modal
    dialogo->exec();

}


void Askme::actualizarTablaApuntes(QDialog *dialogo, int indexAsignatura, int indexTema)
{
    // Obtener la asignatura y el tema seleccionados
    Asignatura *asignatura = m_asignaturas.value(indexAsignatura, nullptr);
    Tema *tema = (asignatura) ? asignatura->temas().value(indexTema, nullptr) : nullptr;

    // Obtener la tabla de apuntes
    QTableWidget *tablaApuntes = dialogo->findChild<QTableWidget *>();

    // Limpiar la tabla de apuntes
    tablaApuntes->clearContents();
    tablaApuntes->setRowCount(0);

    // Mostrar los apuntes si se han seleccionado asignatura y tema válidos
    if (asignatura && tema) {
        int row = 0;
        foreach (Apunte *apunte, tema->apuntes()) {
            tablaApuntes->insertRow(row);
            QTableWidgetItem *item = new QTableWidgetItem(apunte->toString());
            tablaApuntes->setItem(row, 0, item);
            ++row;
        }
    }

    // Ajustar el tamaño de la columna automáticamente
    tablaApuntes->resizeColumnsToContents();

    // Ajustar el tamaño de la ventana al tamaño de la tabla
   dialogo->resize(dialogo->sizeHint());

}





void Askme::on_actionNuevo_triggered()
{
    ApunteForm *w = new ApunteForm(this);
    w->setAsignaturas(m_asignaturas);
    w->cargarAsignaturas();

    connect(w, SIGNAL(apunteTomado(Apunte*)), this, SLOT(on_apunteTomado(Apunte*)));

    cargarSubVentana(w);
}


void Askme::on_actionGenerar_triggered()
{
    CuestionarioForm *w = new CuestionarioForm(this);
    w->setAsignaturas(m_asignaturas);
    w->cargarAsignaturas();

    connect(w, SIGNAL(cuestionarioCreado(Cuestionario*)), this, SLOT(on_cuestionarioCreado(Cuestionario*)));


    cargarSubVentana(w);
}

void Askme::on_actionLista_triggered()
{
    mostrarListaApuntes();
}



void Askme::on_actionCreditos_triggered()
{
    CreditosForm *c = new CreditosForm(this);

    cargarSubVentana(c);
}

