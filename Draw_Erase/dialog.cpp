#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    QPainter painter(this);
    QRect rec(0,0,250,250);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QTextDocument doc;
    QRect rec(0,0,250,250);
    painter.translate(20,20);
    doc.setTextWidth(rec.width());
    doc.setHtml("<b><u>Hello</u></b><br><br><font face='Arial' color='red' size='6'><i>world</i></font>");
    doc.drawContents(&painter,rec);
    }

void Dialog::on_pushButton_clicked()
{

    QPainter painter(this);
    QTextDocument doc;
    QRect rec(0,0,250,250);
    painter.translate(20,20);
    doc.setTextWidth(rec.width());
    doc.setHtml("<b><u>Hello</u></b><br><br><font face='Arial' color='red' size='6'><i>world</i></font>");
    doc.drawContents(&painter,rec);

    painter.eraseRect(rec);

}
