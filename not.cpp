#include "not.h"
#include "ui_not.h"

Not::Not(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Not)
{
    ui->setupUi(this);
    init();
}

Not::~Not()
{
    delete ui;
}

void Not::init()
{

    QPalette palette;
    palette.setColor(ui->not_lbl->foregroundRole(), Qt::red);
    ui->not_lbl->setPalette(palette);

    QSqlQuery sorgu;

    sorgu.prepare("select * from ogrenci");
    model = new QSqlQueryModel();

    if(sorgu.exec())
    {
        model->setQuery(sorgu);
        ui->ogr_table->setModel(model);
    }

    sorgu.prepare("select * from ders");
    model = new QSqlQueryModel();

    if(sorgu.exec())
    {
        model->setQuery(sorgu);
        ui->ders_table->setModel(model);
    }

    sorgu.prepare("select * from notlar");
    model = new QSqlQueryModel();

    if(sorgu.exec())
    {
        model->setQuery(sorgu);
        ui->not_table->setModel(model);
    }

}




void Not::on_ogr_table_clicked(const QModelIndex &index)
{
    QString val = ui->ogr_table->model()->data(index).toString();

    QSqlQuery sorgu;

    sorgu.prepare("select ogr_no from ogrenci where ogr_no='"
                  + val + "' or ogr_ad='"
                  + val + "' or ogr_soyad='" + val + "'");

    if(sorgu.exec())
    {
        if(sorgu.next())
        {
            ui->no_ln->setText(sorgu.value(0).toString());
        }
    }
}



void Not::on_ders_table_clicked(const QModelIndex &index)
{
    QString val = ui->ders_table->model()->data(index).toString();

    QSqlQuery sorgu;

    sorgu.prepare("select ders_kodu from ders where ders_kodu='"
                  + val + "' or ders_adi='" + val + "'");

    if(sorgu.exec())
    {
        if(sorgu.next())
        {
            ui->kod_ln->setText(sorgu.value(0).toString());
        }
    }
}


void Not::on_kayit_btn_clicked()
{

    if(ui->vize_ln->text() == "" or ui->final_ln->text() == ""
            or ui->kod_ln->text() == "" or ui->no_ln->text() == "")
    {
        QMessageBox::critical(this, "Hata!", "Gerekli alanları doldurunuz!");
        return;
    }

    QSqlQuery sorgu;

    sorgu.prepare("select * from notlar where ogr_no='"
            + ui->no_ln->text() + "' and ders_kodu='" +
            ui->kod_ln->text() + "'");
    sorgu.exec();

    if(sorgu.next())
    {
        QMessageBox::information(this,"Hata!", "Bu öğrenci üzerine bu ders zaten tanımlı!");
        return;
    }

    model = new QSqlQueryModel();

    sorgu.prepare("insert into notlar values (:ogr_no, :ders_kodu, :vize_not, :final_not, :gecme_notu)");
    sorgu.bindValue(":ogr_no", ui->no_ln->text());
    sorgu.bindValue(":ders_kodu", ui->kod_ln->text());
    sorgu.bindValue(":vize_not", ui->vize_ln->text());
    sorgu.bindValue(":final_not", ui->final_ln->text());
    int gecme_not = ui->vize_ln->text().toInt() * 0.4 + ui->final_ln->text().toInt() * 0.6;
    sorgu.bindValue(":gecme_notu", QString::number(gecme_not));

    if(sorgu.exec())
    {
        sorgu.exec("select * from notlar");
        model->setQuery(sorgu);
        ui->not_table->setModel(model);

    }




    else
    {
        QMessageBox::information(this,"h", sorgu.lastError().text());
    }
}


