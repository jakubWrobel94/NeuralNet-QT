#ifndef CREATENETDIALOG_H
#define CREATENETDIALOG_H

#include <QDialog>
#include"NetParametersWindow.h"
#include"NeuronSettingsDialog.h"
#include<vector>
#include"NetParameters.h"



namespace Ui {
class CreateNetDialog;
}

class CreateNetDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreateNetDialog(QWidget *parent = 0);
    ~CreateNetDialog();
    NetParameters netParameters;

    bool topologyIsSetted;
    bool neuronParametersIsSetted;

private slots:
    void on_netTopologyButton_clicked();

    void on_neuronSettingsButton_clicked();

    void on_acceptButton_clicked();

private:
    Ui::CreateNetDialog *ui;
};

#endif // CREATENETDIALOG_H
