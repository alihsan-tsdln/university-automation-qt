#include "ogrenci.h"
#include "ui_ogrenci.h"
#include "mainwindow.h"
#include <QMessageBox>

Ogrenci::Ogrenci(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Ogrenci)
{
    ui->setupUi(this);
    init();
}

Ogrenci::~Ogrenci()
{
    delete ui;
}

void Ogrenci::init()
{
    QSqlQuery sorgu;
    model = new QSqlQueryModel();

    if(!sorgu.exec("select * from ogrenci"))
        QMessageBox::critical(this,"Sorgu Hatası",sorgu.lastError().text());


    model->setQuery(sorgu);
    ui->ogr_table->setModel(model);
}

void Ogrenci::on_ogr_table_clicked(const QModelIndex &index)
{
    QString val = ui->ogr_table->model()->data(index).toString();

    QSqlQuery sorgu;

    if(sorgu.exec("select * from ogrenci where ogr_no='" + val + "' or ogr_ad='"
                  + val + "' or ogr_soyad='" + val + "'"))
    {
        while(sorgu.next())
        {
            ui->no_ln->setText(sorgu.value(0).toString());
            ui->ad_ln->setText(sorgu.value(1).toString());
            ui->soyad_ln->setText(sorgu.value(2).toString());
        }
    }

}


void Ogrenci::on_yeni_btn_clicked()
{

    if(ui->ad_ln->text() == "" or ui->soyad_ln->text() == "")
    {
        QMessageBox::critical(this, "HATA!", "Gerekli Alanları Doldurunuz");
        return;
    }

    QSqlQuery sorgu;
    model = new QSqlQueryModel();

    sorgu.prepare("insert into ogrenci values(:ogr_no, :ogr_ad, :ogr_soyad)");
    sorgu.bindValue(":ogr_ad", ui->ad_ln->text());
    sorgu.bindValue(":ogr_soyad", ui->soyad_ln->text());
    if(sorgu.exec())
    {
        sorgu.exec("select * from ogrenci");
        model->setQuery(sorgu);
        ui->ogr_table->setModel(model);
    }
}



void Ogrenci::on_guncelle_btn_clicked()
{
    QSqlQuery sorgu;

    sorgu.exec("select * from notlar where ogr_no=" + ui->no_ln->text());

    if(sorgu.next())
    {
        QMessageBox::information(this, "Hata!", "Bu öğrenci güncellenemez. Bu öğrencinin üstünde tanımlanmış dersler vardır!");
        return;
    }

    model = new QSqlQueryModel();

    sorgu.prepare("update ogrenci set ogr_ad='" + ui->ad_ln->text()
                  + "', ogr_soyad='" + ui->soyad_ln->text() + "' where ogr_no=" + ui->no_ln->text());

    if(sorgu.exec())
    {
        sorgu.exec("select * from ogrenci");
        model->setQuery(sorgu);
        ui->ogr_table->setModel(model);
    }

}


void Ogrenci::on_sil_btn_clicked()
{
    QSqlQuery sorgu;

    sorgu.exec("select * from notlar where ogr_no=" + ui->no_ln->text());

    if(sorgu.next())
    {
        QMessageBox::information(this, "Hata!", "Bu öğrenci silinemez. Bu öğrencinin üstünde tanımlanmış dersler vardır!");
        return;
    }

    model = new QSqlQueryModel();

    sorgu.prepare("delete from ogrenci where ogr_no=" + ui->no_ln->text());

    if(sorgu.exec())
    {
        sorgu.exec("select * from ogrenci");
        model->setQuery(sorgu);
        ui->ogr_table->setModel(model);
    }

    ui->no_ln->setText("");

}

