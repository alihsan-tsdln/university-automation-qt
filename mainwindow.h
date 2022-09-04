#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include "ogrenci.h"
#include "ders.h"
#include "not.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void init();

private slots:
    void on_ogr_btn_clicked();
    void on_ders_btn_clicked();
    void on_not_btn_clicked();

private:
    Ui::MainWindow *ui;
    QSqlQueryModel *model;
    Ogrenci *ogr;
    Ders *ders;
    Not *nott;
    QSqlDatabase qsql = QSqlDatabase::addDatabase("QSQLITE");

};
#endif // MAINWINDOW_H
