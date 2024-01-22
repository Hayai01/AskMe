#include "pregunta.h"

Pregunta::Pregunta()
{

}

bool Pregunta::correcta() const
{
    return m_correcta;
}

void Pregunta::setCorrecta(bool newCorrecta)
{
    m_correcta = newCorrecta;
}

bool Pregunta::respondida() const
{
    return m_respondida;
}

void Pregunta::setRespondida(bool newRespondida)
{
    m_respondida = newRespondida;
}

Apunte *Pregunta::apunte() const
{
    return m_apunte;
}

void Pregunta::setApunte(Apunte *newApunte)
{
    m_apunte = newApunte;
}

QString Pregunta::toString() const
{
    QString str = m_apunte->toString();
    str += ", correcta: " + QString::number(m_correcta) + ", ";
    str += "respondida: " + QString::number(m_respondida) + "\n";
    return str;
}

void Pregunta::responder(QString termino)
{
    m_correcta = (termino == apunte()->termino());
    m_respondida = true;
}

Pregunta::Pregunta(Apunte *apunte) : m_apunte(apunte)
{
    m_correcta = false;
    m_respondida = false;
}
