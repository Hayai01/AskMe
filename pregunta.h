#ifndef PREGUNTA_H
#define PREGUNTA_H

#include <apunte.h>

class Pregunta
{
public:
    Pregunta();
    Pregunta(Apunte *apunte);

    bool correcta() const;
    void setCorrecta(bool newCorrecta);
    bool respondida() const;
    void setRespondida(bool newRespondida);
    Apunte *apunte() const;
    void setApunte(Apunte *newApunte);
    QString toString() const;
    void responder(QString termino);
private:
    bool m_correcta;
    bool m_respondida;
    Apunte *m_apunte;
};

#endif // PREGUNTA_H
