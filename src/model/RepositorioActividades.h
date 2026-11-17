#pragma once

#include "model/IRepositorio.h"

class RepositorioActividades final : public IRepositorio {
public:
    void guardar(std::unique_ptr<Actividad> actividad) override;
    std::vector<const Actividad *> listar() const override;

private:
    std::vector<std::unique_ptr<Actividad>> actividades_;
};
