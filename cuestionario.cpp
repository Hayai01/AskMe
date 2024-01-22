#include "cuestionario.h"

Cuestionario::Cuestionario()
{

}

Cuestionario::Cuestionario(Tema *tema) : m_tema(tema), m_mostradas(0)
{
    foreach (Apunte *a, m_tema->apuntes()){
        m_preguntas.append(new Pregunta(a));
        m_terminos.append(a->termino());
    }
}

Pregunta *Cuestionario::siguiente()
{
    // TODO: Lanzar preguntas al azar
    foreach(Pregunta *p, m_preguntas){
        if(!p->respondida()){
            m_mostradas++;
            return p;
        }
    }
    return nullptr;
}

void Cuestionario::terminar()
{
    int correctas = 0;
    int respondidas = 0;
    foreach(Pregunta *p, m_preguntas){
        if(p->respondida()){
            respondidas++;
            if (p->correcta())
                correctas++;
        }
    }
    m_preguntasCorrectas = correctas;
    if (respondidas > 0){
        m_score = (float) correctas / respondidas * 100;
    }
    else{
        m_score = 0;
    }


}

int Cuestionario::preguntasCorrectas() const
{
    return m_preguntasCorrectas;
}

const QStringList &Cuestionario::terminos() const
{
    return m_terminos;
}

float Cuestionario::score() const
{
    return m_score;
}

const QList<Pregunta *> &Cuestionario::preguntas() const
{
    return m_preguntas;
}

const QString Cuestionario::nombreTema() const
{
    return m_tema->nombre();
}

int Cuestionario::totalPreguntas()
{
    return m_preguntas.size();
}

bool Cuestionario::hayMasPreguntas()
{
    return (m_mostradas < totalPreguntas());
}

int Cuestionario::mostradas() const
{
    return m_mostradas;
}
