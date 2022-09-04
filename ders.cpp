#include "ders.h"
#include "ui_ders.h"

Ders::Ders(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Ders)
{
    ui->setupUi(this);
    init();
}

Ders::~Ders()
{
    delete ui;
}

void Ders::init()
{
    QSqlQuery sorgu;
    model = new QSqlQueryModel();

    if(sorgu.exec("select * from ders"))
    {
        model->setQuery(sorgu);
        ui->dersler_table->setModel(model);
    }
}

QModelIndex indx;
QString val;
QString drs_kod;

void Ders::on_dersler_table_clicked(const QModelIndex &index)
{
    indx = index;

    QSqlQuery sorgu;
    QSqlQuery qry;

    model = new QSqlQueryModel();

    val = ui->dersler_table->model()->data(index).toString();

    sorgu.prepare("select * from ders where ders_kodu='"
                  + val + "' or ders_adi='" + val + "'");

    if(sorgu.exec())
    {
        while(sorgu.next())
        {
            drs_kod = sorgu.value(0).toString();
            ui->kod_ln->setText(sorgu.value(0).toString());
            ui->ad_ln->setText(sorgu.value(1).toString());
        }
    }



    qry.prepare("select * from notlar where ders_kodu='" + drs_kod + "'");

    if(qry.exec())
    {
        while(qry.next())
        {
            model->setQuery(qry);
        }

        ui->ogr_table->setModel(model);



    }

}


void Ders::on_yeni_ln_clicked()
{
    if(ui->kod_ln->text() == "" or ui->ad_ln->text() == "")
    {
        QMessageBox::critical(this, "HATA!", "Gerekli Alanları Doldurunuz");
        return;
    }

    QSqlQuery sorgu;
    model = new QSqlQueryModel();

    sorgu.prepare("insert into ders values (:ders_kodu, :ders_adi)");
    sorgu.bindValue(":ders_kodu", ui->kod_ln->text());
    sorgu.bindValue(":ders_adi", ui->ad_ln->text());

    if(sorgu.exec())
    {
        sorgu.exec("select * from ders");
        model->setQuery(sorgu);
        ui->dersler_table->setModel(model);
    }

    else if (sorgu.lastError().nativeErrorCode() == "1555")
    {
        QMessageBox::information(this, "HATA!", "Bu kodda başka bir ders vardır. Farklı kodda ders ekleyiniz!");
    }

}


void Ders::on_guncelle_ln_clicked()
{
    if(ui->kod_ln->text() == "" or ui->ad_ln->text() == "")
    {
        QMessageBox::critical(this, "HATA!", "Gerekli Alanları Doldurunuz");
        return;
    }

    QSqlQuery sorgu;

    sorgu.exec("select * from notlar where ders_kodu=" + drs_kod);

    if(sorgu.next())
    {
        QMessageBox::information(this, "Hata!", "Bu ders güncellenemez. Bu derse kayıtlı öğrenciler vardır!");
        return;
    }

    model = new QSqlQueryModel();

    sorgu.prepare("update ders set ders_kodu='"
                  + ui->kod_ln->text() + "', ders_adi='" + ui->ad_ln->text()
                  + "' where ders_kodu='" + val + "' or ders_adi='" +
                  val + "'");

    if(sorgu.exec())
    {
        sorgu.exec("select * from ders");
        model->setQuery(sorgu);
        ui->dersler_table->setModel(model);
    }

    else if (sorgu.lastError().nativeErrorCode() == "1555")
    {
        QMessageBox::information(this, "HATA!", "Bu kodda başka bir ders vardır. Farklı kodda ders ekleyiniz!");
    }


}


void Ders::on_sil_ln_clicked()
{

    QString val = ui->dersler_table->model()->data(indx).toString();

    QSqlQuery sorgu;
    model = new QSqlQueryModel();

    sorgu.prepare("select * from notlar where ders_kodu='" + ui->kod_ln->text() + "'");

    if(sorgu.exec())
    {
        while(sorgu.next())
        {
            QMessageBox::information(this, "Hata!", "Bu ders silinemez. Bu derse kayıtlı öğrenciler vardır!");
            return;
        }
    }

    sorgu.prepare("delete from ders where ders_kodu='"
                  + val + "' or ders_adi='" + val + "'");

    if(sorgu.exec())
    {
        sorgu.exec("select * from ders");
        model->setQuery(sorgu);
        ui->dersler_table->setModel(model);
    }

}


















