#include "SetHiddenLayersDialog.h"
#include "ui_setHiddenLayersDialog.h"
#include<QVector>
#include<QPlainTextEdit>
#include<QLabel>
#include<QMessageBox>
setHiddenLayersDialog::setHiddenLayersDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::setHiddenLayersDialog)
{
    setAttribute(Qt::WA_DeleteOnClose);
    ui->setupUi(this);
}

setHiddenLayersDialog::setHiddenLayersDialog(int hiddenLayers, QWidget *parent) :
    QDialog(parent),
    hiddenLayersNumber(hiddenLayers),
    ui(new Ui::setHiddenLayersDialog)
{

    widget = new QWidget(this);
    ui->setupUi(this);
    int x = 0 ;
    int y = 0;
    QSize * size = new QSize(70,hiddenLayers*35);
    widget->setMinimumSize(*size);

    for(int i=0; i < hiddenLayers; ++i)
    {
        QString labelText("Hidden layer");
        labelText += QString::number(i+1);
        QLabel* label = new QLabel(labelText,widget);
        label->setGeometry(x,y,80,25);
        labels.push_back(label);

        QLineEdit* textBox = new QLineEdit(widget);
        textBox->setGeometry(x+label->width()+20,y,40,25);
        textBoxes.push_back(textBox);

        y+=10 + textBox->height();

    }

    ui->scrollArea->setWidgetResizable(true);
    ui->scrollArea->setWidget(widget);

}

setHiddenLayersDialog::~setHiddenLayersDialog()
{
    delete ui;
    for(int i = 0 ; i < hiddenLayersNumber ; ++i)
    {
        delete labels[i];
        delete textBoxes[i];
    }
}


void setHiddenLayersDialog::on_acceptButton_clicked()
{
    std::vector<int> hiddenLayers;
    netParametersWindow *myParent= qobject_cast<netParametersWindow *>(parent());
    bool everyTextIsNum = true;
    int i = 0;
    while(i < hiddenLayersNumber && everyTextIsNum)

    {
        int neuronsNumber = textBoxes.at(i)->text().toInt(&everyTextIsNum);

        if(everyTextIsNum)  hiddenLayers.push_back(neuronsNumber);

        i++;
    }
    if(everyTextIsNum)
    {
        for(int i = 0 ; i < hiddenLayers.size(); ++i)
        {
            myParent->hiddenLayersTopology->push_back(hiddenLayers[i]);
        }
        this->close();
    }
    else
        QMessageBox::warning(this,"Warning !","Every text must be a number !","OK");
}
