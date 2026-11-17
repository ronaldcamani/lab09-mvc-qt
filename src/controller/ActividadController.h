#pragma once

#include "model/IRepositorio.h"

#include <QObject>

class ActividadController final : public QObject {
    Q_OBJECT
public:
    explicit ActividadController(IRepositorio &repositorio, QObject *parent = nullptr);

public slots:
    void crearActividad(const QString &tipo, const QString &titulo, const QString &curso,
                        const QDate &fecha, const QString &responsable);
    void cargarCsv(const QString &ruta);
    void listarActividades();

signals:
    void actividadesActualizadas(const QStringList &resumenes);
    void operacionCompletada(const QString &mensaje);
    void errorOcurrido(const QString &mensaje);

private:
    IRepositorio &repositorio_;
};
