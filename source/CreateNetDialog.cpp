#include "CreateNetDialog.h"
#include "ui_createnetdialog.h"
#include"MainWindow.h"
#include"QMessageBox"
CreateNetDialog::CreateNetDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateNetDialog)
{
    setAttribute(Qt::WA_DeleteOnClose);
    ui->setupUi(this);
    topologyIsSetted = false;
    neuronParametersIsSetted = false;
}

CreateNetDialog::~CreateNetDialog()
{
    delete ui;
}

void CreateNetDialog::on_netTopologyButton_clicked()
{
    netParametersWindow* newWindow = new netParametersWindow(this);
    newWindow->show();
}

void CreateNetDialog::on_neuronSettingsButton_clicked()
{
    NeuronSettingsDialog* newDialog = new NeuronSettingsDialog(this);
    newDialog->show();
}



void CreateNetDialog::on_acceptButton_clicked()
{
    if(topologyIsSetted && neuronParametersIsSetted)
    {
    MainWindow* myParent = qobject_cast<MainWindow*>(parent());
    myParent->netParameters = netParameters;
    myParent->createNet();
    this->close();
    }

    else
        QMessageBox::warning(this,"Warning","Set all net parameters : topology and neuron settings","OK");
}
