#pragma once

#include "model/Actividad.h"

#include <memory>
#include <vector>

class IRepositorio {
public:
    virtual ~IRepositorio() = default;
    virtual void guardar(std::unique_ptr<Actividad> actividad) = 0;
    virtual std::vector<const Actividad *> listar() const = 0;
};
