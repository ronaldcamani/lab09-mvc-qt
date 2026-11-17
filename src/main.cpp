#include "controller/ActividadController.h"
#include "model/RepositorioActividades.h"
#include "view/MainWindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    RepositorioActividades repositorio;
    ActividadController controller(repositorio);
    MainWindow ventana(controller);
    ventana.show();
    controller.listarActividades();
    return app.exec();
}
