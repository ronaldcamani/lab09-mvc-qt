#include "controller/ActividadController.h"

#include "model/ActividadFactory.h"
#include "model/CsvRepositorioAdapter.h"

#include <QStringList>

ActividadController::ActividadController(IRepositorio &repositorio, QObject *parent)
    : QObject(parent), repositorio_(repositorio)
{
}

void ActividadController::crearActividad(const QString &tipo, const QString &titulo,
                                          const QString &curso, const QDate &fecha,
                                          const QString &responsable)
{
    try {
        std::unique_ptr<ActividadCreator> creador;
        if (tipo == QStringLiteral("Tarea")) {
            creador = std::make_unique<TareaCreator>();
        } else if (tipo == QStringLiteral("Examen")) {
            creador = std::make_unique<ExamenCreator>();
        } else if (tipo == QStringLiteral("Proyecto")) {
            creador = std::make_unique<ProyectoCreator>();
        } else {
            throw std::invalid_argument("Tipo de actividad no soportado");
        }
        repositorio_.guardar(creador->crear({titulo, curso, fecha, responsable}));
        listarActividades();
        emit operacionCompletada(QStringLiteral("Actividad creada correctamente"));
    } catch (const std::exception &error) {
        emit errorOcurrido(QString::fromUtf8(error.what()));
    }
}

void ActividadController::cargarCsv(const QString &ruta)
{
    try {
        CsvRepositorioAdapter adaptador{CsvLegacySource(ruta)};
        adaptador.cargar();
        for (const Actividad *actividad : adaptador.listar()) {
            const ActividadData &data = actividad->datos();
            crearActividad(actividad->tipo(), data.titulo, data.curso, data.fecha, data.responsable);
        }
        emit operacionCompletada(QStringLiteral("CSV cargado correctamente"));
    } catch (const std::exception &error) {
        emit errorOcurrido(QString::fromUtf8(error.what()));
    }
}

void ActividadController::listarActividades()
{
    QStringList resumenes;
    for (const Actividad *actividad : repositorio_.listar()) {
        resumenes << actividad->resumen();
    }
    emit actividadesActualizadas(resumenes);
}
