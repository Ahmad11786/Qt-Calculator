#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPushButton>
#include <QMessageBox>
#include <cmath>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setStyleSheet(R"(

QMainWindow {
    background-color: #171923;
}

QWidget {
    color: #F5F7FA;
    font-family: "Segoe UI";
    font-size: 16px;
}

QLineEdit {
    background-color: #222633;
    color: #FFFFFF;
    border: 2px solid #E85D75;
    border-radius: 18px;
    padding: 16px;
    font-size: 34px;
    font-weight: bold;
    selection-background-color: #FF9F43;
    min-height: 65px;
}

QPushButton {
    background-color: #2D3242;
    color: #FFFFFF;
    border: 1px solid #393F51;
    border-radius: 14px;
    padding: 10px;
    font-size: 19px;
    font-weight: bold;
    min-height: 48px;
}

QPushButton:hover {
    background-color: #41485C;
    border: 1px solid #FF9F43;
}

QPushButton:pressed {
    background-color: #515A70;
    padding-top: 12px;
}

QPushButton#pushButton_add,
QPushButton#pushButton_sub,
QPushButton#pushButton_mul,
QPushButton#pushButton_div,
QPushButton#pushButton_mod{
    background-color: #FF9F43;
    color: #171923;
}

QPushButton#pushButton_equal {
    background-color: #35B779;
    color: #FFFFFF;
    border: none;
}

QPushButton#pushButton_remove,
QPushButton#pushButton_clear {
    background-color: #454B60;
    color: #FF8C8C;
}
)");

    // connects buttton from ui
    connect(ui->pushButton_0, &QPushButton::clicked, this, &MainWindow::numberClicked);
    connect(ui->pushButton_1, &QPushButton::clicked, this, &MainWindow::numberClicked);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::numberClicked);
    connect(ui->pushButton_3, &QPushButton::clicked, this, &MainWindow::numberClicked);
    connect(ui->pushButton_4, &QPushButton::clicked, this, &MainWindow::numberClicked);
    connect(ui->pushButton_5, &QPushButton::clicked, this, &MainWindow::numberClicked);
    connect(ui->pushButton_6, &QPushButton::clicked, this, &MainWindow::numberClicked);
    connect(ui->pushButton_7, &QPushButton::clicked, this, &MainWindow::numberClicked);
    connect(ui->pushButton_8, &QPushButton::clicked, this, &MainWindow::numberClicked);
    connect(ui->pushButton_9, &QPushButton::clicked, this, &MainWindow::numberClicked);

    //remove one character from display
    connect(ui->pushButton_remove, &QPushButton::clicked,this, &MainWindow::deleteLastCharacter);
    // clear all display text
    connect(ui->pushButton_clear, &QPushButton::clicked, this , &MainWindow::clearDisplay);
    //decimal
    connect(ui->pushButton_decimal, &QPushButton::clicked , this , &MainWindow::decimalClicked);

    connect(ui->pushButton_add, &QPushButton::clicked , this , &MainWindow::operatorClicked);
    connect(ui->pushButton_sub, &QPushButton::clicked , this , &MainWindow::operatorClicked);
    connect(ui->pushButton_mul, &QPushButton::clicked , this , &MainWindow::operatorClicked);
    connect(ui->pushButton_div,&QPushButton::clicked,this, &MainWindow::operatorClicked);
    connect(ui->pushButton_mod,&QPushButton::clicked,this, &MainWindow::operatorClicked);
    connect(ui->pushButton_sign,&QPushButton::clicked,this, &MainWindow::signClicked);


    connect(ui->pushButton_equal, &QPushButton::clicked , this , &MainWindow::equlaClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::clearDisplay()
{
    ui->display->setText("0");
    firstNumber = 0;
    pendingOperator = "";
}

void MainWindow::operatorClicked()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());

    if (!button)
        return;

    double currentNumber = ui->display->text().toDouble();

    if (!pendingOperator.isEmpty())
    {
        double secondNumber = currentNumber;

        if (pendingOperator == "+")
            firstNumber += secondNumber;

        else if (pendingOperator == "-")
            firstNumber -= secondNumber;

        else if (pendingOperator == "×")
            firstNumber *= secondNumber;

        else if (pendingOperator == "÷")
        {
            if (secondNumber == 0)
            {
                QMessageBox::warning(
                    this,
                    "Math Error",
                    "Cannot divide by zero!"
                    );
                return;
            }

            firstNumber /= secondNumber;
        }

        else if (pendingOperator == "%")
        {
            if (secondNumber == 0)
            {
                QMessageBox::warning(
                    this,
                    "Math Error",
                    "Cannot calculate remainder with zero!"
                    );
                return;
            }

            firstNumber = std::fmod(firstNumber, secondNumber);
        }

        ui->display->setText(QString::number(firstNumber));
    }
    else
    {
        firstNumber = currentNumber;
    }

    pendingOperator = button->text();
    ui->display->setText("0");
}


void MainWindow::equlaClicked()
{
    if (pendingOperator.isEmpty())
    {
        QMessageBox::warning(
            this,
            "Invalid Operation",
            "Please select an operator first!"
            );
        return;
    }

    double secondNumber = ui->display->text().toDouble();
    double result = 0;

    if (pendingOperator == "+")
    {
        result = firstNumber + secondNumber;
    }
    else if (pendingOperator == "-")
    {
        result = firstNumber - secondNumber;
    }
    else if (pendingOperator == "x")
    {
        result = firstNumber * secondNumber;
    }
    else if (pendingOperator == "÷")
    {
        if (secondNumber == 0)
        {
            QMessageBox::warning(
                this,
                "Math Error",
                "Cannot divide by zero!"
                );
            return;
        }

        result = firstNumber / secondNumber;
    }
    else if (pendingOperator == "%")
    {
        if (secondNumber == 0)
        {
            QMessageBox::warning(
                this,
                "Math Error",
                "Cannot calculate remainder with zero!"
                );
            return;
        }

        result = std::fmod(firstNumber, secondNumber);
    }

    ui->display->setText(QString::number(result));

    firstNumber = result;
    pendingOperator = "";
}


void MainWindow::signClicked()
{
    double number = ui->display->text().toDouble();

    number = -number;

    ui->display->setText(QString::number(number));
}

void MainWindow::decimalClicked(){
    QString text= ui->display->text();

    if(!text.contains('.'))
        ui->display->setText(text + ".");

}

void MainWindow::deleteLastCharacter()
{
    QString text = ui->display->text();

    text.chop(1);

    if (text.isEmpty() || text == "-")
        text = "0";

    ui->display->setText(text);
}

void MainWindow::numberClicked()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());

    if (button == nullptr)
        return;

    QString number = button->text();

    if (ui->display->text() == "0")
        ui->display->setText(number);  //setText(use for access of number who written in ui in button)
    else
        ui->display->setText(ui->display->text() + number);
}

