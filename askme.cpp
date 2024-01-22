#include "askme.h"
#include "ui_askme.h"

#include <QTableWidget>


Askme::Askme(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Askme)
{
    ui->setupUi(this);
    cargarDatos();
}

Askme::~Askme()
{
    delete ui;
}

void Askme::on_apunteTomado(Apunte *apunte)
{
    // TODO: Guardar datos en CSV
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
    // TODO: Cargar datos desde CSV

    Tema *t1 = new Tema("Electromagnetismo");
    t1->agregarApunte(new Apunte("Campo eléctrico", "Región del espacio alrededor de una carga eléctrica donde actúa una fuerza eléctrica sobre otras cargas."));
    t1->agregarApunte(new Apunte("Ley de Ampère","Relación matemática que describe la circulación de un campo magnético alrededor de un conductor por el cual fluye una corriente eléctrica."));
    t1->agregarApunte(new Apunte("Ley de Faraday","Principio que establece que un cambio en el flujo magnético a través de una espira induce una fuerza electromotriz (EMF) en la espira."));
    t1->agregarApunte(new Apunte("Bobina","Dispositivo formado por varias vueltas de alambre conductor, utilizado para generar un campo magnético o para inducir corriente."));
    t1->agregarApunte(new Apunte("Ley de Gauss","Principio que relaciona el flujo magnético a través de una superficie cerrada con la suma de las corrientes magnéticas que la atraviesan."));

    Tema *t2 = new Tema("Óptica");
    t2->agregarApunte(new Apunte("Luz","Radiación electromagnética visible por el ojo humano, que se propaga en forma de ondas."));
    t2->agregarApunte(new Apunte("Reflexión","Cambio en la dirección de propagación de la luz al pasar de un medio a otro con diferente índice de refracción."));
    t2->agregarApunte(new Apunte("Refracción","Cambio de dirección de un rayo de luz cuando incide sobre una superficie."));
    t2->agregarApunte(new Apunte("Prisma","Objeto óptico transparente con superficies planas que separa la luz en sus componentes de diferentes longitudes de onda."));
    t2->agregarApunte(new Apunte("Lente","Dispositivo óptico que enfoca o dispersa la luz mediante su curvatura, utilizado en cámaras, anteojos, microscopios, y telescopios."));

    Asignatura *a1 = new Asignatura("Fisica");
    a1->agregarTema(t1);
    a1->agregarTema(t2);

    t1 = new Tema("Ecología");
    t1->agregarApunte(new Apunte("Ecosistema", "Sistema formado por seres vivos y su entorno físico, donde interactúan entre sí y con el ambiente."));
    t1->agregarApunte(new Apunte("Biodiversidad", "Variedad de vida en la Tierra, que incluye la diversidad genética, de especies y de ecosistemas."));
    t1->agregarApunte(new Apunte("Cadena alimentaria", "Serie de organismos interconectados, donde cada uno se alimenta del anterior y es alimento para el siguiente."));
    t1->agregarApunte(new Apunte("Ciclo del agua", "Proceso continuo de circulación del agua entre la atmósfera, la tierra y los cuerpos de agua, que incluye evaporación, condensación y precipitación."));
    t1->agregarApunte(new Apunte("Bioma", "Gran área geográfica con características climáticas similares que alberga una comunidad específica de plantas y animales."));

    t2 = new Tema("Genética");
    t2->agregarApunte(new Apunte("ADN","Ácido desoxirribonucleico, la molécula que contiene la información genética hereditaria en los organismos."));
    t2->agregarApunte(new Apunte("Gen","Unidad de información hereditaria que codifica una característica específica, y que se encuentra en el ADN."));
    t2->agregarApunte(new Apunte("Cromosoma","Estructura compuesta por ADN y proteínas que transporta genes y se encuentra en el núcleo de las células."));
    t2->agregarApunte(new Apunte("Mutación","Cambio en la secuencia de ADN que puede dar lugar a variaciones genéticas."));
    t2->agregarApunte(new Apunte("Herencia","Transmisión de características genéticas de padres a descendencia a través de la reproducción."));

    Asignatura *a2 = new Asignatura("Ciencias naturales");
    a2->agregarTema(t1);
    a2->agregarTema(t2);

    m_asignaturas.append(a1);
    m_asignaturas.append(a2);
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


