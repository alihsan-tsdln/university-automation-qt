#ifndef NOT_H
#define NOT_H

#include <QDialog>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>

namespace Ui {
class Not;
}

class Not : public QDialog
{
    Q_OBJECT

public:
    explicit Not(QWidget *parent = nullptr);
    ~Not();

private slots:
    void on_ogr_table_clicked(const QModelIndex &index);

    void on_ders_table_clicked(const QModelIndex &index);

    void on_kayit_btn_clicked();

private:
    Ui::Not *ui;
    QSqlQueryModel *model;
    void init();
};

#endif // NOT_H
