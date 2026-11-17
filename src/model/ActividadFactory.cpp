#include "model/ActividadFactory.h"

#include <stdexcept>

std::unique_ptr<Actividad> ActividadCreator::crear(const ActividadData &data) const
{
    if (data.titulo.trimmed().isEmpty() || data.curso.trimmed().isEmpty() || !data.fecha.isValid()) {
        throw std::invalid_argument("Los datos de la actividad no son validos");
    }
    return crearProducto(data);
}

std::unique_ptr<Actividad> TareaCreator::crearProducto(const ActividadData &data) const
{
    return std::make_unique<Tarea>(data);
}

std::unique_ptr<Actividad> ExamenCreator::crearProducto(const ActividadData &data) const
{
    return std::make_unique<Examen>(data);
}

std::unique_ptr<Actividad> ProyectoCreator::crearProducto(const ActividadData &data) const
{
    return std::make_unique<Proyecto>(data);
}
