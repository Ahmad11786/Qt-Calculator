#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    Ui::MainWindow *ui;

    double firstNumber = 0;
    QString pendingOperator = "";

    void numberClicked();
    void clearDisplay();
    void deleteLastCharacter();
    void decimalClicked();
    void operatorClicked();
    void equlaClicked();
    void signClicked();
};
#endif // MAINWINDOW_H
