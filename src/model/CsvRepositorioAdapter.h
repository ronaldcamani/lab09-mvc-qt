#pragma once

#include "model/IRepositorio.h"
#include "model/CsvLegacySource.h"
#include "model/RepositorioActividades.h"

class CsvRepositorioAdapter final : public IRepositorio {
public:
    explicit CsvRepositorioAdapter(CsvLegacySource fuente);
    void guardar(std::unique_ptr<Actividad> actividad) override;
    std::vector<const Actividad *> listar() const override;
    void cargar();

private:
    CsvLegacySource fuente_;
    RepositorioActividades repositorio_;
};
