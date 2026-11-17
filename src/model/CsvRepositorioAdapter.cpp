#include "model/CsvRepositorioAdapter.h"

#include "model/ActividadFactory.h"
#include "model/RepositorioActividades.h"

#include <QDate>
#include <stdexcept>

CsvRepositorioAdapter::CsvRepositorioAdapter(CsvLegacySource fuente) : fuente_(std::move(fuente)) {}

void CsvRepositorioAdapter::guardar(std::unique_ptr<Actividad> actividad)
{
    repositorio_.guardar(std::move(actividad));
}

std::vector<const Actividad *> CsvRepositorioAdapter::listar() const
{
    return repositorio_.listar();
}

void CsvRepositorioAdapter::cargar()
{
    for (const LegacyRecord &registro : fuente_.leer()) {
        const ActividadData data{registro.nombre, registro.asignatura,
                                 QDate::fromString(registro.fechaTexto, Qt::ISODate), registro.encargado};
        if (!data.fecha.isValid()) {
            throw std::runtime_error("El CSV heredado contiene una fecha invalida");
        }

        std::unique_ptr<ActividadCreator> creador;
        if (registro.clase.compare("tarea", Qt::CaseInsensitive) == 0) {
            creador = std::make_unique<TareaCreator>();
        } else if (registro.clase.compare("examen", Qt::CaseInsensitive) == 0) {
            creador = std::make_unique<ExamenCreator>();
        } else if (registro.clase.compare("proyecto", Qt::CaseInsensitive) == 0) {
            creador = std::make_unique<ProyectoCreator>();
        } else {
            throw std::runtime_error("Tipo de actividad heredado desconocido");
        }
        guardar(creador->crear(data));
    }
}
