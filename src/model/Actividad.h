#pragma once

#include <QDate>
#include <QString>

struct ActividadData {
    QString titulo;
    QString curso;
    QDate fecha;
    QString responsable;
};

class Actividad {
public:
    explicit Actividad(ActividadData data);
    virtual ~Actividad() = default;

    virtual QString tipo() const = 0;
    const ActividadData &datos() const;
    QString resumen() const;

private:
    ActividadData data_;
};

class Tarea final : public Actividad {
public:
    using Actividad::Actividad;
    QString tipo() const override;
};

class Examen final : public Actividad {
public:
    using Actividad::Actividad;
    QString tipo() const override;
};

class Proyecto final : public Actividad {
public:
    using Actividad::Actividad;
    QString tipo() const override;
};
