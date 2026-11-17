#include "model/CsvLegacySource.h"

#include <QFile>
#include <QTextStream>
#include <stdexcept>

CsvLegacySource::CsvLegacySource(QString ruta) : ruta_(std::move(ruta)) {}

std::vector<LegacyRecord> CsvLegacySource::leer() const
{
    QFile archivo(ruta_);
    if (!archivo.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw std::runtime_error(("No se pudo abrir el CSV: " + ruta_).toStdString());
    }

    QTextStream entrada(&archivo);
    std::vector<LegacyRecord> registros;
    bool cabecera = true;
    while (!entrada.atEnd()) {
        const QString linea = entrada.readLine().trimmed();
        if (linea.isEmpty()) {
            continue;
        }
        if (cabecera) {
            cabecera = false;
            continue;
        }
        const QStringList campos = linea.split(',');
        if (campos.size() != 5) {
            throw std::runtime_error("El CSV heredado contiene una fila invalida");
        }
        registros.push_back({campos[0].trimmed(), campos[1].trimmed(), campos[2].trimmed(),
                             campos[3].trimmed(), campos[4].trimmed()});
    }
    return registros;
}
