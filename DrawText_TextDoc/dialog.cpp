#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::paintEvent(QPaintEvent *)
{
   QPainter painter(this);
   painter.drawText(100,100,"hello world");

   QRect rec(100,125,250,25);
   painter.drawRect(rec);
   painter.drawText(rec,Qt::AlignLeft | Qt::AlignVCenter,"Left");
   painter.drawText(rec,Qt::AlignCenter,"Center");
   painter.drawText(rec,Qt::AlignRight | Qt::AlignVCenter,"Right");

   QRect rec2(120,170,30,30);
   painter.drawRect(rec2);
   painter.drawText(rec2,"We cannot see anything");

   QTextDocument doc;
   QRect rect3(0,0,250,250);
   painter.translate(20,20);
   doc.setTextWidth((rect3.width()));
   doc.setHtml("<b><u>Hello</u></b> <br><br> <font face='Aria' color='blue' size='30'><i>world</i></font>");
   doc.drawContents(&painter,rect3);

}
