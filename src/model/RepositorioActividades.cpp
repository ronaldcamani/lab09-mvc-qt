#include "model/RepositorioActividades.h"

void RepositorioActividades::guardar(std::unique_ptr<Actividad> actividad)
{
    actividades_.push_back(std::move(actividad));
}

std::vector<const Actividad *> RepositorioActividades::listar() const
{
    std::vector<const Actividad *> resultado;
    resultado.reserve(actividades_.size());
    for (const auto &actividad : actividades_) {
        resultado.push_back(actividad.get());
    }
    return resultado;
}
