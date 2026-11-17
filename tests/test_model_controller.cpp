#include "controller/ActividadController.h"
#include "model/ActividadFactory.h"
#include "model/CsvRepositorioAdapter.h"
#include "model/RepositorioActividades.h"

#include <QSignalSpy>
#include <QTemporaryFile>
#include <QtTest>

class ModeloControladorTest final : public QObject {
    Q_OBJECT

private slots:
    void factoryCreaTipos();
    void factoryRechazaDatosInvalidos();
    void adapterTraduceCsvHeredado();
    void controllerEmiteActualizacion();
};

void ModeloControladorTest::factoryCreaTipos()
{
    const ActividadData data{"Entrega 1", "POO", QDate(2026, 11, 20), "Ana"};
    QCOMPARE(TareaCreator().crear(data)->tipo(), QString("Tarea"));
    QCOMPARE(ExamenCreator().crear(data)->tipo(), QString("Examen"));
    QCOMPARE(ProyectoCreator().crear(data)->tipo(), QString("Proyecto"));
}

void ModeloControladorTest::factoryRechazaDatosInvalidos()
{
    QVERIFY_EXCEPTION_THROWN(TareaCreator().crear({"", "POO", QDate(2026, 11, 20), "Ana"}),
                             std::invalid_argument);
}

void ModeloControladorTest::adapterTraduceCsvHeredado()
{
    QTemporaryFile archivo;
    QVERIFY(archivo.open());
    archivo.write("clase,nombre,asignatura,fecha,encargado\n"
                  "tarea,Entrega CSV,POO,2026-11-20,Ana\n"
                  "examen,Parcial,POO,2026-11-25,Luis\n");
    archivo.flush();

    CsvRepositorioAdapter adapter(CsvLegacySource(archivo.fileName()));
    adapter.cargar();
    QCOMPARE(static_cast<int>(adapter.listar().size()), 2);
    QCOMPARE(adapter.listar().at(0)->tipo(), QString("Tarea"));
    QCOMPARE(adapter.listar().at(1)->tipo(), QString("Examen"));
}

void ModeloControladorTest::controllerEmiteActualizacion()
{
    RepositorioActividades repositorio;
    ActividadController controller(repositorio);
    QSignalSpy spy(&controller, &ActividadController::actividadesActualizadas);

    controller.crearActividad("Proyecto", "Sistema", "TO", QDate(2026, 11, 30), "Rosa");

    QCOMPARE(spy.count(), 1);
    QCOMPARE(spy.at(0).at(0).toStringList().size(), 1);
    QCOMPARE(repositorio.listar().at(0)->tipo(), QString("Proyecto"));
}

QTEST_MAIN(ModeloControladorTest)
#include "test_model_controller.moc"
