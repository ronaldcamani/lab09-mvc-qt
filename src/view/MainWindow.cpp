#include "view/MainWindow.h"

#include "controller/ActividadController.h"

#include <QComboBox>
#include <QDateEdit>
#include <QFileDialog>
#include <QFormLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QMainWindow>
#include <QMessageBox>
#include <QPushButton>
#include <QStatusBar>
#include <QVBoxLayout>
#include <QWidget>

MainWindow::MainWindow(ActividadController &controller, QWidget *parent)
    : QMainWindow(parent), controller_(controller), tipo_(new QComboBox(this)),
      titulo_(new QLineEdit(this)), curso_(new QLineEdit(this)), fecha_(new QDateEdit(this)),
      responsable_(new QLineEdit(this)), lista_(new QListWidget(this))
{
    construirUi();
    connect(&controller_, &ActividadController::actividadesActualizadas, this,
            [this](const QStringList &actividades) { lista_->clear(); lista_->addItems(actividades); });
    connect(&controller_, &ActividadController::operacionCompletada, this,
            [this](const QString &mensaje) { statusBar()->showMessage(mensaje, 3000); });
    connect(&controller_, &ActividadController::errorOcurrido, this,
            [this](const QString &mensaje) { QMessageBox::critical(this, "Error", mensaje); });
}

void MainWindow::construirUi()
{
    setWindowTitle("Seguimiento academico");
    resize(760, 480);
    tipo_->addItems({"Tarea", "Examen", "Proyecto"});
    fecha_->setCalendarPopup(true);
    fecha_->setDate(QDate::currentDate());

    auto *formulario = new QFormLayout;
    formulario->addRow("Tipo:", tipo_);
    formulario->addRow("Titulo:", titulo_);
    formulario->addRow("Curso:", curso_);
    formulario->addRow("Fecha:", fecha_);
    formulario->addRow("Responsable:", responsable_);

    auto *crear = new QPushButton("Crear actividad");
    auto *cargar = new QPushButton("Cargar CSV heredado");
    auto *refrescar = new QPushButton("Actualizar lista");
    connect(crear, &QPushButton::clicked, this, [this] {
        controller_.crearActividad(tipo_->currentText(), titulo_->text(), curso_->text(),
                                   fecha_->date(), responsable_->text());
    });
    connect(cargar, &QPushButton::clicked, this, [this] {
        const QString ruta = QFileDialog::getOpenFileName(this, "Seleccionar CSV", {}, "CSV (*.csv)");
        if (!ruta.isEmpty()) {
            controller_.cargarCsv(ruta);
        }
    });
    connect(refrescar, &QPushButton::clicked, &controller_, &ActividadController::listarActividades);

    auto *botones = new QHBoxLayout;
    botones->addWidget(crear);
    botones->addWidget(cargar);
    botones->addWidget(refrescar);

    auto *panel = new QVBoxLayout;
    panel->addWidget(new QLabel("Nueva actividad"));
    panel->addLayout(formulario);
    panel->addLayout(botones);
    panel->addWidget(new QLabel("Actividades registradas"));
    panel->addWidget(lista_);

    auto *central = new QWidget(this);
    central->setLayout(panel);
    setCentralWidget(central);
}
