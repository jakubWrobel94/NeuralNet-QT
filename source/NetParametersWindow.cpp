#include "NetParametersWindow.h"
#include "ui_netparameterswindow.h"
#include<QMessageBox>
netParametersWindow::netParametersWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::netParametersWindow)
{
    setAttribute(Qt::WA_DeleteOnClose);
    ui->setupUi(this);
    hiddenLayersTopology = new std::vector<int>;

}

netParametersWindow::~netParametersWindow()
{
    delete ui;
    delete hiddenLayersTopology;
}

void netParametersWindow::on_cancelButton_clicked()
{
    this->close();
}

void netParametersWindow::on_setHiddenLayersbutton_clicked()
{
    int hiddenLayers = ui->lineEdit_2->text().toInt();
    setHiddenLayersDialog* newDialog = new setHiddenLayersDialog(hiddenLayers,this);
    newDialog->show();
}

void netParametersWindow::on_acceptButton_clicked()
{

    //std::vector<int>& topology = (myParent->netParameters.netTopology);
    std::vector<int> topology;
    bool inputValue = true;
    bool outputValue = true;
    topology.push_back(ui->lineEdit_1->text().toInt(&inputValue));
    if(!hiddenLayersTopology->empty())
    {
    for(int i = 0; i < hiddenLayersTopology->size();++i)
    {

       topology.push_back(hiddenLayersTopology->at(i));
    }
    }
    topology.push_back(ui->lineEdit_3->text().toInt(&outputValue));
    if(inputValue && outputValue)
    {
    CreateNetDialog *myParent= qobject_cast<CreateNetDialog *>(parent());
    myParent->netParameters.netTopology = topology;
    myParent->topologyIsSetted = true;
    this->close();
    }
    else
        QMessageBox::warning(this,"Warning","All text boxes must be string.","OK");
}
