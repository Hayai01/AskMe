#ifndef APUNTE_H
#define APUNTE_H

#include <QString>

class Apunte
{
public:
    Apunte();
    Apunte(const QString &termino, const QString &concepto);

    const QString &termino() const;
    const QString &concepto() const;
    const QString toString() const;

private:
    QString m_termino;
    QString m_concepto;

};

#endif // APUNTE_H
