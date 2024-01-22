#include "tema.h"

Tema::Tema()
{

}

Tema::Tema(const QString &nombre) : m_nombre(nombre)
{}

void Tema::agregarApunte(Apunte *a)
{
    m_apuntes.append(a);
}

const QString &Tema::nombre() const
{
    return m_nombre;
}

const QList<Apunte *> &Tema::apuntes() const
{
    return m_apuntes;
}

const QString Tema::toString() const
{
    QString str = "Tema: " + m_nombre + "\n";
    foreach(Apunte *a, m_apuntes){
        str += "\t"  + a->toString() + "\n";
    }
    return str;
}
