#include "PlotDialog.h"
#include "ui_plotdialog.h"
#include<algorithm>
PlotDialog::PlotDialog(std::vector<double>& dataToPlot,QWidget *parent ) :
    QDialog(parent),
    ui(new Ui::PlotDialog)
{
    ui->setupUi(this);
    for(int i = 0; i< dataToPlot.size() ; ++i)
    {
        this->epochArg.push_back(i+1);
        errorValues.push_back(dataToPlot[i]);
    }
    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setData(epochArg,errorValues);
    ui->customPlot->xAxis->setLabel("epoch");
    ui->customPlot->yAxis->setLabel("error Value");
    // set axes ranges, so we see all data:
    ui->customPlot->xAxis->setRange(1, epochArg.size());
    ui->customPlot->yAxis->setRange(0, *std::max_element(errorValues.begin(),errorValues.end()));
    ui->customPlot->replot();
}

PlotDialog::~PlotDialog()
{
    delete ui;
}
