#pragma once

#include "model/Actividad.h"

#include <QString>
#include <vector>

struct LegacyRecord {
    QString clase;
    QString nombre;
    QString asignatura;
    QString fechaTexto;
    QString encargado;
};

class CsvLegacySource {
public:
    explicit CsvLegacySource(QString ruta);
    std::vector<LegacyRecord> leer() const;

private:
    QString ruta_;
};
