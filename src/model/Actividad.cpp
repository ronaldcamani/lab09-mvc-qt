#include "model/Actividad.h"

Actividad::Actividad(ActividadData data) : data_(std::move(data)) {}

const ActividadData &Actividad::datos() const { return data_; }

QString Actividad::resumen() const
{
    return QStringLiteral("%1 | %2 | %3 | %4")
        .arg(tipo(), data_.titulo, data_.curso, data_.fecha.toString(Qt::ISODate));
}

QString Tarea::tipo() const { return QStringLiteral("Tarea"); }
QString Examen::tipo() const { return QStringLiteral("Examen"); }
QString Proyecto::tipo() const { return QStringLiteral("Proyecto"); }
