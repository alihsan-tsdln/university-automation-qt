#ifndef DERS_H
#define DERS_H

#include <QDialog>
#include <QMainWindow>
#include <QSql>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QMessageBox>

namespace Ui {
class Ders;
}

class Ders : public QDialog
{
    Q_OBJECT

public:
    explicit Ders(QWidget *parent = nullptr);
    ~Ders();

private slots:
    void on_dersler_table_clicked(const QModelIndex &index);

    void on_yeni_ln_clicked();

    void on_guncelle_ln_clicked();

    void on_sil_ln_clicked();

private:
    Ui::Ders *ui;
    QSqlQueryModel *model;
    void init();
};

#endif // DERS_H
