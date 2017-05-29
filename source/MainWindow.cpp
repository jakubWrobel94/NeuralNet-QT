#include "MainWindow.h"
#include "ui_mainwindow.h"
#include"CreateNetDialog.h"
#include<QMessageBox>
#include"SetTrainDataDialog.h"
#include"TrainingData.h"
#include"BackPropagation.h"
#include"TrainingWidget.h"
#include<vector>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    net = nullptr;
    data = nullptr;
    backpropagation = nullptr;
    trainingWidget = new TrainingWidget(this);
    trainingWidget->show();
    trainingWidget->setGeometry(220,42,200,300);
    trainingWidget->setEnabled(false);
    //ui->feedFowardWidget->setEnabled(false );
    //ui->feedFowardWidget->activateWindow();


 }

MainWindow::~MainWindow()
{
    delete ui;
   if(net != nullptr) delete net;
   if(data != nullptr)delete data;
   if(backpropagation != nullptr)delete backpropagation;
   delete trainingWidget;
}

void MainWindow::createNet()
{

    if(net != nullptr)
    {
        delete net;
        QMessageBox::information(this,"Info","Old net has been deleted!");
    }

    net = new Net(netParameters.netTopology,netParameters.activationFunction, netParameters.beta);
    setNetInfo();

    QMessageBox::information(this,"Info","New net has been created !");

    if(data != nullptr)
        createBackPropagation();
}

void MainWindow::createTrainingData(QString &samplesPath, QString &targetsPath)
{
    std::string samplesPathString = samplesPath.toStdString();
    std::string targetsPathString = targetsPath.toStdString();

    if(data != nullptr) delete data;

    data = new TrainingData(samplesPathString,targetsPathString);
    if(net != nullptr)
    {
        if(data->getSamplePointer(0)->size() != net->getFirstLayer()->size())
            QMessageBox::warning(this,"Warrning!!","Data structure doesn't fit to net!");
        else
            createBackPropagation();
    }
    ui->textBoxSamplesNumber->setText(QString::number(data->getSamplesNumber()));
    QMessageBox::information(this,"Info","Data has been set !");
}

void MainWindow::createBackPropagation()
{

    backpropagation = new BackPropagation(*net,*data);
    trainingWidget->setEnabled(true);
    ui->groupBoxFeedFoward->setEnabled(true);

}

void MainWindow::setNetInfo()
{
    QString topologyText="";
    for(int i = 0; i < netParameters.netTopology.size(); ++i)
    {
        topologyText += QString::number(netParameters.netTopology[i]);
        if(i != netParameters.netTopology.size() - 1) topologyText += "-";
    }
    ui->textBoxTopology->setText(topologyText);
    if(netParameters.activationFunction == 0) ui->textBoxActFun->setText("Logistic");
    if(netParameters.activationFunction == 1) ui->textBoxActFun->setText("Tangh");
    ui->textBoxBeta->setText(QString::number(netParameters.beta));

}

Ui::MainWindow *MainWindow::getUi()
{
    return ui;
}

BackPropagation *MainWindow::getBackPropagation()
{
    return backpropagation;
}

void MainWindow::createNewNetWindow()
{
    CreateNetDialog* newWindow = new CreateNetDialog(this);
    newWindow->show();
}

void MainWindow::createSetTrainDataDialog()
{
    setTrainDataDialog = new SetTrainDataDialog(this);
    setTrainDataDialog ->show();
}


void MainWindow::on_pushButton_clicked()
{

    QString inputString = ui->inputTextBox->text();

    QStringList stringList = inputString.split(" ");
    std::vector<double> inputVector;
    for(int i =0; i< stringList.size() ; ++i)
    {
        inputVector.push_back(stringList[i].toDouble());

    }
    if(stringList.size() == net->getTopology()->at(0))
    {
    this->net->setInputs(inputVector);
    this->net->feedFoward();

    QString outputString;
    std::vector<double>* outputVector = net->getOutput();
    for(int i = 0; i< outputVector->size();++i)
    {
        outputString += QString::number(outputVector->at(i));
    }
    ui->outputTextBox->setText(outputString);
    }
    else
        QMessageBox::warning(this,"Warning","Inputs must have same size as input layer !","OK");
}
