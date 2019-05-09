#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include"logindlg.h"
//#include"newroutedlg.h"
#include<QImage>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /*添加图片*/
    QImage *img=new QImage;//新建一个image对象
    if(!(img->load("D:/QT/project/Tourist/map.jpg")))//将图像资源载入对象img
    {
        ui->pic_lb->setText("fail to load picture");
    }
    else
        ui->pic_lb->setPixmap((QPixmap::fromImage(*img)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_signIn_btn_clicked()
{
    LoginDlg *lDlg=new LoginDlg(this);
    if(lDlg->exec()==QDialog::Accepted)
    {
        newRouteDlg nDlg;
        if(nDlg.exec()==QDialog::Accepted)
        {
            /*在mainWindow界面里增加一行*/
        }
    }
}
