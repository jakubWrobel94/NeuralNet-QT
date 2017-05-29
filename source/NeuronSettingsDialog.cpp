#include "NeuronSettingsDialog.h"
#include "ui_NeuronSettingsDialog.h"
#include<QMessageBox>
#include<math.h>
NeuronSettingsDialog::NeuronSettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NeuronSettingsDialog)
{
    setAttribute(Qt::WA_DeleteOnClose);
    ui->setupUi(this);
    plot();
}

NeuronSettingsDialog::~NeuronSettingsDialog()
{
    delete ui;
}

void NeuronSettingsDialog::plot()
{

    QVector<double> arguments(101);
    QVector<double> values(101);
    double beta = ui->betaTextBox->text().toDouble();
    if(ui->tanghRadioButton->isChecked())
    {
        for(int i=0; i<101;++i)
        {
            double x = i/25.0 -2;;
            arguments[i] = x;
            values[i] = std::tanh(beta*x);
        }
    }
    if(ui->logisticRadioButton->isChecked())
    {
    for(int i=0; i<101;++i)
    {
        double x = i/25.0 -2;

        arguments[i] = x ;
        values[i] = 1/(1+exp(-beta*x));
    }
    }

    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setData(arguments,values);
    ui->customPlot->xAxis->setLabel("x");
    ui->customPlot->yAxis->setLabel("y");
    ui->customPlot->xAxis->setRange(-2,2);
    ui->customPlot->yAxis->setRange(-1.5,1.5);
    ui->customPlot->replot();
}


void NeuronSettingsDialog::on_pushButton_clicked()
{
    bool radioButtonIsChecked = false;
    bool betaIsNum = false;

    if(ui->tanghRadioButton->isChecked() || ui->logisticRadioButton->isChecked()) radioButtonIsChecked = true;
    double beta = ui->betaTextBox->text().toDouble(&betaIsNum);
    if(radioButtonIsChecked && betaIsNum)
    {
    CreateNetDialog *myParent= qobject_cast<CreateNetDialog *>(parent());
    myParent->netParameters.beta = beta;
    if(ui->tanghRadioButton->isChecked()) myParent->netParameters.activationFunction = 1;
    if(ui->logisticRadioButton->isChecked()) myParent->netParameters.activationFunction = 0;
    myParent->neuronParametersIsSetted = true;
    this->close();
    }
    else
        QMessageBox::warning(this,"Warning","At least one radio button must be checked and beta must be a number","OK");
}
