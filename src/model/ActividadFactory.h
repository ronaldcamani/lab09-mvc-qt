#pragma once

#include "model/Actividad.h"

#include <memory>

class ActividadCreator {
public:
    virtual ~ActividadCreator() = default;
    std::unique_ptr<Actividad> crear(const ActividadData &data) const;

protected:
    virtual std::unique_ptr<Actividad> crearProducto(const ActividadData &data) const = 0;
};

class TareaCreator final : public ActividadCreator {
protected:
    std::unique_ptr<Actividad> crearProducto(const ActividadData &data) const override;
};

class ExamenCreator final : public ActividadCreator {
protected:
    std::unique_ptr<Actividad> crearProducto(const ActividadData &data) const override;
};

class ProyectoCreator final : public ActividadCreator {
protected:
    std::unique_ptr<Actividad> crearProducto(const ActividadData &data) const override;
};
