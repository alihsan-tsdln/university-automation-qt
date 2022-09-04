#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init()
{
    QPalette palette;
    palette.setColor(ui->label->foregroundRole(), Qt::red);
    ui->label->setPalette(palette);

    qsql.setDatabaseName("C:/Users/alihsan-tsdln/Desktop/Coding/VisualProgramming/Odev2/db.db");

    if(qsql.open())
    {
        ui->statusBar->showMessage("Veri Tabanına Bağlanıldı!");
    }

}

void MainWindow::on_ogr_btn_clicked()
{
    ogr = new Ogrenci();
    ogr->show();
}


void MainWindow::on_ders_btn_clicked()
{
    ders = new Ders();
    ders->show();
}


void MainWindow::on_not_btn_clicked()
{
    nott = new Not();
    nott->show();
}

