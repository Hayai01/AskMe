#ifndef TEMA_H
#define TEMA_H

#include <QString>
#include <QList>

#include "apunte.h"

class Tema
{
public:
    Tema();
    Tema(const QString &nombre);
    void agregarApunte(Apunte* a);

    const QString &nombre() const;
    const QList<Apunte *> &apuntes() const;
    const QString toString() const;
private:
    QString m_nombre;
    QList<Apunte*> m_apuntes;
};

#endif // TEMA_H
