#include "asignatura.h"

Asignatura::Asignatura()
{

}

Asignatura::Asignatura(const QString &nombre) : m_nombre(nombre)
{}

void Asignatura::agregarTema(Tema *tema)
{
    m_temas.append(tema);
}

const QString &Asignatura::nombre() const
{
    return m_nombre;
}

const QList<Tema *> &Asignatura::temas() const
{
    return m_temas;
}

const QString Asignatura::toString() const
{
    QString str = "Asignatura: " + m_nombre + "\n";
    foreach(Tema *t, m_temas){
        str += t->toString();
    }
    return str;
}
