#pragma once

#include <QMainWindow>

class QListWidget;
class QComboBox;
class QLineEdit;
class QDateEdit;
class ActividadController;

class MainWindow final : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(ActividadController &controller, QWidget *parent = nullptr);

private:
    void construirUi();
    ActividadController &controller_;
    QComboBox *tipo_;
    QLineEdit *titulo_;
    QLineEdit *curso_;
    QDateEdit *fecha_;
    QLineEdit *responsable_;
    QListWidget *lista_;
};
