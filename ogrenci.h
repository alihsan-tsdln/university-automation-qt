#ifndef OGRENCI_H
#define OGRENCI_H

#include <QDialog>
#include <QSql>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>

namespace Ui {
class Ogrenci;
}

class Ogrenci : public QDialog
{
    Q_OBJECT

public:
    explicit Ogrenci(QWidget *parent = nullptr);
    ~Ogrenci();
    Ui::Ogrenci *ui;

private slots:
    void on_ogr_table_clicked(const QModelIndex &index);

    void on_yeni_btn_clicked();

    void on_guncelle_btn_clicked();

    void on_sil_btn_clicked();

private:

    void init();
    QSqlQueryModel *model;
};

#endif // OGRENCI_H
