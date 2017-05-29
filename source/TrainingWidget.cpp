#include "TrainingWidget.h"
#include "ui_trainingwidget.h"
#include"BackPropObserver.h"
#include"BackPropagation.h"
#include"MainWindow.h"
#include"PlotDialog.h"
#include"ui_mainwindow.h"
TrainingWidget::TrainingWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TrainingWidget)
{
    ui->setupUi(this);
    firstTraining = true;
}

TrainingWidget::~TrainingWidget()
{
    delete ui;
}

void TrainingWidget::on_pushButton_clicked()
{
    MainWindow* myParent = qobject_cast<MainWindow*>(parent());
    BackPropagation *backPropagation = myParent->getBackPropagation();
    Neuron::setEta(myParent->getUi()->learningRateTextBox->text().toDouble());
    if(!firstTraining) backPropagation->reset();
    observer = new BackPropObserver(myParent->getBackPropagation(),ui->textBoxEpoch,ui->textBoxError,ui->progressBar);
    if(myParent->getUi()->radioButtonOnline->isChecked()) backPropagation->onlineTrain();
    if(myParent->getUi()->radioButtonBatch->isChecked()) backPropagation->batchTrain();
    firstTraining = false;
}

void TrainingWidget::on_plotButton_clicked()
{
    MainWindow* myParent = qobject_cast<MainWindow*>(parent());
    std::vector<double> &dataToPlot = myParent->getBackPropagation()->getErrorVector();
    PlotDialog* plotDialog = new PlotDialog(dataToPlot,this);
    plotDialog->show();
}
