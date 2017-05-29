#include "SetTrainDataDialog.h"
#include "ui_settraindatadialog.h"
#include<QFileDialog>
#include"MainWindow.h"
#include<QMessageBox>
SetTrainDataDialog::SetTrainDataDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetTrainDataDialog)
{
    setAttribute(Qt::WA_DeleteOnClose);
    ui->setupUi(this);
    samplesDirectory = nullptr;
    targetsDirectory = nullptr;
}

SetTrainDataDialog::~SetTrainDataDialog()
{
    delete ui;
    delete samplesDirectory;
    delete targetsDirectory;
}

void SetTrainDataDialog::loadSamples()
{
    samplesDirectory = new QString(QFileDialog::getOpenFileName(this,"Choose target file","","Text file (*.txt)"));
    ui->lineEdit->setText(*samplesDirectory);
}

void SetTrainDataDialog::loadTargets()
{
    targetsDirectory = new QString(QFileDialog::getOpenFileName(this,"Choose target file","","Text file (*.txt)"));
    ui->lineEdit_2->setText(*targetsDirectory);
}

void SetTrainDataDialog::on_pushButton_clicked()
{
    loadSamples();

}

void SetTrainDataDialog::on_pushButton_4_clicked()
{
    this->close();
    //delete this;
}

void SetTrainDataDialog::on_pushButton_2_clicked()
{
    loadTargets();
}

void SetTrainDataDialog::on_pushButton_3_clicked()
{
    if(!ui->lineEdit->text().isEmpty() && !ui->lineEdit_2->text().isEmpty())
       {
    MainWindow* myParent = qobject_cast<MainWindow*>(parent());
    myParent->createTrainingData(*samplesDirectory,*targetsDirectory);
    this->close();
    }
    else
        QMessageBox::warning(this,"Warning","Both paths must be setted.","OK");
}
