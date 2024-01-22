#include "apunte.h"

Apunte::Apunte()
{
    m_termino = "";

}

Apunte::Apunte(const QString &termino, const QString &concepto)
    : m_termino(termino), m_concepto(concepto)
{}

const QString &Apunte::termino() const
{
    return m_termino;
}

const QString &Apunte::concepto() const
{
    return m_concepto;
}

const QString Apunte::toString() const
{
    return m_termino + ".- " + m_concepto;
}
